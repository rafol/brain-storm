#include <iostream>
#include <climits>
#include <string>
#include <cmath>
#include <stdio.h>
#include <cstdlib>
#include <floatfann.h>

using namespace std;

#define hit 0
#define miss 1
#define diff 2
#define diffMiss 3

int main(int argc, char **argv){
	if(argc < 3){
		cerr << "insuficient parameters." << endl;
		cerr << "\tSyntax: " << argv[0] << " <input_file> <split_point> <max_epochs> <time_betwen_epochs>" << endl;
		exit(1);
	}
	int total = 3511;
	int splitPoint = atoi(argv[2]);
	int validate = total - splitPoint;
	FILE* inputFile = fopen(argv[1], "r");
	fann_type *output;
	fann_type input[total][26];
	float expected[total];
	int max = atoi(argv[3]);
	int inbetwen = atoi(argv[4]);
	char netFile[100];
	int bestEpoch = 0, bestResult = -1;
	// le os exemplos
	for( int i=0 ; i<total ; i++ ){
		for(int j=0 ; j<26 ; j++){
			fscanf(inputFile, "%f", &input[i][j]);
		}
		fscanf(inputFile, "%f", &expected[i]);
	}
	//int i=0;
	// testando as redes
	cerr << "Total: " << total << endl;
	cerr << "Split: " << splitPoint << endl;
	cerr << "validate: " << total-splitPoint << endl;
	cerr << "max: " << max << endl;
	for(int i=0 ; i<=max ; i+=inbetwen){
		// testa uma rede
		sprintf(netFile, "net/redeNeural%iepocas.dat", i);
		cerr << "running net: " << netFile << endl;
		struct fann *ann = fann_create_from_file(netFile);
		float trainSet[4] = {0};
		float validadeSet[4] = {0};
		// para os valores de treino
		for( int i=0 ; i<splitPoint ; i++ ){
			output = fann_run(ann, input[i]);
			if( expected[i] == *output ){
				trainSet[hit]++;
			}
			else{
				trainSet[miss]++;
				trainSet[diffMiss]+=*output-expected[i];
			}
			trainSet[diff]+=*output-expected[i];
		}
		cerr << "train stats: (abs | rel)" << endl;
		cerr << "\thit:  " << trainSet[hit] << " | " << trainSet[hit]/splitPoint << endl;
		cerr << "\tmiss: " << trainSet[miss] << " | " << trainSet[miss]/splitPoint << endl;
		cerr << "\terro medio:  " << trainSet[diff]/splitPoint << endl;
		cerr << "\terro medio das erradas: " << trainSet[diffMiss]/trainSet[miss] << endl;
		//para os valores de validacao
		for( int i=0 ; i<validate ; i++ ){
			for(int j=0 ; j<26 ; j++){
				fscanf(inputFile, "%f", &input[i][j]);
			}
			output = fann_run(ann, input[i]);
			fscanf(inputFile, "%i", &expected[i]);
			if( expected[i] == round(*output) ){
				validadeSet[hit]++;
			}
			else{
				validadeSet[miss]++;
				validadeSet[diffMiss]+=*output-expected[i];
			}
			validadeSet[diff]+=*output-expected[i];
		}
		cerr << "validate stats: (abs | rel)" << endl;
		cerr << "\thit:  " << validadeSet[hit] << " | " << validadeSet[hit]/validate << endl;
		cerr << "\tmiss: " << validadeSet[miss] << " | " << validadeSet[miss]/validate << endl;
		cerr << "\terro medio:  " << validadeSet[diff] << " | " << trainSet[diff]/validate << endl;
		cerr << "\terro medio das erradas: " << validadeSet[diffMiss] << " | " << validadeSet[diffMiss]/validadeSet[miss] << endl;

		//printf("xor test (%f,%f) -> %f\n", input[0], input[1], calc_out[0]);
		if(validadeSet[hit]>bestResult){
			bestEpoch = i;
			bestResult = validadeSet[hit];
		}
		fann_destroy(ann);
		cerr << endl;
	}
	cerr << "bestEpoch = " << bestEpoch << endl;
	cerr << "bestResult = " << bestResult << endl;
	return 0;
}
