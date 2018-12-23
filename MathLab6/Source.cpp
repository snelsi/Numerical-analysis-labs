//*********************************************************************************************************************************
//***												Лабораторна работа номер 6													***
//***											з курсу Чисельні методи, варіант 5												***
//***			     			Середньоквадратичне наближення функцій. Ортогональні поліноми									***																														***
//***	За допомогою ортогональних багаточленів потрібно побудувати поліноми Pn(x) степенів n=0...4, які на сітці xi дають		***
//***	найкраще середньоквадратичне наближення. Для кожного багаточлена скласти таблицю величин та побудувати на одному полі	***
//***	графіки функцій f(x), Pn(x) на тому самому відрізку. Також виконати додаткове завдання відповідно варіанту.				***
//***																Виконав: Журавльов Роман Вiкторович							***
//***																Перевiрив: Сiгайов А.О.										***
//*********************************************************************************************************************************

#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

const int n = 11;
const int m = 20;

double a = -1;
double b = 3;
double h = (b - a) / 10;

double X[m + 1]; // Масив точок x
double Y[m + 1]; // Масив точок y

void drawGraph();											// Графік 1
void drawGraph2();											// Графік 2
double polinom(double t, int k);  // Функцiя нормальних рiвнянь

int main()
{
	system("chcp 1251 & cls");
	cout << "Точки початкової функції: " << endl;
	cout << "     x          y" << endl;

	for (int i = 0; i < m; i++)
	{
		X[i] = a + i * h;
		Y[i] = X[i] * X[i] + sin(X[i]);
		cout << "|  " << setw(4) << X[i] << "  |  " << setw(9) << Y[i] << "  |" << endl;
	}

	a -= 2 * h;
	b += 2 * h;
	h = (b - a) / 20;

	cout << endl << endl << "Таблиця величин P(x):" << endl;
	// Таблиця значень i вiдхилень
	for (int i = 1; i <= 4; i++)
	{
		cout << "\n n = " << i << endl;
		cout << "--------------------------------------------------------------------------" << endl;
		cout << "      x          f(x)          Pn(x)         Pn(x)-f(x)            %" << endl;
		int step = 0;
		double x = a;
		cout.setf(ios::fixed);
		while (x <= b)
		{
			double pol = polinom(x, i);
			double func = x * x + sin(x);

			cout << setw(8)  << setprecision(3) << x;
			cout << setw(14) << setprecision(6) << func;
			cout << setw(15) << setprecision(6) << pol;
			cout << setw(17) << setprecision(7) << pol - func;
			cout << setw(18) << setprecision(7) << (pol - func) / func << "%";
			cout << endl;
			step++;
			x += h;
		}
	}

	// Вывод графика
	drawGraph();

	// додаткове завдання
	drawGraph2();

	getchar();
}


double polinom(double x, int k) // функция нормальных уровнений
{
	double a[m];
	double q[n];
	double alpha[n + 1];
	double beta[n];
	q[0] = 0;
	q[1] = 1;

	// запис значень величин до a
	double sumk = 0;
	double summ = 0;
	for (int i = 0; i < m; i++)
	{
		sumk += Y[i];
		summ += X[i];
	}
	a[0] = sumk / m;
	alpha[0] = summ / m;

	for (int j = 1; j < k + 1; j++)
	{
		double sum1 = 0, sum2 = 0;
		for (int i = 0; i < m; i++)
		{
			sum1 += X[i] * q[j] * q[j];
			sum2 += q[j] * q[j];
		}
		alpha[j] = sum1 / sum2;

		if (j - 1 > 0)
		{
			sum1 = 0;
			sum2 = 0;
			for (int i = 0; i < m; i++)
			{
				sum1 += X[i] * q[j] * q[j - 1];
				sum2 += q[j - 1] * q[j - 1];
			}
			beta[j - 1] = sum1 / sum2;
		}
		else beta[j - 1] = 0;

		q[j + 1] = x * q[j] - alpha[j] * q[j] - beta[j - 1] * q[j - 1];

		sum1 = 0;
		sum2 = 0;
		for (int i = 0; i < m; i++)
		{
			sum1 += q[j + 1] * Y[i];
			sum2 += q[j + 1] * q[j + 1];
		}
		a[j] = sum1 / sum2;
	}

	// побудова полінома
	double sum = 0;
	for (int i = 0; i < k; i++)
	{
		sum += a[i] * q[i];
	}
	return sum;
}

void drawGraph() {
	ofstream dots("values.log"); // запис значень величин до файлу для гнуплот
	for (int i = 0; i <= m; i++)
	{
		double x = a + i * h;
		dots << x << " " << x * x + sin(x) << " " << polinom(x, 1) << " " << polinom(x, 2) << " " << polinom(x, 3) << " " << polinom(x, 4) << endl;
	}
	dots.close();

	ofstream graph("commands.txt"); // запис команд до файлу для гнуплот
	graph << "set output 'graph.png'" << endl << "set key right center" << endl;
	graph << "plot 'values.log' u 1:2 title 'f(x)' w linesp, 'values.log' u 1:3 title 'P1(x)' w linesp, 'values.log' u 1:4 title 'P2(x)' w linesp, 'values.log' u 1:5 title 'P3(x)' w linesp, 'values.log' u 1:6 title 'P4(x)' w linesp " << endl;
	graph.close();

	system("\"C:\\gnuplot\\bin\\wgnuplot.exe\"");
}

void drawGraph2() {
	ofstream dots("values.log"); // запис значень величин до файлу для гнуплот
	for (int i = 0; i <= m; i++)
	{
		double x = a + i * h;
		dots << x << " " << " " << x * x + sin(x) - polinom(x, 3) << " " << x * x + sin(x) - polinom(x, 4) << endl;
	}
	dots.close();

	ofstream graph("commands.txt");
	graph << "set key right center" << endl;
	graph << "plot 'x * x + sin(x) title 'f(x)' w linesp, 'values.log' u 1:2 title 'f(x) - P3(x)' w linesp, 'values.log' u 1:3 title 'f(x) - P4(x)' w linesp " << endl;
	graph.close();

	system("\"C:\\gnuplot\\bin\\wgnuplot.exe\"");
}
