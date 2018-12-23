// This is the realization of c++ square matrix library
#include "Matrix.h"
#include <iostream>
#include <iomanip>


//** Constructors **//

Matrix::Matrix(int size) {
	// If size doesn`t make sense, set n = 1;
	if (size <= 0 || size > 100000000) 
	{
		std::cout << "\nWrong size value was passed, assuming size = 1\n";
		size = 1;
	}
	// Creating n x n matrix
	n = size;
	a = new float *[n];
	b = new float[n];
	for (int i = 0; i < n; i++) {
		a[i] = new float [n];
	}
	
}

// Copying constructor
Matrix::Matrix(const Matrix &copy) {
	n = copy.n;
	if(copy.a) {
		a = new float *[n];
		b = new float[n];
		for (int i = 0; i < n; i++) {
			a[i] = new float [n];
			for (int j = 0; j < 0; j++) {
				a[i][j] = copy.a[i][j];
			}
			b[i] = copy.b[i];
		}
	}
}

// Destructor
Matrix::~Matrix() {
	if (a) {
		for (int i = 0; i < n; i++) {
			delete[] a[i];
		}
		delete[] a;
	}
	if (b) {
		delete[] b;
	}
}


//** Methods **//

// Input from keyboard
void Matrix::init() {
	std::cin.clear();
	// a[][] initialization
	std::cout << "Enter matrix values:\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			// Checking whether entered data is number
			while (!(std::cin >> a[i][j]) || (std::cin.peek() != '\n'))
			{
				std::cin.clear();
				while (std::cin.get() != '\n');
				std::cout << "Error! Non-numeric value was entered.\n" << std::endl;
			}
		}
	}
	// b[] initialization
	std::cout << "Enter matrix keys:\n";
	for (int i = 0; i < n; i++) {
		// Checking whether entered data is number
		while (!(std::cin >> b[i]) || (std::cin.peek() != '\n'))
		{
			std::cin.clear();
			while (std::cin.get() != '\n');
			std::cout << "Error! Non-numeric value was entered.\n" << std::endl;
		}
	}
}


// Initializing the identity matrix
void Matrix::initIdent() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = 0;
		}
	}
	for (int i = 0; i < n; i++) {
		a[i][i] = 1;
	}
}


// Display matrix on screen
void Matrix::print() {
	if (a == NULL) return;
	std::cout.setf(std::ios::fixed);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << std::setw(6) << std::setprecision(2) << a[i][j] << "  ";
		}
		std::cout << "=  " << b[i] << std::endl;
	}
}


// Пошук оберненоi матрицi
Matrix Matrix::reverse() const
{
	Matrix matrix(*this);
	Matrix result(n);
	result.initIdent();	// Initialization of identity matrix

	int row = 0;	// Biggest element row
	int clm = 0;	// Biggest element column

	// Перший крок
	for (int i = 0; i < n; i++) {
		// Finding the indexes of the biggest element
		for (int k = i; k < n; k++) {
			for (int l = i; l < n; l++) {
				if (abs(a[row][clm]) < abs(a[k][l])) 
				{
					row = k;
					clm = l;
				}
			}
		}

		// Перестановка рядкiв
		if (row != i) {
			for (int k = 0; k < n; k++) {
				std::swap(matrix.a[i][k], matrix.a[row][k]);
				std::swap(result.a[i][k], matrix.a[row][k]);
			}
		}
		if (clm != i) {
			for (int k = 0; k < n; k++) {
				std::swap(matrix.a[k][clm], matrix.a[k][clm]);
				std::swap(result.a[k][clm], result.a[k][clm]);
			}
		}

		// Вiднiмання рядкiв з коефiцiентом k
		for (int j = i + 1; j < n; j++) {
			float k = matrix.a[j][i] / matrix.a[i][i];	// Coefficient memorization
			for (int l = i; l < n; l++) {
				matrix.a[j][l] -= matrix.a[i][l] * k;
			}
			for (int l = 0; l < n; l++) {
				result.a[j][l] -= result.a[i][l] * k;
			}
		}
	}

	// Дiлення рядкiв на дiагональний елемент
	for (int i = 0; i < n; i++) {
		float d = matrix.a[i][i];
		for (int j = 0; j < n; j++) {
			matrix.a[i][j] /= d;
			result.a[i][j] /= d;
		}
	}

	// Вiднiмання рядкiв з коефiцiентом k
	for (int i = n - 1; i >= 0; i--) {
		for (int j = i - 1; j >= 0; j--) {
			float k = matrix.a[j][i];
			for (int l = 0; l < n; l++) {
				matrix.a[j][l] -= matrix.a[i][l] * k;
				result.a[j][l] -= result.a[i][l] * k;
			}
		}
	}

	return result;
}


// Знаходження норми матрицi
void Matrix::norm() {
	N = 0;
	float s;
	for (int i = 0; i < n; i++) {
		s = 0;
		for (int j = 0; j < n; j++) {
			s += abs(a[i][j]);
		}
		if (s > N) {
			N = s;
		}
	}
}


// Determinant initializing 
void Matrix::determinant() {
	// Basic cases
	if (n <= 0) { D = -1; return; }
	if (n == 1) { D = a[0][0]; return; }
	if (n == 2) { D = a[0][0] * a[1][1] - a[0][1] * a[1][0]; return; }

	D = 1;

	// Optimal exclusion method
	// Reducing matrix to identity
	for (int l = 0; l < n; l++)
	{
		// First step, subtraction previous rows from the current,
		// Reducing all pre-diagonal elements to zero
		for (int i = 0; i < l; i++) {
			if (a[l][i] == 0) continue;
			float koef = a[l][i];
			for (int j = 0; j < n; j++)  {
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

		// Dividing current row elements to the diagonal element
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


// Overloading of matrix multiplication
Matrix Matrix::operator *(const Matrix &b) {
	if (this->a != b.a) return *this;
	Matrix product(n);
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			product.a[row][col] = 0;
			for (int inner = 0; inner < n; inner++) {
				product.a[row][col] += this->a[row][inner] * b.a[inner][col];
			}
		}
	}
	return product;
}
