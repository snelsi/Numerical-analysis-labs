//*****************************************************************************************************************************************
//***												Лабораторна работа номер 5															***
//***											з курсу Чисельні методи, варіант 5														***
//***			     			Середньоквадратичне наближення функцій. Нормальні рівняння												***																														***
//***			Завдання: За допомогою нормальних рівнянь потрібно побудувати поліноми Pn(x) степенів n=0...4, які на сітці xi дають	***
//***			найкраще середньоквадратичне наближення. Для кожного багаточлена скласти таблицю величин та побудувати на одному полі	***
//***			графіки функцій f(x), Pn(x) на тому самому відрізку. Також виконати додаткове завдання відповідно варіанту.				***
//***																			Виконав: Журавльов Роман Вiкторович						***
//***																			Перевірив: Сігайов А.О.									***
//*****************************************************************************************************************************************
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

const int n = 10;

// Масив координат
double X[n + 1];
double Y[n + 1];

// Дiапазон, крок
double a = -1;
double b = 3;
double h = (b - a) / n;


double polinom(double t, int k);  // Функцiя нормальних рiвнянь
void initDots();				// Запис значень точок до масивiв X, Y
void table();					// Вивiд таблицi значень
void Additional();				// Додаткове завдання
void graph();					// Вивiд графiка


int main() {
	system("chcp 1251 & cls");
	initDots();
	table();
	graph();
	getchar();
}

// Запис значень точок до масивiв X, Y
void initDots() {
	cout << "Точки початкової функції: " << endl;
	cout << "     x          y" << endl;
	// Запис значень функцiї у масив
	for (int i = 0; i < 11; i++) {
		X[i] = a + i * h;
		Y[i] = exp(0.2 * X[i]) + cos(X[i]);
		cout << "|  " << setw(4) << X[i] << "  |  " << setw(9) << Y[i] << "  |" << endl;
	}
}


void table() {
	cout << " \n\nТаблиця величин для кожного P(x): " << endl;
	// Таблиця значень i вiдхилень
	for (int i = 2; i <= 5; i++) {
		cout << "\n n = " << i << endl;
		cout << "--------------------------------------------------------------------------" << endl;
		cout << "      x          f(x)          Pn(x)         Pn(x)-f(x)            % " << endl;
		int step = 0;
		double x = a;
		cout.setf(ios::fixed);
		while (x <= b)
		{
			double pol = polinom(x, i);
			double func = exp(0.2 * x) + cos(x);

			cout << setw(8) << setprecision(3) << x;
			cout << setw(14) << setprecision(6) << func;
			cout << setw(15) << setprecision(6) << pol;
			cout << setw(17) << setprecision(7) << pol - func;
			cout << setw(18) << setprecision(7) << (pol - func) / func << "%";
			cout << endl;
			step++;
			x = a + step * h;
		}
	}
}


// Функцiя нормальних рiвнянь
double polinom(double t, int k) {
	double a[n][n];
	double xx[n], yy[n];
	double eps = 0.00001;

	// Запис значень величин лівої частини системи рівнянь
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			a[i][j] = pow(X[i], k - j - 1);
		}
		yy[i] = Y[i];
	}

	for (int l = 0; l < k; l++) {
		// Пошук рядка з максимальним a[i][k]
		double max = abs(a[l][l]);
		int index = l;
		for (int i = l + 1; i < k; i++) {
			if (abs(a[i][l]) > max) {
				max = abs(a[i][l]);
				index = i;
			}
		}

		// Якщо всi елементи нульовi, помилка
		if (max < eps) {
			cout << "Розв'язок не знаходиться " << endl;
			return 0;
		}

		for (int j = 0; j < k; j++) {
			swap(a[l][j], a[index][j]);
		}
		swap(yy[l], yy[index]);

		// Нормалізація рівнянь
		for (int i = l; i < k; i++)
		{
			if (abs(a[i][l]) < eps) continue;
			// Дiлення рядка на максимальний елемент
			double temp = a[i][l];
			for (int j = 0; j < k; j++) {
				a[i][j] /= temp;
			}
			yy[i] /= temp;

			if (i == l) continue;
			// Вiднiмання поелементно рядки
			for (int j = 0; j < k; j++) {
				a[i][j] -= a[l][j];
			}
			yy[i] -= yy[l];
		}
	}

	// Зворотня підстановка
	for (int l = k - 1; l >= 0; l--) {
		xx[l] = yy[l];
		for (int i = 0; i < l; i++) {
			yy[i] -= a[i][l] * xx[l];
		}
	}

	// Побудова полінома
	double sum = 0;
	for (int j = 0; j < k; j++) {
		sum += pow(t, k - j - 1) * xx[j];
	}
	return sum;
}


// Додаткове завдання
void Additional() {
	int index = 0;
	double miss = DBL_DIG;
	// Пошук мiнiмальноi похибки
	for (int i = 2; i <= 5; i++) {
		double sum = 0;
		double x = a;
		int step = 0;
		while (x <= b) {
			miss += pow(polinom(x, i) - exp(0.2 * x) + cos(x), 2);
			step++;
			x = a + step * h;
		}
		if (step) {
			sum = sqrt(sum / step);
			if (sum < miss) {
				index = i;
				miss = sum;
			}
		}
	}
	cout << "Вiдхилення найменше при " << index << endl;
}


// Вивiд графiка
void graph() {
	ofstream dots("values.log");
	for (int i = 0; i <= n; i++) {
		double x = a + i * h;
		dots << x << " " << polinom(x, 2) << " " << polinom(x, 3) << " " << polinom(x, 4) << " " << polinom(x, 5) << endl;
	}
	dots.close();

	ofstream graph("commands.txt"); // Запис команд до файлу для гнуплот
	graph << "set output 'graph.png'" << endl << "set key right center" << endl;
	graph << "plot (exp(0.2 * x) + cos(x)) title 'f(x)', 'values.log' u 1:2 title 'P2(x)' w lines, 'values.log' u 1:3 title 'P3(x)' w lines, 'values.log' u 1:4 title 'P4(x)' w lines,  'values.log' u 1:5 title 'P5(x)' w lines" << endl;
	graph.close();

	system("\"C:\\gnuplot\\bin\\wgnuplot.exe -p\" commands.txt");
}
