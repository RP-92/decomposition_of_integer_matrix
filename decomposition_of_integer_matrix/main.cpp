// IOA matrix decomposition.cpp: Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "reader.h"; // lor archivos h solamente contienen definiciones, para que el compilador sepa que existen
// la implementacion va en un cpp que no se necesita incluir
#include "solver.h"
#include <iostream> // cosas de in out
#include <vector> // algo asi como arraylist

int main()
{
	std::cout << "Hello World!\n";
	// el operador :: es para ingresar a los miembros de una clase, cout es un metodo de la clase std
	// cout es para imprimir por pantalla, el << funciona igual que el + en java cuando usas println
	// \n es para hacer salto de linea

	std::vector< std::vector<int> > matrix = { {1, 3, 4}, {7, 2, 6} };
	// no se por que no me deja usar vector sin el std::, pero filo, esto es ver un arraylist
	// creo que los > > siempre deben ir separados por un espacio, pero no me cites por eso
	// en c++98 no se puede inicializar así, tienes que usar el constructor, pero estamos en c++11 :P

	std::cout << matrix[1][2] << "\n";
}