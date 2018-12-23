/**********************************************************************************************************/
/*** 									  Лабороторна робота №4 										***/
/*** 										   Варiант №5		 										***/
/*** 											З курсу		 											***/
/*** 										Чисельнi методи 											***/
/*** 										IНТЕРПОЛЯЦІЯ  ФУНКЦІЙ										***/
/*** 											Завдання: 												***/
/***	Функція f(x) задана. Побудувати таблицю її значень і потім провести інтерполяцію.				***/
/***	Функцiя y = exp(0.2 * x) + cos(x), iнтервал [-1,3]. Використовуючи y=f(x), побудувати таблицю	***/
/***	її значень в (n+1)-й точцi xi=a+iH, H=(b-a)/n, i=0,1,…,n. Якщо поліном будується у канонічному	***/
/***	вигляді, надрукувати його коефіцієнти. У програмі побудуйте таблицю значень: x; точне f(x),		***/
/***	наближене g(x), абсолютну похибку f(x)-g(x), відносну похибку (f(x)-g(x))100/ f(x).				***/
/***	Надрукувати графiки.																			***/
/***																Виконав:	Журавльов Роман ТР-71	***/
/**********************************************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "Spline.h"			// Бiблiотека обчислення кубiчних сплайнiв

using namespace std;

const float a = -1;			// Левая граница
const float b = 3;			// Правая граница
const int n = 4;

int main()
{
	vector< float > x;		// Массив точек абсцисс
	vector< float > y;		// Массив точек ординат

	float temp;
	for (int i = 0; i <= n; i++) {	// Заполнение векторов точками
		temp = a + i * (b - a) / n;
		x.push_back(temp);
		y.push_back(exp(0.2 * temp) + cos(temp));
	}

	Spline spline(x, y);	// Интерполяция сплайнов

	for (int i = 0; i < 4; i++) {
		cout << setw(8) << spline.coeff[i].a << " " 
			<< setw(8) << spline.coeff[i].b << " " 
			<< setw(8) << spline.coeff[i].c << " " 
			<< setw(8) << spline.coeff[i].d << endl;
	}

	cout << endl << "      x    |   f(x)   |   g(x)  |    -   |   %" << endl;

	// Вывод таблицы на экран и значений в файлы
	ofstream polynom;
	ofstream reference;
	ofstream miss;
	polynom.open("polynom.txt");
	reference.open("reference.txt");
	miss.open("miss.txt");

	cout.setf(ios::fixed);

	for (double i = -1; i < 3; i += 0.1) {
		temp = exp(0.2 * i) + cos(i);
		polynom << i << " " << spline.getY(i) << endl;
		reference << i << " " << temp << endl;
		miss << i << " " << temp - spline.getY(i) << endl;
		cout << setw(9) << setprecision(2) << i << setw(11) << setprecision(4) << temp << setw(10) << setprecision(4) << spline.getY(i) << setw(10) << setprecision(4) << temp - spline.getY(i) << setw(10) << setprecision(4) << temp - spline.getY(i) / temp * 100 << "%" << endl;
	}
	getchar();

	polynom.close();
	reference.close();
	miss.close();

	return 0;
}
