#include "solver.h"
#include <iostream>

using namespace std;

void decompose( vector< vector<int> >& matrix ){
	std::cout << "In decompose!\nMatrix value in [1][1]: " << matrix[1][1] << "\n";

	// actual code
	vector< vector<int> > diffMatrix;

	diffMatrix.reserve( matrix.size() );
	for( int row = 0; row < matrix.size(); row++ ){
		diffMatrix[row].reserve(matrix[0].size());
	}

	std::cout << "difference matrix:\n";
	for(int row = 0; row < matrix.size(); row++){
		for( int column = 0; column < matrix[0].size(); column++ ){
			if( column == 0){
				diffMatrix[row][column] = matrix[row][column + 1];
			}
			else{
				diffMatrix[row][column] = matrix[row][column] - matrix[row][column - 1];
			}
			std::cout << diffMatrix[row][column] << " ";
		}
		std::cout << "\n";
	}


	return;
}