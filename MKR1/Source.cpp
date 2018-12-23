#include <iostream>
#include "Matrix.h"	// Бiблiотека роботи з матрицями

using namespace std;

int main()
{
	system("chcp 1251 & cls");
	Matrix matrix;

	cout << "Початокова матриця:\n";
	matrix.print();

	matrix.determinant();

	cout << "Детермiнант 1 способом: " << matrix.D << endl;
	cout << "Кiлькiсть операцiй: " << matrix.k << endl << endl;

	matrix.init();
	matrix.optimalException();

	//matrix.print();
	cout << "Детермiнант 2 способом: " << matrix.D << endl;
	cout << "Кiлькiсть операцiй: " << matrix.k << "\n\n\n";


	matrix.init();
	matrix.swapl();
	cout << "Додаткове завдання, змiнена матриця:\n";
	matrix.print();
	matrix.determinant();
	cout << "Детермiнант змiненої матрицi 1 способом: " << matrix.D << endl;
	cout << "Кiлькiсть операцiй: " << matrix.k << endl << endl;

	matrix.init();
	matrix.swapl();
	matrix.optimalException();
	cout << "Детермiнант змiненої матрицi 2 способом: " << matrix.D << endl;
	cout << "Кiлькiсть операцiй: " << matrix.k << endl << endl;
	getchar();
}
