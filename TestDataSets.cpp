
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>


#include "vtkGNGGraph.h"
#include "vtkINGGraph.h"
#include "vtkENGGraph.h"

int main()
{
	std::string nameOfDataSet;
	std::string nameOfDataSetPath;
	std::string nameOfResultPath;

	//nameOfResultPath >> C:/dataset/

	std::cin >> nameOfDataSet;
	std::cin >> nameOfDataSetPath;
	std::cin >> nameOfResultPath;
	

	std::cout << (nameOfDataSetPath + nameOfDataSet + ".tra").c_str() << std::endl;
	std::cout << (nameOfDataSetPath + nameOfDataSet ".tes").c_str() << std::endl;
	std::cout << (nameOfResultPath + nameOfDataSet).c_str() << std::endl;

	std::ifstream inputDataSetTrain( (nameOfDataSetPath + nameOfDataSet + ".tra").c_str() );
	std::ifstream inputDataSetTest( (nameOfDataSetPath + nameOfDataSet ".tes").c_str() );
	std::ofstream outputTraining( (nameOfResultPath + nameOfDataSet).c_str() );

	
    clock_t start, end;

	int numberOfObjects,
		dimension,
		i,
		j;
	//compilar para cada datasets, modificando en point DIMENSION...
	
	inputDataSetTrain >> numberOfObjects;
	inputDataSetTrain >> dimension;

	
	stGNG* gng = stGNG::New();
	Point p(dimension);
	Point p1(dimension);
	Point p2(dimension);
	
	char coma;
	int countOfObjects = 0;
	
	for (i = 0; i < dimension - 1; i++) {
		inputDataSetTrain >> p1[i] >> coma;
	}
	inputDataSetTrain >> p1[i] ;

	for (i = 0; i < dimension - 1; i++) {
		inputDataSetTrain >> p2[i] >> coma;
	}
	inputDataSetTrain >> p2[i] ;

	gng->InsertNewUnits(p1, p2, 0);


	start = clock();
	while(!inputDataSetTrain.eof()) {
		for (i = 0; i < dimension - 1; i++) {
			inputDataSetTrain >> p[i] >> coma;
		}
		inputDataSetTrain >> p[i] ;
		gng->InsertNextPattern(p);
		countOfObjects++;
		if( ( numberOfObjects / 10) % countOfObjects == 0) {
			end = clock();
			outputTraining << numberOfDC << "\n";
			outputTraining << ((double )end-(double )start) / 1000.0 << "\n";
		}
	}
	
	return 0;
}