/**********************************************************************************************************/
/*** 									  Лабороторна робота №3 										***/
/*** 										   Варiант №5		 										***/
/*** 											З курсу		 											***/
/*** 										Чисельнi методи 											***/
/*** 								ІТЕРАЦІЙНІ МЕТОДИ РОЗВ'ЯЗУВАННЯ СИСТЕМ								***/
/***									ЛІНІЙНИХ АЛГЕБРАЇЧНИХ РІВНЯНЬ									***/
/*** 											Завдання: 												***/
/***	Скласти програму для розв'язування системи iтерацiйним методом послiдовних наближень.			***/
/***	Передбачити максимально допустиму кількість iтерацiй 40. На кожнiй iтерацiї надрукувати її		***/
/***	номер i вектор невiдомих. Надрукувати початкову та перетворену системи. У програмi передбачити	***/
/***	побудову графiка залежностi величини || x(n)- x*||  від n  для  n=1, 2,...,k при  e = 10-6.		***/
/***																Виконав:	Журавльов Роман ТР-71	***/
/**********************************************************************************************************/
#include <fstream>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cmath>

using namespace std;

float a[3][3];
float b[3];
float x[3];
int n = 3;
float eps = 0.0001;
float accuracyArray[40] = { 0 };


void init();				// Инициализация начальной матрицы
void print();				// Вывод матрицы
void gradApprox();			// Решение слау методом простых итераций
void graph();			// Вывод графика
void miss();				// Погрешность


int main()
{
	system("chcp 1251 & cls");
	init();			// Инициализация матрицы
	print();		// Вывод условия
	gradApprox();	// Решение слау
	miss();			// Вывод погрешности
	graph();		// Вывод графика
	getchar();
}


// Инициализация матрицы
void init() {
	a[0][0] = 2;	a[0][1] = 2;	a[0][2] = 10; 		b[0] = 14;
	a[1][0] = 10;   a[1][1] = 1;    a[1][2] = 1;		b[1] = 12;
	a[2][0] = 2;	a[2][1] = 10;	a[2][2] = 1;		b[2] = 13;
}


// Вывод матрицы
void print() {
	cout << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << fixed << setprecision(1) << setw(5) << a[i][j] << "  ";
		}
		cout << "=  " << b[i] << endl;
	}
	cout << endl;
}

// Метод послiдовних наближень
void gradApprox() {
	float xk[3];
	float sum;
	int k = 0;
	// Перестановка рядкiв матрицi щоб елементи головноi дiагоналi були бiльше суми модулiв iнших елементiв рядка
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n; i++) {
			// Пошук суми елементiв рядка
			sum = 0;
			for (int k = 0; k < n; k++) {
				sum += fabs(a[i][k]);
			}
			sum -= fabs(a[i][j]);
			// Перестановка рядкiв якщо вони вiдповiдають умовi
			if (a[i][j] > sum)
			{
				for (int l = 0; l < n; l++) {
					swap(a[j][l], a[i][l]);
				}
				swap(b[j], b[i]);
			}
		}
	}
	// Перетворення матрицi до вигляду "x = ax + b"
	for (int i = 0; i < n; i++) {
		b[i] /= a[i][i];
		for (int j = 0; j < n; j++) {
			if (j != i)
			{
				a[i][j] /= -a[i][i];
			}
		}
		a[i][i] = 0;
	}
	print();
	// Перевiрка на схiднiсть
	for (int i = 0; i < n; i++) {
		sum = 0;
		for (int j = 0; j < n; j++) {
			sum += fabs(a[i][j]);
		}
		if (sum >= 1) {
			cout << "\n Помилка! Матриця не сходиться!\n";
			return;
		}
	}
	// Обчислення матрицi
	cout << "    i         x1         x2         x3         eps\n";
	for (int i = 0; i < n; i++) {
		x[i] = b[i];
	}
	for (int k = 0; k < 40; k++) {
		// Обчислення x(k + 1)
		for (int i = 0; i < n; i++) {
			xk[i] = 0;
			for (int j = 0; j < n; j++) {
				xk[i] += a[i][j] * x[j];
			}
			xk[i] += b[i];
		}
		// Обчислення точностi
		accuracyArray[k] = abs(xk[n - 1] - x[n - 1]);
		// Вивiд результатiв
		cout << endl << fixed << setprecision(5) << setw(4) << k + 1 << " ";
		cout << setw(12) << xk[0] << setw(12) << xk[1] << setw(12) << xk[2] << setw(12) << accuracyArray[k];
		for (int i = 0; i < n; i++) {
			x[i] = xk[i];
		}
		if (eps > accuracyArray[k]) {
			cout << "\n\nРозв'язок знайдено.\n";
			return;
		}
	}
	cout << "\nIтераційний процес не збігається.\n";
}

//  Вычисление погрешности
void miss()
{
	init();
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << "x[" << i + 1 << "] = " << x[i] << endl;
	}
	cout << endl;
	for (int i = 0; i < n; i++) {
		double s = 0;								// Сума ряда
		for (int j = 0; j < n; j++) {
			s += a[i][j] * x[j];
		}
		printf("a[%d] = %lf\n", i + 1, s - b[i]);	// Вывод каждой погрешности
	}
}


// Вывод графика
void graph() {
	ofstream dots("dots.txt");
	for (int i = 0; i < 40; i++) {
		dots << i << " " << accuracyArray[i] << endl;
	}
	dots.close();

	ofstream com("commands.txt");
	com << "set key right center" << endl;
	com << "plot 'dots.txt' u 1:2 title 'miss' with lines";
	com.close();
	system("\"C:\\gnuplot\\bin\\wgnuplot.exe -p\" commands.txt");
}
