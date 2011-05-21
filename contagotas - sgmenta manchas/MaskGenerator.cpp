#include "MaskGenerator.h"

MaskGenerator::MaskGenerator() {
	maxPixelValue = 1;
	this->externalThreshold = false;
}

MaskGenerator::~MaskGenerator() {
}

void MaskGenerator::SetInput(ImageType::Pointer InputImage) {
	this->inputImage = InputImage;
	// mask image allocation
	this->mask = MaskImageType::New();
	MaskImageType::IndexType maskIndex;
	maskIndex.Fill(0);
	RegionType anotherRegion;
	anotherRegion.SetIndex(maskIndex);
	anotherRegion.SetSize(this->inputImage->GetLargestPossibleRegion().GetSize());
	mask->SetLargestPossibleRegion(anotherRegion);
	mask->SetBufferedRegion(anotherRegion);
	mask->SetRequestedRegion(anotherRegion);
	mask->Allocate();
}

void MaskGenerator::Update() {
	SizeType inputImageSize = this->inputImage->GetLargestPossibleRegion().GetSize();
	IndexType index;
	for (index[0] = 0; (long) index[0] < (long) inputImageSize[0]; index[0]++) {
		for (index[1] = 0; (long) index[1] < (long) inputImageSize[1]; index[1]++) {
			this->mask->SetPixel(index, (this->pixelToHSV(inputImage->GetPixel(index)) ));
		}
	}
	this->generateOutput();
}

double MaskGenerator::pixelToHSV(PixelType pixel) {
	float tmp2 = 1.0 / 255.0;
	float tmp = (1.0 / 6.0)*255.0;
	int F, I;
	double R, G, B, H, S, V, X;
	//PixelType pixel = inputImage->GetPixel();
	R = (double) pixel.GetRed();
	G = (double) pixel.GetGreen();
	B = (double) pixel.GetBlue();
	X = MIN3(R, G, B);
	V = MAX3(R, G, B);
	if (V == X) {
		H = 0.0;
		S = 0.0;
	} else {
		S = (float) (V - X) / (float) V * 255.0;
		F = (R == V) ? (G - B) : ((G == V) ? (B - R) : (R - G));
		I = (R == V) ? 0 : ((G == V) ? 2 : 4);
		H = (I + (float) F / (float) (V - X)) * tmp; // /6.0*255.0;
		if (H < 0) {
			H += 255.0;
		}
		if (H < 0.0 || H > 255.0 || V < 0 || V > 255.0) {
			cerr << "Bad HS values: " << H << " " << S << endl;
			exit(-1);
		}
	}
	return ((V * tmp2)*(S * tmp2)*(H * tmp2))*255.0;
}

void MaskGenerator::generateOutput() {

	// generating histogram
	typedef itk::Statistics::ScalarImageToListAdaptor< MaskImageType > AdaptorType;
	typedef unsigned char HistogramMeasurementType;
	typedef itk::Statistics::ListSampleToHistogramGenerator< AdaptorType, HistogramMeasurementType > GeneratorType;
	typedef GeneratorType::HistogramType HistogramType;

	AdaptorType::Pointer adaptor = AdaptorType::New();
	adaptor->SetImage(this->mask);
	GeneratorType::Pointer generator = GeneratorType::New();
	HistogramType::SizeType size;
	size.Fill(256);
	generator->SetListSample(adaptor);
	generator->SetNumberOfBins(size);
	generator->SetMarginalScale(10.0);
	HistogramType::MeasurementVectorType min;
	HistogramType::MeasurementVectorType max;
	min.Fill(-0.5);
	max.Fill(255.5);
	generator->SetHistogramMin(min);
	generator->SetHistogramMax(max);
	generator->Update();
	HistogramType::ConstPointer histogram = generator->GetOutput();
	const unsigned int histogramSize = histogram->Size();
	this->maxHistogramValue = 0;
	// calculating maximum value of histogram
	for (unsigned int bin = 0; bin < histogramSize; bin++) {
		if( histogram->GetFrequency(this->maxHistogramValue, 0) < histogram->GetFrequency(bin, 0) ){
			this->maxHistogramValue = bin;
		}
	}
	//cerr << "calculed threshold = " << round(this->maxHistogramValue*1.3) << endl;
	if (!externalThreshold) this->thresholdValue = this->maxHistogramValue*1.5;
	ThresholdFilterType::Pointer thresholdFilter = ThresholdFilterType::New();
	thresholdFilter->SetInput(this->mask);
	thresholdFilter->SetLowerThreshold( this->thresholdValue );
	thresholdFilter->Update();
	//cerr << "threshold value = " << this->thresholdValue << "...";

	outputImage = thresholdFilter->GetOutput();
}

MaskGenerator::MaskImageType::Pointer MaskGenerator::GetOutput() {
	return outputImage;
	//return mask;
}

void MaskGenerator::SetThresholdValue(double v){
	this->thresholdValue = v;
	this->externalThreshold = true;
}

MaskGenerator::Pointer MaskGenerator::New() {
	return new MaskGenerator();
}

void MaskGenerator::SetMaxPixelValue(int value) {
	this->maxPixelValue = value;
}

