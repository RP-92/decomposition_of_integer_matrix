#include "solver.h"
#include <iostream>

using namespace std;

void decompose( vector< vector<int> >& matrix ){
	std::cout << "In decompose!\n\n";

	// actual code
	vector< vector<int> > diffMatrix, p_lists, l_lists;

	diffMatrix.reserve( matrix.size() );
	for( int row = 0; row < matrix.size(); row++ ){
		diffMatrix[row].reserve(matrix[0].size()+1);
	}

	// genera la matriz de diferencia
	for(int row = 0; row < matrix.size(); row++){
		vector<int> newVector;
		for( int column = 0; column < matrix[0].size() + 1; column++ ){
			if( column == 0){
				newVector.push_back( matrix[row][column] - matrix[row][column + 2] );
			}
			else{
				if( column == matrix[0].size() ){
					newVector.push_back( -matrix[row][column - 1] );
				}
				else{
					newVector.push_back( matrix[row][column] - matrix[row][column - 1] );
				}
			}
		}
		diffMatrix.push_back(newVector);
	}

	// muestra la matriz de diferencia
	std::cout << "difference matrix:\n";
	for(int row = 0; row < matrix.size(); row++){
		vector<int> newVector;
		for( int column = 0; column < matrix[0].size() + 1; column++ ){
			std::cout << diffMatrix[row][column] << " ";
		}
		std::cout << "\n";
	}


	// genera las listas P y Q
	vector< vector<int> > P_lists, Q_lists;
	P_lists.reserve( matrix.size() );
	Q_lists.reserve( matrix.size() );
	for(int row = 0; row < diffMatrix.size(); row++){
		vector<int> newP_list, newQ_list;
		for( int column = 0; column < diffMatrix[0].size(); column++ ){
			if( diffMatrix[row][column] > 0 ){
				newP_list.push_back( column + 1 );
			}
			if( diffMatrix[row][column] < 0 ){
				newQ_list.push_back( column + 1 );
			}
		}
		P_lists.push_back( newP_list );
		Q_lists.push_back( newQ_list );
	}

	// muestra el contenido de las listas P y !
	for( int row = 0; row < P_lists.size(); row++ ){
		std::cout << "P" << row+1 << "= ";
		for( int column = 0; column < P_lists[row].size(); column++ ){
			std::cout << P_lists[row][column] << " ";
		}
		std::cout << "\n";
	}
	for( int row = 0; row < Q_lists.size(); row++ ){
		std::cout << "Q" << row+1 << "= ";
		for( int column = 0; column < Q_lists[row].size(); column++ ){
			std::cout << Q_lists[row][column] << " ";
		}
		std::cout << "\n";
	}

	// algoritmo 2.1

	// algoritmo 2.2
	vector< vector< vector<int> > > decomposition; //dimension 1: número de la matriz, dim 2 y 3, la matriz en cuestión
	vector<int> coeficients;

	vector< vector<int> > alfas;
	vector< vector< vector<int> > > L; //1era dim: filas; dim 2: numero de intervalo en esa fila; dim 3 inicio y fin de intervalo
	int k = 0;
	//for( int i= 0; i<10; i++ ){ este for es para hacerlo correr en caso de fallar la condicion del while
	while( matrixIsOccupied( matrix ) ){
		k++;

		vector< vector<int> > Y;
		vector<int> alfa_per_row;

		// elegir Im y generar Yk
		for( int row = 0; row < matrix.size(); row++ ){
			vector<int> newRow;
			if( L[row].size() == 0 ){
				for( int column = 0; column < matrix[0].size(); column++ ){
					newRow.push_back(0);
					alfa_per_row.push_back(-1);
				}
			}
			else{
				for( int column = 0; column < matrix[0].size(); column++ ){
					if( column+1 < L[row][0][0] || column+1 >= L[row][0][1] ){newRow.push_back(0);}
					else{newRow.push_back(1);}
				}
				alfa_per_row.push_back(alfas[row][0]);
			}
			Y.push_back(newRow);
		}

		// minimizar el alfa
		int alfa = -1;
		for( int row = 0; row < matrix.size(); row++ ){
			if( alfa_per_row[row] > 0 ){
				if( alfa == -1){alfa = alfa_per_row[row];}
				else{
					if(alfa > alfa_per_row[row]){alfa = alfa_per_row[row];}
				}
			}
		}

		// A = A - alfa*Y
		for( int row = 0; row < matrix.size(); row++){
			for( int column = 0; column.size(); column++ ){
				matrix[row][column] = matrix[row][column] - alfa*Y[row][column];
			}
		}

		// Agregar Y a la solucion final, lo mismo el alfa
		decomposition.push_back(Y);
		coeficients.push_back(alfa);

		// re-calcular los alfa
		for( int row = 0; row < matrix.size(); row++ ){
			alfas[row][0] = alfas[row][0] - alfa;
		// Eliminar los intervalos y alfa que no son necesarios ya
			if( alfas[row][0] == 0 ){
				alfas[row].erase(0);
				L[row].erase(0);
			}
		}
	}
	return;
}

bool rowIsOccupied( vector<int>& row ){
	for( int column = 0; column < row.size(); column++ ){
		if( row[column] != 0 ){
			return true;
		}
	}
	return false;
}

bool matrixIsOccupied( vector< vector<int> >& matrix ){
	for( int row = 0; row < matrix.size(); row++ ){
		for( int column = 0; column < matrix[0].size(); column++ ){
			if( matrix[row][column] != 0 ){
				return true;
			}
		}
	}
	return false;
}