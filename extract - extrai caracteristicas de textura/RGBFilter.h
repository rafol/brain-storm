#ifndef _RGBFILTER_H
#define _RGBFILTER_H

#include <itkRGBPixel.h>
#include <itkImage.h>
#include <cmath>

using namespace std;

class RGBFilter{
public:
	#define MaskImageDimension 2
	//-------------------------Public Definitions----------------------
	typedef itk::RGBPixel< unsigned char > PixelType;
	typedef itk::Image< PixelType, MaskImageDimension > ImageType;
	typedef itk::Image< unsigned char, MaskImageDimension > ChannelType;
	typedef itk::ImageRegion< MaskImageDimension > RegionType;
	typedef itk::Size< MaskImageDimension > SizeType;
	typedef itk::Index< MaskImageDimension > IndexType;
	typedef RGBFilter* Pointer;
	
	RGBFilter();
	~RGBFilter();
	ImageType::Pointer GetOutput();
	void SetInput(ImageType::Pointer InputImage);
	void Update();
	ChannelType::Pointer GetRed();
	ChannelType::Pointer GetGreen();
	ChannelType::Pointer GetBlue();
	ChannelType::Pointer ImRed, ImGreen, ImBlue;

private:
	ImageType::Pointer inputImage;
	ImageType::Pointer outputImage;
};

#endif

