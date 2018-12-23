#pragma once

struct Matrix {
	float a[4][4];		// Лiва частина матрицi
	float b[4];			// Права частина матрицi

	int n = 4;			// Розмiр матрицi
	int D = 0;			// Визначник

	int k = 0;			// Кiлькiсть арифметичних операцiй

	int var[4];			// Допомiжний масив перестановок
	int pos = 0;		// Допомiжне число перестановок

	Matrix() { init(); }

	void init();
	void swapl();
	void print();
	void reshuffle();
	void determinant();
	void optimalException();
};
