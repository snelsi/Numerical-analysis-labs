//*****************************************************************************************
//*** 							Лабораторна работа номер 8								***
//*** 						з курсу Чисельні методи, варіант 5							***
//*** 					Чисельне розв’язування нелінійних рівнянь						***     
//*** 		Завдання: Відокремити корені. Обчислити значення функції на [-10,10] з		***
//*** 		кроком 0.5 і знайти значення на яких функці змінює знак. Побудувати			***
//*** 		графік і знайти за допомогою відповідного методу корені рівняння.			***
//*** 					На кожній ітерації виводити значення.							***
//*** 									Виконав: Журавльов Роман Вiкторович				***
//*** 									Перевірив: Сігайов А.О.							***
//*****************************************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

double a = -10;
double b = 10;

double H = 0.5;
double eps = 0.0001;

int k = 1 + (b - a) / H;


vector<double> findRoots();
double NewtonMethod(double x);
void drawGraph(vector<double> &values);


// Значення функцiї в точцi
double f(double x)  { return atan(x) - pow(x, 3) / 3; }

// Похiдна в точцi
double df(double x) { return 1. / (1 + x * x) - x * x; }


// Вхiд в програму
int main() {
	vector<double> roots = findRoots();			// Знаходження коренiв
	for (int i = 0; i < roots.size(); i++) {	// Уточнення коренiв методом Ньютона
		roots[i] = NewtonMethod(roots[i]);
	}
	cout << endl << "Roots of the equation:" << endl;
	for (auto p : roots) {						// Вивiд коренiв
		cout << p << " ";
	}
	drawGraph(roots);							// Графік
	getchar();
}


// Уточнення коренiв
double NewtonMethod(double x)
{
	cout << "Processing root " << x << endl;
	for (double iter = 1; fabs(f(x)) > eps; iter++)
	{
		if (df(x) == 0) break;
		cout << setw(2) << setprecision(0) << iter;
		cout << "  x = " << setw(4) << x;
		cout << ", f(x) = " << setw(8) << f(x) << endl;
		x -= f(x) / df(x);
	}
	cout << endl;
	return x;
}


// Пошук коренiв
vector<double> findRoots()
{
	double* X = new double[k];
	double* Y = new double[k];
	vector<double> roots;
	X[0] = a;
	Y[0] = f(a);
	for (int i = 1; i < k; i++)
	{
		// Запис значень функцiї
		X[i] = a + H * i;
		Y[i] = f(X[i]);
		// Відокремлення коренів
		if (Y[i] == 0) {
			cout << "Separated root: x = " << X[i] << endl;
			roots.push_back(X[i]);
		}
		else if (Y[i] * Y[i - 1] < 0) {
			cout << "Separated root on [a,b]: [" << X[i - 1] << ";" << X[i] << "]" << endl;
			roots.push_back(X[i - 1]);
		}
	}
	// Вивід таблиці значень
	cout << "\n    x           f(x)" << endl;
	cout << "----------------------" << endl;
	for (int i = 0; i < k; i++)
	{
		cout << setw(7) << X[i] << setw(15) << Y[i] << endl;
	}
	cout << "----------------------" << endl << endl;

	delete[] X;
	delete[] Y;
	return roots;
}


// Графiк
void drawGraph(vector<double> &values)
{
	ofstream dots("dots.log");
	for (auto p : values)
	{
		dots << p << " " << 0 << endl;
	}
	dots.close();

	ofstream com("commands.txt"); // Запис команд до файлу для гнуплот
	com << "set title 'Чисельне розвязування нелінійних рівнянь'" << endl;
	com << "set mxtics 2" << endl << "set mytics 2" << endl << "set grid xtics ytics mxtics mytics" << endl;
	com << "plot (atan(x) - (x * x * x) / 3) title 'f(x)', 'dots.log' u 1:2 title 'roots'" << endl;
	com.close();
	// Створення графiка
	system("\"C:\\gnuplot\\bin\\wgnuplot.exe -p\" commands.txt");
}
