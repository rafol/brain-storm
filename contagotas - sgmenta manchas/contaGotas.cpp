#include <iostream>
#include <climits>
#include <string>
#include <cmath>
#include <cstdlib>
#include <list>
#include <stdio.h>
#include <stdlib.h>

#include <itkRGBPixel.h>
#include <itkIndex.h>
#include <itkImageRegion.h>
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkBinaryThresholdImageFilter.h>
#include "MaskGenerator.h"
#include "RGBFilter.h"
#include "BlobExtractor.h"
#include <itkShiftScaleImageFilter.h>

using namespace std;

#define ImageDimension 2
#define PRETO 0
#define CINZAESQ 100
#define CINZACLR 200
#define BRANCO 255

//--------------------------TYPEDEFS ITK/VTK-------------------------------
typedef MaskGenerator::MaskImageType MaskType;
typedef RGBFilter::ChannelType ChannelType;
typedef itk::RGBPixel<unsigned char> PixelType;
typedef itk::Image< PixelType, ImageDimension > ImageType;
typedef itk::ImageFileReader< ImageType > ReaderType;
typedef itk::ImageFileWriter< ImageType > WriterType;
typedef itk::ImageFileWriter< MaskType > MaskWriterType;
typedef itk::Index< ImageDimension > IndexType;
typedef itk::ImageRegion< ImageDimension > RegionType;
typedef itk::ShiftScaleImageFilter< ImageType, ImageType > ScalerType;

MaskType::SizeType filledSize;
MaskType::IndexType filledIndex;

void floodFill(MaskType::Pointer image, IndexType seedIndex, unsigned char target, unsigned char repleace);

int main(int argc, char **argv) {
	//-----------------------Checking program call syntx------------------------
	if( argc < 7 ){
		cout << "Wrong arguments. Syntex:" << endl;
		cout << "\t" << argv[0] << " <input_file> <blobed_mask_file> <output_file_prefix> <output_file_offset> <output_file_postfix> <blob_ minimal_area> [Threshold_Value]" << endl;
		exit(1);
	}
	//----------------------------File Reading----------------------------------
	cerr << "Abrindo arquivo... ";
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(argv[1]); //le imagem stress do paciente
	reader->Update();
	ImageType::Pointer imagem = reader->GetOutput();
	cerr << "OK" << endl;
	//---------------------------Generating Mask--------------------------------
	cerr << "Gerando mascara para segmentacao...";
	MaskGenerator::Pointer maskGen = MaskGenerator::New();
	maskGen->SetInput(imagem);
	maskGen->SetMaxPixelValue(255);
	if(argc>7)	maskGen->SetThresholdValue(atof(argv[7]));
	maskGen->Update();
	MaskType::Pointer mask = maskGen->GetOutput();
	cerr << "OK!" << endl;
	//---------------------------Segmenting-------------------------------------
	cerr << "Segmentando...";		
	// find one blob
	ImageType::Pointer blob = ImageType::New();
	MaskType::SizeType maskSize = mask->GetLargestPossibleRegion().GetSize();	
	MaskType::IndexType maskIndex = mask->GetLargestPossibleRegion().GetIndex();
	int i=0, small = 0;
	for( maskIndex[0] = mask->GetLargestPossibleRegion().GetIndex()[0] ; maskIndex[0]< (int) maskSize[0] ; maskIndex[0]++ ){
		for( maskIndex[1] = mask->GetLargestPossibleRegion().GetIndex()[1] ; maskIndex[1]< (int) maskSize[1] ; maskIndex[1]++ ){
			//maskIndex[0]=105;
			//maskIndex[1]=128;
			if( mask->GetPixel(maskIndex) == BRANCO ){
				filledSize[0] = 1;
				filledSize[1] = 1;
				filledIndex[0] = maskIndex[0];
				filledIndex[1] = maskIndex[1];
				floodFill(mask, maskIndex, BRANCO, CINZACLR); // tbm tme que determinar a regiao
				//cout<< "fillindex: " << filledIndex <<endl;
				//cout<< "fillsize:  " << filledSize <<endl;
				if( filledSize[0] * filledSize[1] < (unsigned) atoi(argv[6]) ){ // gota é muito pequena e deve ser desconsiderada
					floodFill(mask, maskIndex, CINZACLR, CINZAESQ);
					small++;
					continue;
				}
				// gota encontrada e marcada, regiao delimitada
				// blob image allocation			
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
							blob->SetPixel(destnyIndex, imagem->GetPixel(sourceIndex));
							mask->SetPixel(sourceIndex, CINZAESQ);
						}
						else{
							blob->GetPixel(destnyIndex).SetRed(PRETO);
							blob->GetPixel(destnyIndex).SetGreen(PRETO);
							blob->GetPixel(destnyIndex).SetBlue(PRETO);
							//blob->SetPixel(destnyIndex, imagem->GetPixel(sourceIndex));
						}
					}
				}
				i++;
				//cout << "found blob " << ++i;
				// gravando blob
				WriterType::Pointer writer = WriterType::New();					
				char blobId[10];
				sprintf(blobId, "%d", i+atoi(argv[4]));
				//nome do arquivo
				string outName = argv[3];
				outName += blobId;
				outName += argv[5];
				// gravando
				writer->SetFileName(outName);
				writer->SetInput(blob);
				try{
					writer->Update();
				} catch (int x) {
				}
				//cout<<" ... gravado com nome: \"" << outName << "\"" << endl << endl;
				//goto there;
			}
			
		}
	}
	//there:
	
	cerr << "OK!" << endl;
	cout << "\tGotas encontradas: " << i << endl;
	cout << "\tGotas ignoradas:   " << small << endl;
	//-------------------------Writing output files-----------------------------
	MaskWriterType::Pointer maskWriter = MaskWriterType::New();
	maskWriter->SetFileName(argv[2]);
	maskWriter->SetInput(mask);
	cerr << "Writing output file...";
	try {
		maskWriter->Update();
	} catch (int x) {
	}
	cerr << "OK!" <<endl;
	cerr << "ultima gota gravada: " << i+atoi(argv[4]) << endl<<endl;
	//cout << "ultima gota gravada: " << i+atoi(argv[4]) << endl<<endl;
	return 0;
}


void floodFill(MaskType::Pointer image, IndexType seedIndex, unsigned char target, unsigned char repleace){
	if( image->GetPixel(seedIndex) == target ){
		image->SetPixel(seedIndex, repleace);
		if(seedIndex[0] < filledIndex[0]){
			filledSize[0]++;
			filledIndex[0] = seedIndex[0];
		}
		if(seedIndex[0] > (int) (filledIndex[0] + filledSize[0] - 1) ){
			filledSize[0]++;
		}		
		if(seedIndex[1] < filledIndex[1]){
			filledSize[1]++;
			filledIndex[1] = seedIndex[1];
		} 
		if(seedIndex[1] > (int) (filledIndex[1] + filledSize[1] - 1) ){
			filledSize[1]++;
		}
		seedIndex[0] +=1;
		floodFill(image, seedIndex, target, repleace);
		seedIndex[0] -=2;
		floodFill(image, seedIndex, target, repleace);
		seedIndex[0] +=1;
		seedIndex[1] +=1;
		floodFill(image, seedIndex, target, repleace);
		seedIndex[1] -=2;
		floodFill(image, seedIndex, target, repleace);
	}
}
