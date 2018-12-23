#include "Spline.h"

using namespace std;

Spline::Spline(vector <float> &x, vector <float> &y): myX(x), myY(y)
{
	int n = x.size() - 1;		// Amount of space between points

	vector <float> a;
	vector <float> b(n);
	vector <float> d(n);

	float h = x[1] - x[0];		// Step between points

	a.insert(a.begin(), y.begin(), y.end());

	// Finding A[]
	vector <float> alpha(n);
	for (int i = 1; i < n; i++) {
		alpha[i] = 3. / h * (a[i + 1] - 2 * a[i] + a[i - 1]);
	}

	vector <float> c(n + 1);
	vector <float> l(n + 1);
	vector <float> m(n + 1);
	vector <float> z(n + 1);

	// Finding coefficients
	l[0] = 1;
	m[0] = 0;
	z[0] = 0;

	for (int i = 1; i < n; ++i) {
		l[i] = h * (4 - m[i - 1]);
		m[i] = h / l[i];
		z[i] = (alpha[i] - h * z[i - 1]) / l[i];
	}

	l[n] = 1;
	z[n] = 0;
	c[n] = 0;

	for (int i = n - 1; i >= 0; --i) {
		c[i] = z[i] - m[i] * c[i + 1];
		b[i] = (a[i + 1] - a[i]) / h - h * (c[i + 1] + 2 * c[i]) / 3;
		d[i] = (c[i + 1] - c[i]) / 3 / h;
	}

	// Saving the results to struct
	coeff.resize(n);
	for (int i = 0; i < n; ++i) {
		coeff[i].a = a[i];
		coeff[i].b = b[i];
		coeff[i].c = c[i];
		coeff[i].d = d[i];
		coeff[i].x = x[i];
	}
}

// Return value of y in point x
float Spline::getY(float x) {
	int i = 0;
	while (i < (int)coeff.size() - 1 && coeff[i].x < x) { i++; }	// Finding rigth diapason
	float dx = x - coeff[i].x;
	return coeff[i].a + coeff[i].b * dx + coeff[i].c * dx* dx + coeff[i].d * dx* dx * dx;
}


