#ifndef _RGBTOHSV_H
#define _RGBTOHSV_H

#include <cmath>
#include <itkRGBPixel.h>
#include <itkImage.h>
#include <itkBinaryThresholdImageFilter.h>

#include "itkListSampleToHistogramGenerator.h"
#include "itkScalarImageToListAdaptor.h"

using namespace std;

class MaskGenerator {
public:
	#define MAX3(r,g,b) ((r)>(g)?((r)>(b)?(r):(b)):((g)>(b)?(g):(b)))
	#define MIN3(r,g,b) ((r)<(g)?((r)<(b)?(r):(b)):((g)<(b)?(g):(b)))
	#define MaskImageDimension 2
	//-------------------------Public Definitions----------------------
	typedef itk::RGBPixel< unsigned char > PixelType;
	typedef itk::Image< PixelType, MaskImageDimension > ImageType;
	typedef itk::Image< unsigned char, MaskImageDimension > MaskImageType;
	typedef itk::ImageRegion< MaskImageDimension > RegionType;
	typedef itk::Size< MaskImageDimension > SizeType;
	typedef itk::Index< MaskImageDimension > IndexType;
	typedef MaskGenerator* Pointer;
	typedef itk::BinaryThresholdImageFilter< MaskImageType, MaskImageType > ThresholdFilterType;
	//-------------------------Public Methods--------------------------
	MaskGenerator(); // ok
	~MaskGenerator(); // ok
	MaskImageType::Pointer GetOutput(); // ok
	void SetInput(ImageType::Pointer InputImage); // ok
	void SetMaxPixelValue(int value);
	void Update(); // ok
	static MaskGenerator::Pointer New(); // ok
	void SetThresholdValue(double v); // ok
	
	double thresholdValue;

private:
	ImageType::Pointer inputImage;
	MaskImageType::Pointer outputImage;
	MaskImageType::Pointer mask;
	int maxPixelValue, maxHistogramValue;
	bool externalThreshold;


	double pixelToHSV(PixelType pixel); // ok
	void generateOutput(); //
};

#endif
