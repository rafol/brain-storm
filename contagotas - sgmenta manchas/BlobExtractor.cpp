#include "BlobExtractor.h"


BlobExtractor::BlobExtractor(){
	this->inputImage = NULL;
	this->mask = NULL;
	this->blob = NULL;
}

BlobExtractor::~BlobExtractor(){
}

BlobExtractor::ImageType::Pointer BlobExtractor::GetNextBlob(){
	for( ; maskIndex[0]< (int) maskSize[0] ; maskIndex[0]++ ){
		for(  ; maskIndex[1]< (int) maskSize[1] ; maskIndex[1]++ ){
			//maskIndex[0] = 127;
			//maskIndex[1] = 131;
			if( mask->GetPixel(maskIndex) == BRANCO ){
				filledSize[0] = 1;
				filledSize[1] = 1;
				filledIndex[0] = maskIndex[0];
				filledIndex[1] = maskIndex[1];
				floodFill(maskIndex, BRANCO, CINZACLR); // tbm tme que determinar a regiao
				// gota encontrada e marcada, regiao delimitada
				// blob image allocation		
				ImageType::Pointer blob = ImageType::New();	
				ImageType::IndexType blobIndex;
				blobIndex.Fill(0);
				ImageType::RegionType blobRegion;
				blobRegion.SetIndex(blobIndex);
				blobRegion.SetSize(filledSize);
				blob->SetLargestPossibleRegion(blobRegion);
				blob->SetBufferedRegion(blobRegion);
				blob->SetRequestedRegion(blobRegion);
				blob->Allocate();
				// blob crop (elimina potenciais residuos externos a gota)
				IndexType sourceIndex = filledIndex;
				IndexType destnyIndex = blobIndex;
				
				for( sourceIndex[0] = filledIndex[0], destnyIndex[0] = blobIndex[0] ; sourceIndex[0]< (int) (filledSize[0] + filledIndex[0]) ; sourceIndex[0]++, destnyIndex[0]++  ){
					for( sourceIndex[1] = filledIndex[1], destnyIndex[1] = blobIndex[1] ; sourceIndex[1]< (int) (filledSize[1] + filledIndex[1]) ; sourceIndex[1]++, destnyIndex[1]++  ){
						if( mask->GetPixel(sourceIndex) == CINZACLR ){
							blob->SetPixel(destnyIndex, this->inputImage->GetPixel(sourceIndex));
							mask->SetPixel(sourceIndex, CINZAESQ);
						}
						else{
							blob->GetPixel(destnyIndex).SetRed(PRETO);
							blob->GetPixel(destnyIndex).SetGreen(PRETO);
							blob->GetPixel(destnyIndex).SetBlue(PRETO);
						}
					}
				}
				goto THERE;
			}
			
		}
		maskIndex[1] = mask->GetLargestPossibleRegion().GetIndex()[1];
	}
	this->endOfImage = true;
	THERE:
	if(endOfImage) return NULL;
	else 				return blob;
}


void BlobExtractor::floodFill(BlobExtractor::IndexType seedIndex, unsigned char target, unsigned char repleace){
	cout << seedIndex << " " << (int) this->mask->GetPixel(seedIndex) << " ";
	if( this->mask->GetPixel(seedIndex) == target ){
		cout<<"M";
		this->mask->SetPixel(seedIndex, repleace);
		cout << " " << (int) this->mask->GetPixel(seedIndex) << endl;
		if(seedIndex[0] < filledIndex[0]){
			filledSize[0]++;
			filledIndex[0] = seedIndex[0];
		}else{
			if(seedIndex[0] > (int) (filledIndex[0] + filledSize[0]) ){
				filledSize[0]++;
			}else{
				if(seedIndex[1] < filledIndex[1]){
					filledSize[1]++;
					filledIndex[1] = seedIndex[1];
				}else{		
					if(seedIndex[1] > (int) (filledIndex[1] + filledSize[1]) ){
						filledSize[1]++;
					}
				}
			}
		}
		seedIndex[0] +=1;
		floodFill(seedIndex, target, repleace);
		seedIndex[0] -=2;
		floodFill(seedIndex, target, repleace);
		seedIndex[0] +=1;
		seedIndex[1] +=1;
		floodFill(seedIndex, target, repleace);
		seedIndex[1] -=2;
		floodFill(seedIndex, target, repleace);
		return;
	}
	cout<<"s"<<endl;
}


BlobExtractor::ImageType::Pointer BlobExtractor::GetCurrentBlob(){
	return blob;
}

void BlobExtractor::SetInput(ImageType::Pointer inputImage){
	this->inputImage = inputImage;
	this->Setup();
}

void BlobExtractor::SetMask(MaskType::Pointer mask){
	this->mask = mask;
	this->Setup();
}

BlobExtractor::Pointer BlobExtractor::New(){
	return new BlobExtractor();
}

void BlobExtractor::Setup(){
	if( this->inputImage && this->mask ){
		this->maskSize = this->mask->GetLargestPossibleRegion().GetSize();
		this->maskIndex = this->mask->GetLargestPossibleRegion().GetIndex();
		this->filledSize.Fill(0);
		this->filledIndex.Fill(0);
		this->endOfImage = false;
	}
}

bool  BlobExtractor::IsEndOfImage(){
	return this->endOfImage;

}

