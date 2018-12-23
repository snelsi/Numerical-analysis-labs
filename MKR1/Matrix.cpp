#include <algorithm>
#include <iostream>
#include <iomanip>
#include "Matrix.h"

using namespace std;

// Iнiцiалuзацiя матрицi / вiдновлення початкових значень
void Matrix::init() {
	a[0][0] = 3;	a[0][1] = 0;	a[0][2] = 67;	a[0][3] = 7;	b[0] = 6;
	a[1][0] = 10;	a[1][1] = 1;	a[1][2] = 12;	a[1][3] = 3;	b[1] = 3;
	a[2][0] = 8;	a[2][1] = 4;	a[2][2] = 5;	a[2][3] = 1;	b[2] = 3;
	a[3][0] = 5;	a[3][1] = 2;	a[3][2] = 98;	a[3][3] = 80;	b[3] = 9;
}


// Вивiд матрицi на екран
void Matrix::print() {
	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < n; j++) 
		{
			cout << setw(4) << setprecision(3) << a[i][j] << "  ";
		}
		cout << " =   " << b[i] << endl;
	}
	cout << endl;
}

// Рекурсивний перебiр множникiв матрицi
void Matrix::reshuffle()
{
	if (pos >= n)
	{
		int multiplier = 1;	// Добуток множникiв матрицi
		for (int i = 0; i < n; i++) {
			// Перевiрка кiлькостi "Безладiв"
			for (int j = i + 1; j < n; j++) {
				if (var[i] > var[j]) {
					multiplier *= -1;
					k++;
				}
			}
			// Домноження поточного члена до добутку
			multiplier *= a[i][var[i] - 1];
			k++;
		}
		D += multiplier;	// Додання добутку до детермiнанту
		k++;
		return;
	}
	else
	{
		for (int i = pos; i < n; i++)
		{	// Перестановка множникiв, рекурсiя
			swap(var[i], var[pos++]);
			reshuffle();
			swap(var[i], var[--pos]);
		}
	}
}

// Визначення детермiнанту
void Matrix::determinant() {
	k = D = 0;
	for (int i = 1; i <= n; i++) {
		var[i - 1] = i;
	}
	reshuffle(); // Перебiр множникiв
}


void Matrix::optimalException() {
	// Basic cases
	if (n <= 0) { D = -1; return; }
	if (n == 1) { D = a[0][0]; return; }
	if (n == 2) { D = a[0][0] * a[1][1] - a[0][1] * a[1][0]; return; }

	float koef;	// temporary multiplier

	D = 1;

	// Optimal exclusion method
	// Reducing matrix to identity
	for (int l = 0; l < n; l++)
	{
		// First step, subtraction previous rows from the current,
		// Reducing all pre-diagonal elements to zero
		for (int i = 0; i < l; i++) {
			if (a[l][i] == 0) continue;
			koef = a[l][i];
			for (int j = 0; j < n; j++) {
				a[l][j] -= a[i][j] * koef;
			}
			b[l] -= b[i] * koef;
		}

		// If diagonal element of current row is zero, try to swap rows with not zero element
		if (a[l][l] == 0) {
			for (int i = l + 1; i < n; i++) {
				// If possible, swap rows
				if (a[i][l] != 0) {
					for (int j = 0; j < n; j++) {
						std::swap(a[i][j], a[l][j]);
					}
					std::swap(b[i], b[l]);
					D *= -1;
					break;
				}
			}
			// If impossible, return -1
			if (a[l][l] == 0) {
				D = -1;
				return;
			}
		}

		// Dividing current row elements to thediagonal element
		D *= a[l][l];	// Memorizing the divisions into a determinant
		b[l] /= a[l][l];
		for (int i = l + 1; i < n; i++) {
			a[l][i] /= a[l][l];
		}
		a[l][l] = 1;

		// Subtraction current row from previous,
		// Reducing all l-index elements to zero
		for (int i = 0; i < l; i++) {
			b[i] -= b[l] * a[i][l];
			for (int j = l + 1; j < n; j++) {
				a[i][j] -= a[l][j] * a[i][l];
			}
			a[i][l] = 0;
		}
	}
}

// Переставити мiсцями 1-й та 2-й стовпчик
void Matrix::swapl() {
	for (int i = 0; i < n; i++) {
		swap(a[i][0], a[i][1]);
	}
}
