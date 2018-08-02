//This program randomly splits data into training and testing data

#include <iostream>
#include <fstream>
#include <eigen3/Eigen/Eigen>
#include <string>
#include <algorithm>

using namespace std;

// Testing output file
ofstream qtest_out_file("./simOutData/testingData/qTest.txt");
ofstream dqtest_out_file("./simOutData/testingData/dqTest.txt");
ofstream ddqtest_out_file("./simOutData/testingData/ddqTest.txt");
ofstream torquetest_out_file("./simOutData/testingData/testTorque.txt");
ofstream mtest_out_file("./simOutData/testingData/M_Test.txt");
ofstream cgtest_out_file("./simOutData/testingData/CgTest.txt");
ofstream timetest_out_file("./simOutData/testingData/time_test.txt");

// Training output file
ofstream qtrain_out_file("./simOutData/trainingData/qTrain.txt");
ofstream dqtrain_out_file("./simOutData/trainingData/dqTrain.txt");
ofstream ddqtrain_out_file("./simOutData/trainingData/ddqTrain.txt");
ofstream torquetrain_out_file("./simOutData/trainingData/trainTorque.txt");
ofstream mtrain_out_file("./simOutData/trainingData/M_Train.txt");
ofstream cgtrain_out_file("./simOutData/trainingData/CgTrain.txt");
ofstream timetrain_out_file("./simOutData/trainingData/time_train.txt");

// Temporary data matrices
Eigen::MatrixXd qDataMat(2640,17);
Eigen::MatrixXd dqDataMat(2640,17);
Eigen::MatrixXd ddqDataMat(2640,17);
Eigen::MatrixXd torqueDataMat(2640,1);
Eigen::MatrixXd mDataMat(50160,17);
Eigen::MatrixXd cgDataMat(2640,17);
Eigen::MatrixXd timeDataMat(2640,1);

// int inc = 0;
int currLine = -1;
int col;

//Function Prototype
Eigen::MatrixXd extractDataToMat(string filename, int numRows, int numCols);

int main(){

	// Data matrix = extractDataToMat(input file path, #rows, #columns)
	qDataMat 		= extractDataToMat("./simOutData/qWaistData.txt", qDataMat.rows(), qDataMat.cols());
	dqDataMat 		= extractDataToMat("./simOutData/dqWaistData.txt", dqDataMat.rows(), dqDataMat.cols());
	ddqDataMat		= extractDataToMat("./simOutData/ddqWaistData.txt", ddqDataMat.rows(), ddqDataMat.cols());
	torqueDataMat 	= extractDataToMat("./simOutData/torqueWaistData.txt", torqueDataMat.rows(), torqueDataMat.cols());
	mDataMat 		= extractDataToMat("./simOutData/mWaistData.txt", mDataMat.rows(), mDataMat.cols());
	cgDataMat 		= extractDataToMat("./simOutData/cgWaistData.txt", cgDataMat.rows(), cgDataMat.cols());
	timeDataMat 	= extractDataToMat("./simOutData/timeWaistData.txt", timeDataMat.rows(), timeDataMat.cols());

	//Create array of 2640 numbers (# data points)
	int a[2640];
	//Assign array elements in order from 0 to 2640
	for (int num = 0; num < 2640; num++){
		a[num] = num;
	}
	//Shuffle the numbers in the array
	random_shuffle(begin(a), end(a));

	// cout << a[0] << endl;
	// cout << a[1] << endl;

	// //prints the first Matrix of the extracted M Matrix
	// for (int i = 0; i < 17; i++){
	// 	cout << mDataMat.row(i) << endl;
	// }
	// cout << qDataMat.row(0) << endl;

	int index;
	//Use first 500 numbers in a to access Matrix.row(index). Save in outfiles
	for (int i = 0; i < 500; i++){
		//save testing
		index = a[i];
		qtest_out_file 		<< qDataMat.row(index) 		<< endl;
		dqtest_out_file 	<< dqDataMat.row(index) 	<< endl;
		ddqtest_out_file 	<< ddqDataMat.row(index) 	<< endl;
		torquetest_out_file << torqueDataMat.row(index) << endl;
		// mtest_out_file 		<< mDataMat.row(index) 		<< endl;
		cgtest_out_file 	<< cgDataMat.row(index) 	<< endl;
		timetest_out_file 	<< timeDataMat.row(index) 	<< endl;
		for(int i = index*17; i < index*17+17; i++){
			mtest_out_file << mDataMat.row(i) << endl;
		}
		mtest_out_file << endl;
	}
	//Use last 2140 numbers in a to access Matrix.row(index). Save in outfiles
	for (int i = 500; i < 2640; i++){
		//save training
		index = a[i];
		qtrain_out_file 	 << qDataMat.row(index) 	 << endl;
		dqtrain_out_file 	 << dqDataMat.row(index)	 << endl;
		ddqtrain_out_file 	 << ddqDataMat.row(index)	 << endl;
		torquetrain_out_file << torqueDataMat.row(index) << endl;
		// mtrain_out_file 	 << mDataMat.row(index)	 	 << endl;
		cgtrain_out_file 	 << cgDataMat.row(index) 	 << endl;
		timetrain_out_file 	 << timeDataMat.row(index)	 << endl;
		for(int i = index*17; i < index*17+17; i++){
			mtrain_out_file << mDataMat.row(i) << endl;
		}
		mtrain_out_file << endl;
	}

	cout << "Done Saving" << endl;
}

Eigen::MatrixXd extractDataToMat(string filename, int numRows, int numCols){
	//Load data files into arrays for easy separation
	Eigen::MatrixXd tempDataMat(numRows,numCols);
	currLine = -1;
	string line;
	ifstream in_file(filename);
	std::string::size_type sz;
	while(getline(in_file, line)){
		//put data into MatrixXd array
		if(!line.empty()){
			currLine++;
			col = 0;
			stringstream lineStream(line);
			string t;
			while(getline(lineStream, t, ' ')){
				if(!t.empty()){
					if(!lineStream.eof()){
						//insert value into Matrix
						tempDataMat(currLine,col) = stod(t,&sz);
						col++;
					}
					else{
						//insert last value into Matrix
						tempDataMat(currLine,col) = stod(t,&sz);
						col++;
					}
				}
				else{//do nothing
				}
			}
		}
	}
	return tempDataMat;
}