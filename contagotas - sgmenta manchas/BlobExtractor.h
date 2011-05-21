#ifndef _BLOBEXTRACTOR_H
#define _BLOBEXTRACTOR_H

#include <itkRGBPixel.h>
#include <itkIndex.h>
#include <itkImageRegion.h>
#include <itkImage.h>
using namespace std;

class BlobExtractor{
public:
	#define MaskImageDimension 2
	#define PRETO 0
	#define CINZAESQ 100
	#define CINZACLR 200
	#define BRANCO 255
	//-------------------------Public Definitions----------------------
	typedef itk::RGBPixel< unsigned char > PixelType;
	typedef itk::Image< PixelType, MaskImageDimension > ImageType;
	typedef itk::Image< unsigned char, MaskImageDimension > MaskType;
	typedef itk::ImageRegion< MaskImageDimension > RegionType;
	typedef itk::Size< MaskImageDimension > SizeType;
	typedef itk::Index< MaskImageDimension > IndexType;
	typedef BlobExtractor* Pointer;
	//-------------------------Public Methods--------------------------
	BlobExtractor(); 
	~BlobExtractor();
	ImageType::Pointer GetNextBlob(); 
	void SetInput(ImageType::Pointer inputImage); 
	void SetMask(MaskType::Pointer mask); 
	static BlobExtractor::Pointer New(); 
	ImageType::Pointer GetCurrentBlob();
	bool  IsEndOfImage();
private:
	ImageType::Pointer inputImage;
	ImageType::Pointer blob;
	MaskType::Pointer mask;
	SizeType maskSize, filledSize;
	IndexType maskIndex, filledIndex;
	bool endOfImage;
	
	void floodFill(IndexType seedIndex, unsigned char target, unsigned char repleace);
	void Setup();
	
};
#endif
