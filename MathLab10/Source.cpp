//*********************************************************************************************
//***								Лабораторна работа номер 10								***
//***							з курсу Чисельні методи, варіант 5							***
//***							Тема: Чисельне iнтегрування							    	***
//***			Завдання: На початку програми обчислюється точне значення інтеграла по		***
//***	формулі Ньютона - Лейбница. Наближене значення інтеграла обчислюється методом		***
//***	Ньютона-Котеса n = 6. Вивести таблицю i графiк y = f(x).							***
//***										Виконав: Журавльов Роман Вiкторович				***
//***										Перевірив: Сігайов А.О.							***
//*********************************************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

// Коефiцiенти Котеса
const int n = 6;
const double H[] = { 41, 216, 27, 272, 27, 216, 41 };


// Пiдiнтегральна функцiя
double f(double x) { return x * x * x * pow(x * x + 4, 3 / 2.); }
// Первiсна
double F(double x) { return pow(x * x + 4, 5 / 2.) * (5 * x * x - 8) / 35.; }


// Графiк
void graph1() {
	ofstream com("commands.txt");
	com << "set key right center" << endl;
	com << "set title 'Iнтегрування функцiй'" << endl;
	com << "set xrange[3:5]" << endl;
	com << "plot x**3 * sqrt((x * x + 4) ** 3) title 'y(x)'";
	com.close();
	system("\"C:\\gnuplot\\bin\\wgnuplot.exe -p\" commands.txt");
}

// Вивiд дiаграми
void graph2() {
	ofstream com("commands.txt");
	com << endl << "set yrange [0:8]" << endl;
	com << "set xtics('e' 0,'e/5' 1, 'e/25' 2, 'e/125' 3, 'e/625' 4, 'e/3125' 5, 'e/15625' 6, '' 7)" << endl;
	com << "set style data boxes" << endl << "set boxwidth 0.6 absolute" << endl;
	com << "set style fill solid 1" << endl;
	com << "plot 'additional.log' u 1 title 'L*(e)'" << endl;
	com.close();
	system("\"C:\\gnuplot\\bin\\wgnuplot.exe -p\" commands.txt");
}

double integral(double a, double d) {
	double h = d / n;
	double Sum = 0;
	double x = a;
	for (int i = 0; i <= n; i++) {
		Sum += H[i] * f(x);
		x += h;
	}
	Sum *= d / 840.;
	return Sum;
}

int main() {
	// Початковi умови
	double a = 3;
	double b = 5;

	double h;
	double eps = 0.001;
	double Sum;
	double Check = F(b) - F(a);
	int L;

	// Таблиця значень f(x)
	cout.setf(ios::fixed);
	cout << setprecision(2);
	double x = a;
	do {
		cout << "y(" << x << ") = " << f(x) << endl;
		x += 0.1;
	} while (x < b);

	// Обчислення iнтеграла
	ofstream iter("additional.log");
	for (int i = 0; i < 8; i++) {
		L = 0;
		do {
			L++;
			Sum = 0;
			h = (b - a) / L;
			for (int i = 0; i < L; i++) {
				Sum += integral(a + i * h, h);
			}
		} while (fabs(Sum - Check) > eps);
		iter << L << endl;
		eps /= 5;
	}
	iter.close();

	// Вивiд результатiв
	cout << setprecision(10) << endl;
	cout << "Approximated value: " << Sum << endl;
	cout << "Verification value: " << Check << endl;

	graph1();
	graph2();
	getchar();
}
