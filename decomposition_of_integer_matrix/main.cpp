// IOA matrix decomposition.cpp: Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream> // cosas de in out
#include <vector> // algo asi como arraylist
#include "reader.h" // lor archivos h solamente contienen definiciones, para que el compilador sepa que existen
// la implementacion va en un cpp que no se necesita incluir
#include "solver.h"

using namespace std;

int main()
{
	cout << "Hello World!\n";
	// std es un clase y cout un "método" de ella, esto debería escribirse std::cout... pero al haber usado "using namespace std" esto se simplifica
	// técnicamente no lo es, pero para nuestros propósitos si
	// la explicación es enredada y la sintáxis es diferente a la de un método en c++ (que es igual a java), pero sencilla
	// Hay tres tipos de operadores de acceso a las clases
	// :: es para clases, . es para objetos y -> es para punteros a objetos
	// Cout es para imprimir por pantalla, el << funciona igual que el + en java cuando usas System.out.println()
	// \n es para hacer salto de linea, debe ir dentro de doble comillas como si fuese texto.

	vector< vector<int> > matrix = { {1, 3, 4}, {7, 2, 6} };
	// no se por que no me deja usar vector sin el std::, pero filo, esto es ver un arraylist
	// creo que los > > siempre deben ir separados por un espacio, pero no me cites por eso
	// en c++98 no se puede inicializar así, tienes que usar el constructor, pero estamos en c++11 :P

	cout << "Matrix in [1][2]: " << matrix[1][2] << "\n" << "Matrix size = " << matrix.size() << "x" << matrix[0].size() << "\n";

	decompose( matrix );
}

