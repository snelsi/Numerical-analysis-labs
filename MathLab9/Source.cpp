//*********************************************************************************************************************************
//****										Лабораторна работа номер 9															***
//****									з курсу Чисельні методи, варіант 5														***
//****							Тема: Чисельне роз'язування систем нелінійних рівнянь									    	***
//****			Завдання: Розв'язати систему нелінійних рівнянь модифікованим методом Ньютона з перерахуванням Якобіана через	***
//****			дві ітерації. Виводити на кожному кроці поточні значення. Виконати додаткове завдання. Побудувати графік.		***
//****																		Виконав: Журавльов Роман Вiкторович					***
//****																		Перевірив: Сігайов А.О.								***
//*********************************************************************************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

#define eps 0.0001 // Точність

using namespace std;

int NewtonMethod(double x, double y);	// Модифікований метод Ньютона з перерахуванням Якобіана через 2 ітерації
void drawGraph();						// Графік
void drawDiagram();						// Дiаграма


// Початковi функцiї
double f1(double x, double y) { return x + sin(y); }
double f2(double x, double y) { return x + y * 100; }

// Частковi похiднi
double f1x(double x, double y) { return 1; }
double f1y(double x, double y) { return cos(y); }
double f2x(double x, double y) { return 1; }
double f2y(double x, double y) { return 100; }


// Вхiд в програму
int main() {
	NewtonMethod(-24, 18);
	drawGraph();
	drawDiagram();
	getchar();
}


// Обчислення Якобіана
void Jacobian(double a[2][2]) {
	double det = a[0][0] * a[1][1] - a[0][1] * a[1][0];
	double aa = a[0][0];
	a[0][0] = a[1][1] / det;
	a[1][1] = aa / det;
	a[0][1] /= -det;
	a[1][0] /= -det;
}


// Уточнення значень
int NewtonMethod(double x, double y) {
	ofstream miss("miss.log");
	int i = 1;
	double a[2][2];
	double norm;
	double dx, dy;
	cout << "  i            xk            yk              F1              F2" << endl;
	cout << fixed << "  0\t" << setw(10) << setprecision(9) << x << "\t" << setw(10) << setprecision(7) << y << "\t" << setw(10) << setprecision(7) << f1(x, y) << "\t" << setprecision(7) << f2(x, y) << endl;
	do
	{
		// Кожну другу iтерацiю рахувати якобiан
		if (i - 2 == 1 || i == 1)
		{
			// Запис значень функцiй i похiдних в матрицю
			a[0][0] = f1x(x, y);
			a[0][1] = f1y(x, y);
			a[1][0] = f2x(x, y);
			a[1][1] = f2y(x, y);
			// Використання якобiана
			Jacobian(a);
		}
		dx = a[0][0] * f1(x, y) + a[0][1] * f2(x, y);
		dy = a[1][0] * f1(x, y) + a[1][1] * f2(x, y);
		miss << fabs(dx) << " "<< fabs(dy) << endl;
		x -= dx;
		y -= dy;
		norm = sqrt(f1(x, y) * f1(x, y) + f2(x, y) * f2(x, y));

		cout << fixed << setw(3) << i << "\t" << setw(10) << setprecision(9) << x << "\t" << setw(10) << setprecision(7) << y << "\t" << setw(10) << setprecision(7) << f1(x, y) << "\t" << setprecision(7) << f2(x, y) << endl;
		i++;
	} while (norm >= eps);
	miss.close();
	cout << "X = " << x << endl << "Y = " << y << endl; // Вивід розвязку
	return i - 1;
}


// Вивiд графiка функцiй
void drawGraph() {
	ofstream com("commands.txt"); // Запис команд до файлу для гнуплот
	com << "set key right center" << endl;
	com << "set title 'Розв`язування систем нелінійних рівнянь.'" << endl;
	com << "set xrange[-1:1]" << endl;
	com << "plot (asin(-x)) title 'f1', (- x / 100 ) title 'f2'";
	com.close();
	system("\"C:\\gnuplot\\bin\\wgnuplot.exe -p\" commands.txt");
}


// Вивiд дiаграми
void drawDiagram() {
	ofstream com("commands.txt");
	com << endl << "set grid ytics" << endl;
	com << "set xtics('1' 0, '2' 1, '3' 2, '4' 3)" << endl << "set style data boxes" << endl << "set boxwidth 0.6 absolute" << endl;
	com << "set style fill solid 1"  << endl << "plot 'miss.log' u 1 title '|xk - xk-1|', 'miss.log' u 2 title '|yk - yk-1|'" << endl;
	com.close();
	system("\"C:\\gnuplot\\bin\\wgnuplot.exe -p\" commands.txt"); 
}
