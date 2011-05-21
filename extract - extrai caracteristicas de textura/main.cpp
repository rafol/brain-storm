#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <itkImage.h>
#include "itkImageFileReader.h"
#include <itkRescaleIntensityImageFilter.h>
#include "itkRegionOfInterestImageFilter.h"
#include "itkScalarImageTextureCalculator.h"
#include "itkGreyLevelCooccurrenceMatrixTextureCoefficientsCalculator.h"
#include "RGBFilter.h"

#define IMAGE_DIMENSIONS 2

typedef itk::RGBPixel<unsigned char> PixelType;
typedef itk::Image< PixelType, IMAGE_DIMENSIONS > ImageType;
typedef itk::Image< unsigned char, IMAGE_DIMENSIONS > ImageTypeExt;
typedef itk::Image< unsigned char, IMAGE_DIMENSIONS > ImageTypeInt;
typedef itk::ImageFileReader< ImageType > ReaderType;
typedef itk::RescaleIntensityImageFilter< ImageTypeExt, ImageTypeInt > RescaleType;
typedef itk::RegionOfInterestImageFilter< ImageTypeInt, ImageTypeInt > ROIFilterType;
typedef itk::Statistics::ScalarImageTextureCalculator<ImageTypeInt> TextureCalculator;

using namespace std;

void decodeCharactheristic(int x, char name[]) {
	switch(x) {
		case 0:
			strcpy(name, "energy");
			break;
		case 1:
			strcpy(name, "entropy");
			break;
		case 3:
			strcpy(name, "inverseDifferenceMoment");
			break;
		case 4:
			strcpy(name, "contrast");
			break;
		case 7:
			strcpy(name, "correlation");
			break;
	}
}

int main(int argc, char **argv)	{
	unsigned int x;
	//-----------------------Checking program call syntx------------------------
	if( argc<3 ){
		cout << "Wrong arguments. Syntex:" << endl;
		cout << "\t" << argv[0] << " <input_file> <output_file>" << endl;
		exit(1);
	}
	//----------------------------File Reading----------------------------------
	//cerr << "Abrindo arquivo... ";
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(argv[1]); //le imagem stress do paciente
	reader->Update();
	ImageType::Pointer imagem = reader->GetOutput();
	
	double max[26] = {80.0, // size 1
							80.0, // size 2
							0.497945, // 8 red caracs
							7.655577,
							0.735413,
							44590.607435,
							181701329.792638,
							0.006324,
							7413811.884241,
							3136752424.97704,
							0.49789,  // 8 green caracs
							7.722023,
							0.734585,
							44742.509646,
							190876564.899964,
							0.003388,
							7449771.700953,
							3153145456.1761,
							0.497906, // 8 blue caracs
							7.653616,
							0.744153,
							41882.242635,
							224157204.126346,
							0.009425,
							7903470.37811,
							3508972233.78681};
	
	FILE* fp = fopen(argv[2], "a+");
	fprintf(fp, "%f %f ", imagem->GetLargestPossibleRegion().GetSize()[0]/max[0], imagem->GetLargestPossibleRegion().GetSize()[1]/max[1]);
	//cerr << "OK" << endl;
	//----------------------------Dividindo os canais----------------------------
	//cerr << "Dividindo canais RGB... ";
	RGBFilter::Pointer splitter = new RGBFilter();
	splitter->SetInput(imagem);
	splitter->Update();
	//cerr << "OK" << endl;
	//-------------------------Rescaling Input Image----------------------------
	//cerr << "selecionando regiao de interesse e redimencionando...";
	RescaleType::Pointer rescalerFilter1 = RescaleType::New();
	rescalerFilter1->SetInput(splitter->GetRed());
	ROIFilterType::Pointer roiFilterLeft1 = ROIFilterType::New();
	roiFilterLeft1->SetRegionOfInterest( imagem->GetLargestPossibleRegion() );
	roiFilterLeft1->SetInput(rescalerFilter1->GetOutput());
	roiFilterLeft1->Update();
	//cerr << "Red...";
	
	RescaleType::Pointer rescalerFilter2 = RescaleType::New();
	rescalerFilter2->SetInput(splitter->GetGreen());
	ROIFilterType::Pointer roiFilterLeft2 = ROIFilterType::New();
	roiFilterLeft2->SetRegionOfInterest( imagem->GetLargestPossibleRegion() );
	roiFilterLeft2->SetInput(rescalerFilter2->GetOutput());
	roiFilterLeft2->Update();
	//cerr << "Green...";
	
	RescaleType::Pointer rescalerFilter3 = RescaleType::New();
	rescalerFilter3->SetInput(splitter->GetBlue());
	ROIFilterType::Pointer roiFilterLeft3 = ROIFilterType::New();
	roiFilterLeft3->SetRegionOfInterest( imagem->GetLargestPossibleRegion() );
	roiFilterLeft3->SetInput(rescalerFilter3->GetOutput());
	roiFilterLeft3->Update();
	//cerr << "Blue...";
	//cerr << "OK!" << endl;
	//-----------------------------Extraindo Caracteristicas---------------------
	//cerr << "Extraindo caracteristicas...";
	
	TextureCalculator::Pointer calc1  = TextureCalculator::New();
	TextureCalculator::FeatureNameVector::Pointer featureVector1 = TextureCalculator::FeatureNameVector::New();
	featureVector1->InsertElement(0, itk::Statistics::Energy);
	featureVector1->InsertElement(1, itk::Statistics::Entropy);
	featureVector1->InsertElement(2, itk::Statistics::InverseDifferenceMoment);
	featureVector1->InsertElement(3, itk::Statistics::Inertia);
	featureVector1->InsertElement(4, itk::Statistics::HaralickCorrelation);
	featureVector1->InsertElement(5, itk::Statistics::Correlation);
	featureVector1->InsertElement(6, itk::Statistics::ClusterShade);
	featureVector1->InsertElement(7, itk::Statistics::ClusterProminence);

	calc1->SetRequestedFeatures(featureVector1);
	calc1->SetInput(roiFilterLeft1->GetOutput());
	calc1->Compute();

	unsigned long size1 = calc1->GetFeatureMeans()->Size();
	for(x = 0; x < size1; x++) {
		char charactheristic[100];
		decodeCharactheristic(calc1->GetRequestedFeatures()->GetElement(x), charactheristic);
		fprintf(fp, "%lf ", calc1->GetFeatureMeans()->GetElement(x)/max[2+x]);
	}
	//fprintf(fp, "\n");
	//cerr << "Red...";
	
	TextureCalculator::Pointer calc2  = TextureCalculator::New();
	TextureCalculator::FeatureNameVector::Pointer featureVector2 = TextureCalculator::FeatureNameVector::New();
	featureVector2->InsertElement(0, itk::Statistics::Energy);
	featureVector2->InsertElement(1, itk::Statistics::Entropy);
	featureVector2->InsertElement(2, itk::Statistics::InverseDifferenceMoment);
	featureVector2->InsertElement(3, itk::Statistics::Inertia);
	featureVector2->InsertElement(4, itk::Statistics::HaralickCorrelation);
	featureVector2->InsertElement(5, itk::Statistics::Correlation);
	featureVector2->InsertElement(6, itk::Statistics::ClusterShade);
	featureVector2->InsertElement(7, itk::Statistics::ClusterProminence);

	calc2->SetRequestedFeatures(featureVector2);
	calc2->SetInput(roiFilterLeft2->GetOutput());
	calc2->Compute();

	unsigned long size2 = calc2->GetFeatureMeans()->Size();
	for(x = 0; x < size2; x++) {
		char charactheristic[100];
		decodeCharactheristic(calc2->GetRequestedFeatures()->GetElement(x), charactheristic);
		fprintf(fp, "%lf ", calc2->GetFeatureMeans()->GetElement(x)/max[10+x]);
	}
	//fprintf(fp, "\n");
	//cerr << "Green...";
	
	TextureCalculator::Pointer calc3  = TextureCalculator::New();
	TextureCalculator::FeatureNameVector::Pointer featureVector3 = TextureCalculator::FeatureNameVector::New();
	featureVector3->InsertElement(0, itk::Statistics::Energy);
	featureVector3->InsertElement(1, itk::Statistics::Entropy);
	featureVector3->InsertElement(2, itk::Statistics::InverseDifferenceMoment);
	featureVector3->InsertElement(3, itk::Statistics::Inertia);
	featureVector3->InsertElement(4, itk::Statistics::HaralickCorrelation);
	featureVector3->InsertElement(5, itk::Statistics::Correlation);
	featureVector3->InsertElement(6, itk::Statistics::ClusterShade);
	featureVector3->InsertElement(7, itk::Statistics::ClusterProminence);

	calc3->SetRequestedFeatures(featureVector3);
	calc3->SetInput(roiFilterLeft3->GetOutput());
	calc3->Compute();

	unsigned long size3 = calc3->GetFeatureMeans()->Size();
	for(x = 0; x < size3; x++) {
		char charactheristic[100];
		decodeCharactheristic(calc3->GetRequestedFeatures()->GetElement(x), charactheristic);
		fprintf(fp, "%lf ", calc3->GetFeatureMeans()->GetElement(x)/max[18+x]);
	}
	// imprimindo pixels
	ImageType::IndexType xxx;
	for ( xxx[0]=0 ; xxx[0]<80 ; xxx[0]++){
		for (xxx[1]=0 ; xxx[1]<80 ; xxx[1]++){
			if( (unsigned) xxx[0]<imagem->GetLargestPossibleRegion().GetSize()[0] && (unsigned) xxx[1]<imagem->GetLargestPossibleRegion().GetSize()[1]){
				fprintf(fp, "%f %f %f ", imagem->GetPixel(xxx).GetRed()/255.0, imagem->GetPixel(xxx).GetGreen()/255.0, imagem->GetPixel(xxx).GetBlue()/255.0);
			}
			else{
				fprintf(fp, "%f %f %f ", 0.0, 0.0, 0.0);
			}
		}
	}
	
	
	fprintf(fp, "\n");
	//cerr << "Blue...";
	//cerr << "OK!" << endl;
	
	fclose(fp);
		
	return 0;
}


