#include <iostream>
#include <climits>
#include <string>
#include <cmath>
#include <doublefann.h>
#include <cstdlib>

using namespace std;

#define hit 0
#define miss 1
#define diff 2
#define diffMiss 3
#define squad 4
#define squadReal 5

struct fann_train_data* train;
double valid[3008][19226];

int main(int argc, char ** argv){ 
	if(argc < 3){
		cerr << "insuficient parameters." << endl;
		cerr << "\tSyntax: " << argv[0] << " <max_epochs> <neurons> < <validation file>" << endl;
		exit(1);
	}
	char *ptr;
	//network variables
	const unsigned int num_input = 19226;
	const unsigned int num_output = 21;
	const unsigned int num_layers = 3;
	const unsigned int num_neurons_hidden = atoi(argv[2]);
	const unsigned int max_epochs = atoi(argv[1]);
	const unsigned int epochs_between_reports = 0;
	const double desired_error = 0.0002;
	double neta = 0.3;
	double momentum = 0.2;
	double erroChacagem = 0.5;
	// data sets variables
	//--------------Carregando conjuntos de treinamento de validacao--------------
	cout << "Loading data...";
	train = fann_read_train_from_file("2500/dataPixTrain.txt");
	cout << "train set...";
	int validateNum = 1008;
	fann_type *output;
	double expected[validateNum][21];
	double validadeSet[6] = {0};
	double missVec[21][21] = {0};
	for( int k=0 ; k<validateNum ; k++ ){
		for(int j=0 ; j<num_input ; j++){
			cin >> valid[k][j];
		}
		for(int pp=0 ; pp<21 ; pp++){
			expected[k][pp]=0;
		}
		double modafoca;
		cin >> modafoca;
		expected[k][(int)(modafoca*20)]=1;
	}
	cout << "validation set...";
	cout << "OK!" << endl;
	//------------------------criando rede neural--------------------------------
	cout << "Creating artificial neural network with the following configuration:" << endl;
	cout << "\tinput layer size  = " << num_input << endl;
	cout << "\thidden layer size = " << num_neurons_hidden << endl;
	cout << "\toutput layer size = " << num_output << endl;
	cout << "\tnumber of layers  = " << num_layers << endl;
	cout << "\ttime between reports  = " << epochs_between_reports << endl;
	cout << "\tlearning rate     = " << neta << endl;
	cout << "\tmomentum          = " << momentum << endl;
	cout << "\tErro de validacao = " << erroChacagem << endl;
	cout << "Creating NN...";
	struct fann *ann = fann_create_standard(num_layers, num_input, num_neurons_hidden, num_output);
	fann_set_learning_momentum(ann, momentum);
	fann_set_learning_rate(ann, neta);
	fann_set_training_algorithm(ann, FANN_TRAIN_BATCH);
	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);
	cout << "OK!" << endl;
	//-----------------------Treinando rede neural------------------------------
	cout << "training network..." << endl;
//	for( int i=epochsPerNet ; i<=max_epochs ; i+=epochsPerNet ){
		cerr << "Treinando ate " << max_epochs << " epocas" << endl;
		fann_train_on_data(ann, train, max_epochs, epochs_between_reports, desired_error);
		cout << "Done!...Saving to file: ";
		char outputFile[100];
		sprintf(outputFile, "net/%dn%de.dat", num_neurons_hidden, max_epochs);
		fann_save(ann, outputFile);
		cout << outputFile << endl;
		//-------------------------Validando rede--------------------------------
		cout << "Validando...";
		validadeSet[hit] = 0;
		validadeSet[miss] = 0;
		validadeSet[diff] = 0;
		validadeSet[diffMiss] = 0;
		validadeSet[squad] = 0;
		validadeSet[squadReal] = 0;
		for(int kk = 0 ; kk<21 ; kk++){
			for(int jj=0 ; jj<21 ; jj++){
				missVec[kk][jj] = 0;
			}
		}
		for( int k=0 ; k<validateNum ; k++ ){
			output = fann_run(ann, valid[k]);
			int was = 0;
			int wegot = 0;
			for(int i=0 ; i<21 ; i++){
				if(expected[k][i]==1){
					was = i;
				}
				if(output[i]>output[wegot]){
					wegot = i;
				}
			}
			//for(int i=0 ; i<313 ; i++)
			//	xxx *= 10;
			if( was == wegot ){
				validadeSet[hit]++;
			}
			else{
				validadeSet[miss]++;
				validadeSet[diffMiss]+=wegot-was;
			}
			missVec[was][wegot]++;
			validadeSet[diff]+=wegot-was;
			validadeSet[squad] += (wegot-was)*(wegot-was);
		}
		cout << "OK!" <<endl;
		cout << "\tCorrectly Classified Instances:  " << validadeSet[hit] << " | " << validadeSet[hit]*100/validateNum  << endl;
		cout << "\tIncorrectly Classified Instances: " << validadeSet[miss] << " | " << validadeSet[miss]*100/validateNum << endl;
		cout << "\terro medio:  (" << validadeSet[diff] <<" / "<< validateNum <<") = "<< validadeSet[diff]/validateNum << endl;
		cout << "\terro medio das erradas: (" << validadeSet[diffMiss] <<" / "<< validadeSet[miss] <<") = " << validadeSet[diffMiss]/validadeSet[miss] << endl;
		cout << "\tmedia do desvio quadrado:  (" << validadeSet[squad] <<" / "<< validateNum <<") = " << validadeSet[squad]/validateNum << endl;
		cout << "\ta\tb\tc\td\te\tf\tg\th\ti\tj\tk\tl\tm\tn\to\tp\tq\tr\ts\tt\tu\t<-- classified as"<<endl;
		char abobora='a';
		float shudabe=0;
		for(int kk = 0 ; kk<21 ; kk++, abobora++, shudabe+=0.05){
			for(int jj=0 ; jj<21 ; jj++){
				cout << "\t" << missVec[kk][jj];
			}
			cout << " |   " << abobora << " = " << shudabe << endl;
		}
		cout << endl;
//	}
	fann_destroy(ann);
	return 0;
}
