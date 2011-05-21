#include "RGBFilter.h"

RGBFilter::RGBFilter(){ };


RGBFilter::~RGBFilter(){ };


RGBFilter::ImageType::Pointer RGBFilter::GetOutput(){
	this->Update();
	return this->outputImage;
}

void RGBFilter::SetInput(ImageType::Pointer InputImage){
	this->inputImage = InputImage;
	// output image allocation
	this->outputImage = ImageType::New();
	ImageType::IndexType outputIndex;
	outputIndex.Fill(0);
	RegionType anotherRegion;
	anotherRegion.SetIndex(outputIndex);
	anotherRegion.SetSize(this->inputImage->GetLargestPossibleRegion().GetSize());
	outputImage->SetLargestPossibleRegion(anotherRegion);
	outputImage->SetBufferedRegion(anotherRegion);
	outputImage->SetRequestedRegion(anotherRegion);
	outputImage->Allocate();
	
	
	this->ImRed = ChannelType::New();
	ChannelType::IndexType outputIndex2;
	outputIndex2.Fill(0);
	RegionType anotherRegion2;
	anotherRegion2.SetIndex(outputIndex2);
	anotherRegion2.SetSize(this->inputImage->GetLargestPossibleRegion().GetSize());
	ImRed->SetLargestPossibleRegion(anotherRegion2);
	ImRed->SetBufferedRegion(anotherRegion2);
	ImRed->SetRequestedRegion(anotherRegion2);
	ImRed->Allocate();
	
	this->ImGreen = ChannelType::New();
	ChannelType::IndexType outputIndex3;
	outputIndex3.Fill(0);
	RegionType anotherRegion3;
	anotherRegion3.SetIndex(outputIndex3);
	anotherRegion3.SetSize(this->inputImage->GetLargestPossibleRegion().GetSize());
	ImGreen->SetLargestPossibleRegion(anotherRegion3);
	ImGreen->SetBufferedRegion(anotherRegion3);
	ImGreen->SetRequestedRegion(anotherRegion3);
	ImGreen->Allocate();

	this->ImBlue = ChannelType::New();
	ChannelType::IndexType outputIndex4;
	outputIndex4.Fill(0);
	RegionType anotherRegion4;
	anotherRegion4.SetIndex(outputIndex4);
	anotherRegion4.SetSize(this->inputImage->GetLargestPossibleRegion().GetSize());
	ImBlue->SetLargestPossibleRegion(anotherRegion4);
	ImBlue->SetBufferedRegion(anotherRegion4);
	ImBlue->SetRequestedRegion(anotherRegion4);
	ImBlue->Allocate();
}

void RGBFilter::Update(){
	SizeType inputImageSize = this->inputImage->GetLargestPossibleRegion().GetSize();
	IndexType index;
	for (index[0] = 0; (long) index[0] < (long) inputImageSize[0]; index[0]++) {
		for (index[1] = 0; (long) index[1] < (long) inputImageSize[1]; index[1]++) {
			this->ImRed->SetPixel(   index, this->inputImage->GetPixel(index).GetRed() );
			this->ImGreen->SetPixel( index, this->inputImage->GetPixel(index).GetGreen() );
			this->ImBlue->SetPixel(  index, this->inputImage->GetPixel(index).GetBlue() );
		}
	}
}

RGBFilter::ChannelType::Pointer RGBFilter::GetRed(){
	return this->ImRed;
}

RGBFilter::ChannelType::Pointer RGBFilter::GetGreen(){
	return this->ImGreen;
}

RGBFilter::ChannelType::Pointer RGBFilter::GetBlue(){
	return this->ImBlue;
}
