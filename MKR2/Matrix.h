#pragma once

struct Matrix {
	float **a = nullptr;			// Left  part values
	float *b  = nullptr;			// Right part values

	int n = 0;						// Matrix size

	float D = 0;					// Determinant
	float N = 0;					// Matrix Norm

	// Constructors
	Matrix(int size);
	Matrix(const Matrix &copy);

	// Destructor
	~Matrix();

	// Methods
	void norm();
	void init();
	void print();
	void initIdent();				// Identity matrix
	void determinant();

	Matrix reverse() const;
	Matrix operator *(const Matrix &b);
};
