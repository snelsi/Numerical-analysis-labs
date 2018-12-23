//*****************************************************************************************************************************
//***										Лабораторна работа номер 11														***
//***									з курсу Чисельні методи, варіант 5													***
//***									Тема: Чисельне диференцiювання													   	***
//***		Завдання: Необхідно обчислити значення похідної трьома способами: по спрощенiй формулi, по формулi 4.5 i по 	***
//***		формулi, отриманiй аналiтично. Побудувати таблицю значень величин на промiжку [a, b]. Побудувати графiк f(x) i	***
//***		окремо графiки похiдних на одному полi. В тих же вузлах знайти D* зi зменшеним в 4 рази кроком.					***
//***																		Виконав: Журавльов Роман Вiкторович				***
//***																		Перевірив: Сігайов А.О.							***
//*****************************************************************************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

long double eps = 0.00000001;

// Значення функцii в точцi
double f(long double x) {
	return sqrt(x) + cos(x);
}

// Спрощена формула
double drv1(double x, double h = eps) {
	return (f(x + h) - f(x)) / h; 
}

// Формула 4.5
double drv2(double x, double h = eps) {
	return (f(x + h) - f(x - h)) / (2 * h);
}

// Аналiтично
double drv3(long double x) {
	return 1 / (2 * sqrt(x)) - sin(x);
}

// Графiки
void graph() {
	ofstream com1("commands.txt");
	com1 << "set key right center" << endl;
	com1 << "plot (sqrt(x) + cos(x)) title 'f(x)'";
	com1.close();
	system("\"C:\\gnuplot\\bin\\wgnuplot.exe -p\" commands.txt");

	ofstream com2("commands2.txt");
	com2 << "set key right center" << endl;
	com2 << "plot ((sqrt(x + 0.5) + cos(x + 0.5) - sqrt(x) - cos(x)) / 0.5) title 'D*', ";
	com2 << "(sqrt(x + 0.5) + cos(x + 0.5) - sqrt(x - 0.5) - cos(x - 0.5)) title 'Dнабл', ";
	com2 << "(1/ (2 * sqrt(x)) - sin(x)) title 'Dточ', ";
	com2 << "((sqrt(x + 0.125) + cos(x + 0.125) - sqrt(x) - cos(x)) / 0.125) title 'D*/4'";
	com2.close();
	system("\"C:\\gnuplot\\bin\\wgnuplot.exe -p\" commands2.txt");
}


int main() {
	int a = 0;
	int b = 5;
	double h = (b - a) / 10.;
	double x = a;
	cout << " x       f(x)         D*          D~          D            D*%          D~%" << endl;
	for (int i = 0; i < 10; i++) {
		x += h;
		cout << setw(3) << x << " ";
		cout << setprecision(6)<< setw(10) << f(x) << "   ";
		cout << setw(10) << drv1(x, h) << "  ";
		cout << setw(10) << drv2(x, h) << "  ";
		cout << setw(10) << drv3(x) << "  ";
		cout << setw(10) << (drv1(x, h) - drv3(x)) / drv3(x) * 100 << "%" << "  ";
		cout << setw(10) << (drv2(x, h) - drv3(x)) / drv3(x) * 100 << "%" << endl;
	}

	x = a;
	cout << endl << "D* with smaller step:" << endl;
	for (int i = 0; i < 10; i++) {
		x += h;
		cout << setw(3) << x << "  " << setw(10) << drv1(x, h / 4) << endl;
	}
	graph();
	getchar();
}
