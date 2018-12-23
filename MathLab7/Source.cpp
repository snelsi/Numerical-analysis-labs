//*****************************************************************************************************************************************
//****												Лабораторна работа номер 7															***
//****											з курсу Чисельні методи, варіант 5														***
//****			     			Середньоквадратичне наближення функцій. Ортогональні поліноми.											***
//****		Завдання: Побудувати таблицю значень функції f(x) на відрізку [a,b] в точках xi=a+H(i-1), H=(b-a)/(n-1),i=1,n, n=6			***
//****		Результатом є інтерполяційний сплайн S(x) другого або третього степеня. Потім будується сплайн у вигляді прямокутного		***
//****		масиву розміром (n-1)*3, де збігаються коефіцієнти сплайну. Потім використовується метод згідно варіанту.					***
//****																			Виконав: Журавльов Роман Вiкторович						***
//****																			Перевірив: Сігайов А.О.									***
//*****************************************************************************************************************************************

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

const int n = 6;
double a = -1;
double b = 3;
double H = (b - a) / (n - 1);

double X[n + 6];
double Y[n + 6];
double Sx[n + 6];
double gamma[n + 6];
double* M;

void tables();	// вивід таблицi
void getM();	// пошук значень 

void drawGraph();	// Основний графік
void addExercise(); // Додатковий графiк

double S(int i, double x); // запис значень до допоміжного масиву
double* GausFunction(double** A, double* B); // метод Гауса


int main()
{
	// Pапис значень до таблиці X, Y
	for (int i = 0; i < n + 4; i++) {
		X[i] = a + H * (i - 1);
		Y[i] = exp(0.2 * X[i]) + cos(X[i]);
	}
	// Iніціалізаця значень похiдних
	for (int i = 1; i < n + 3; i++) {
		gamma[i] = 3 * (Y[i + 1] - Y[i - 1]) / H;
	}
	getM();			// Пошук промiжних значень за допомогою сплайнів
	tables();		// Вивід таблиці
	drawGraph();	// Графік функцii
	addExercise();	// Графiк похiдних
	getchar();
	return 0;
}


// Таблиця
void tables()
{
	cout.flags(ios::fixed);
	cout << "     x          y" << endl;
	for (int i = 0; i < n + 4; i++) {
		cout << "|  " << setw(4) << setprecision(1) << X[i] << "  |  " << setw(9) << setprecision(6) << Y[i] << "  |" << endl;
	}

	cout << "\n___________________________________________________" << endl;
	cout << "   x           f              fi            abs" << endl;
	for (int i = 0; i < n + 4; i++) {
		cout << setw(5) << setprecision(2) << X[i] << setw(15) << setprecision(8) << Y[i] << setw(15) << setprecision(8) << S(i, X[i]) << setw(15) << setprecision(6) << Y[i] - S(i, X[i]) << endl;
	}
	cout << "___________________________________________________" << endl;
}


// Графiк
void drawGraph()
{
	ofstream fout("values.log"); // запис значень величин до файлу для гнуплот
	for (int i = 0; i < n + 4; i++)
	{
		fout << X[i] << " " << S(i, X[i]) << endl;
	}
	fout.close(); // закрываем файл

	ofstream com("commands.txt"); // запис команд до файлу для гнуплот
	com << "set output 'graph1.png'" << endl << "set key right center" << endl;
	com << "set title 'Апроксимація сплайнами'" << endl;
	com << "plot (exp(0.2 * x) + cos(x)) title 'f(x)', 'values.log' u 1:2 title 'S(x)' w lines" << endl;
	com.close();
	// создание графика 
	system("\"C:\\gnuplot\\bin\\wgnuplot.exe -p\" commands.txt");
}

void addExercise()
{
	ofstream fout("values2.log"); // запис значень величин до файлу для гнуплот
	for (int i = 1; i < n + 4; i++)
	{
		fout << X[i] << " " << (Y[i] - Y[i - 1]) / H << " " << (Sx[i] - Sx[i - 1]) / H << endl;
	}
	fout.close(); // закрываем файл

	ofstream com("commands2.txt"); // запис команд до файлу для гнуплот
	com << "set output 'graph2.png'" << endl << "set key right center" << endl;
	com << "set title 'Апроксимація сплайнами'" << endl;
	com << "plot 'values2.log' u 1:2 title 'f`(x)' w lines, 'values2.log' u 1:3 title 'S`(x)' w lines" << endl;
	com.close();
	// создание графика 
	system("\"C:\\gnuplot\\bin\\wgnuplot.exe -p\" commands2.txt");
}


double S(int i, double x)
{
	double tmp[4];
	double h = X[i + 1] - X[i];
	tmp[0] = pow((X[i + 1] - x), 2) * (2 * (x - X[i]) + h) * Y[i] / h / h / h;
	tmp[1] = pow((x - X[i]), 2) * (2 * (X[i + 1] - x) + h) * Y[i + 1] / h / h / h;
	tmp[2] = pow((X[i + 1] - x), 2) * (x - X[i]) * M[i] / h / h;
	tmp[3] = pow((x - X[i]), 2) * (x - X[i + 1]) * M[i + 1] / h / h;

	h = 0;
	for (int i = 0; i < 4; i++)
	{
		h += tmp[i];
	}
	Sx[i] = h;

	return h;
}



void getM()
{
	double* B = new double[n + 4];
	double** A = new double*[n + 4];
	for (int i = 0; i < n + 4; i++)
	{
		A[i] = new double[n + 4];
	}

	for (int i = 0; i < n + 4; i++)
	{
		for (int j = 0; j < n + 4; j++)
		{
			if (i == j) A[i][j] = 4;
			if (j - i == 1) A[i][j] = 1;
			if (i - j == 1) A[i][j] = 1;
		}
	}

	// крайові елементи
	B[0] = gamma[1] - 0.2 * exp(0.2 * X[0]) + sin(X[0]);
	B[n + 3] = gamma[n + 2] - 0.2 * exp(0.2 * X[n + 3]) + sin(X[n + 3]);

	// права частина
	for (int i = 1; i < n + 2; i++)
	{
		B[i] = gamma[i];
	}

	double* tmp = GausFunction(A, B); // метод гауса

	//крайові елементи кінцевого масиву
	tmp[0] = 0.2 * exp(0.2 * X[0]) - sin(X[0]);
	tmp[n + 3] = 0.2 * exp(0.2 * X[n + 3]) - sin(X[n + 3]);

	M = tmp;

	delete[] tmp;
	delete[] B;
	for (int count = 0; count < 2; count++)
	{
		delete[] A[count];
	}
}



double* GausFunction(double** A, double* B)
{
	int size = sizeof(B);
	double* x = new double[size];

	for (int k = 0; k < size - 1; k++)
	{
		double maxA = fabs(A[k][k]);
		int maxK = k;

		for (int i = k + 1; i < size; i++)
		{
			if (fabs(A[i][k]) > maxA) {
				maxA = fabs(A[i][k]);
				maxK = i;
			}

			if (maxK != k)
			{
				for (int j = 0; j < size; j++) {
					double buf1 = A[k][j];
					A[k][j] = A[maxK][j];
					A[maxK][j] = buf1;
				}
				swap(B[k], B[maxK]);
			}
		}

		for (int i = k + 1; i < size; i++)
		{
			double r = A[i][k] / A[k][k];

			for (int j = k; j < size; j++) {
				A[i][j] -= r * A[k][j];
			}
			B[i] -= r * B[k];
		}
	}

	x[size - 1] = B[size - 1] / A[size - 1][size - 1];
	for (int i = size - 2; i >= 0; i--) {
		double sum = 0;
		for (int j = i + 1; j < size; j++) {
			sum += A[i][j] * x[j];
		}
		x[i] = (B[i] - sum) / A[i][i];
	}

	return x;
}
