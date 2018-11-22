#include "solver.h"
#include <iostream>

using namespace std;

void decompose( vector< vector<int> >& matrix ){
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
				//if( matrix[row][column] == 0 ){
				//	newVector.push_back( 0 );
				//}
				//else{
				newVector.push_back( matrix[row][column] );
				//}
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
	std::cout << "Difference matrix:\n";
	for(int row = 0; row < matrix.size(); row++){
		vector<int> newVector;
		for( int column = 0; column < matrix[0].size() + 1; column++ ){
			std::cout << diffMatrix[row][column] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";


	// genera las listas P y Q
	vector< vector<int> > P_lists, Q_lists;
	P_lists.reserve( matrix.size() );
	Q_lists.reserve( matrix.size() );
	for(int row = 0; row < diffMatrix.size(); row++){
		vector<int> newP_list, newQ_list;
		for( int column = 0; column < diffMatrix[0].size(); column++ ){
			if( diffMatrix[row][column] > 0 ){
				newP_list.push_back( column );
			}
			if( diffMatrix[row][column] < 0 ){
				newQ_list.push_back( column );
			}
		}
		P_lists.push_back( newP_list );
		Q_lists.push_back( newQ_list );
	}

	// muestra el contenido de las listas P y !
	for( int row = 0; row < P_lists.size(); row++ ){
		std::cout << "P" << row+1 << "= ";
		for( int column = 0; column < P_lists[row].size(); column++ ){
			std::cout << P_lists[row][column]+1 << " ";
		}
		std::cout << "\n";
	}
	for( int row = 0; row < Q_lists.size(); row++ ){
		std::cout << "Q" << row+1 << "= ";
		for( int column = 0; column < Q_lists[row].size(); column++ ){
			std::cout << Q_lists[row][column]+1 << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";

	// algoritmo 2.1
	vector< vector<int> > alfas;

	vector< vector< vector<int> > > L; //1era dim: filas; dim 2: numero de intervalo en esa fila; dim 3 inicio y fin de intervalo
	int alpha = 0;
	int actual_k = 0;
	//Tomo la fila m, y a cada columna k se selecciona un alfa con el mínimo entre a_r y a_l
	for(int row =0; row<matrix.size(); row++) {
		vector<int> Ks;
		vector<int> actual_row = matrix[row]; //entra la fila
		vector< vector<int> > intervalos;
		L.push_back(intervalos);
		alfas.push_back(Ks);

		while (rowIsOccupied(actual_row) ) {
			actual_k++;
			vector <int> intervalo = {P_lists[row][0],Q_lists[row][0]};//saco la posición inicial de los listados
			L[row].push_back(intervalo);
			std::cout << "intervalo agregado: [" << intervalo[0]+1 << ", " << intervalo[1]+1 << " )\n";

			int l = intervalo[0];
			int r = intervalo[1];

			alpha = diffMatrix[row][l];
			if( -diffMatrix[row][r] < alpha ){
				alpha = -diffMatrix[row][r];
			}
			std::cout << "New alpha value for row " << row+1 << ": " << alpha << "\n";

			alfas[row].push_back(alpha);
			for(int i=l;i<r;i++){ //recorro restando a-alpha en el intervalo Ym
				actual_row[i]-=alpha;
			}

			if( rowIsOccupied(actual_row) == false ) break;
			if( alpha == diffMatrix[row][l] || 0 == actual_row[l] ){
				P_lists[row].erase(P_lists[row].begin());
			}
			if( alpha == -diffMatrix[row][r] || 0 == actual_row[r] ){
				Q_lists[row].erase(Q_lists[row].begin());
			}

			diffMatrix[row][l] -= alpha;
			diffMatrix[row][r] += alpha;
		}
		std::cout << "\n";
	}

		std::cout << "\n";
	for( int row = 0; row < L.size(); row++ ){
		std::cout << "L" << row+1 << ":\n";
		for(int interval = 0; interval < L[row].size(); interval++ ){
			std::cout << "[" << L[row][interval][0]+1 << ", " << L[row][interval][1]+1 << ") ";
		}
		std::cout << "\n";
	}
		std::cout << "\n";

	// algoritmo 2.2
	vector< vector< vector<int> > > decomposition; //dimension 1: número de la matriz, dim 2 y 3, la matriz en cuestión
	vector<int> coeficients;

	int k = 0;
	while( matrixIsOccupied( matrix) ){
		k++;

		vector< vector<int> > Y;
		vector<int> alfa_per_row;

		// elegir Im y generar Yk
		std::cout << "Y" << k << ":\n";
		for( int row = 0; row < matrix.size(); row++ ){
			vector<int> newRow;
			std::cout << "| ";
			if( L[row].size() == 0 ){
				alfa_per_row.push_back(-1);
				for( int column = 0; column < matrix[0].size(); column++ ){
					newRow.push_back(0);
					std::cout << "0 ";
				}
			}
			else{
				for( int column = 0; column < matrix[0].size(); column++ ){
					if( column >= L[row][0][0] && column < L[row][0][1] ){
						newRow.push_back(1);
						std::cout << "1 ";
					}
					else{
						newRow.push_back(0);
						std::cout << "0 ";}
				}
				alfa_per_row.push_back(alfas[row][0]);
			}
			Y.push_back(newRow);
			std::cout << "| \n";
		}

		// minimizar el alfa
		int alfa = -1;
		for( int row = 0; row < matrix.size(); row++ ){
			if( alfa_per_row[row] > 0 ){
				if( alfa == -1 ){alfa = alfa_per_row[row]; }
				if(alfa > alfa_per_row[row] && alfa > 0){
					alfa = alfa_per_row[row];
				}
			}
		}
		std::cout << "alpha: " << alfa << "\n\n";

		// A = A - alfa*Y
		for( int row = 0; row < matrix.size(); row++){
			for( int column = 0; column < matrix[0].size(); column++ ){
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
				alfas[row].erase(alfas[row].begin());
				L[row].erase(L[row].begin());
			}
		}
	}

	std::cout << "Number of matrices: " << k << "\n";
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