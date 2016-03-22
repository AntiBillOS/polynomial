#include "polynomial.h"
#include <cstdlib>
#include <iostream>
#include <complex>
using namespace std;

int main () {
	setlocale(LC_ALL, "Russian");
	Polynomial<complex<double> > P1,P2;
	cout << "¬ведите P1 и P2\n";
	cout << "в формате {a, b, c, ...}, где a, b, с ... точки полинома\n";
	cout << "комплексные коефиценты ввод€тс€ в формате: дл€ 4+i - (0,4)\n";
	cin >> P1 >> P2;
	cout << "P1 + P2 = " << P1 + P2 << endl;
	cout << "P1 - P2 = " << P1 - P2 << endl;
	cout << "P1 * P2 = " << P1 * P2 << endl;
	cout << "P1 / P2 = " << P1 / P2 << endl;
	cout << "P1 % P2 = " << P1 % P2 << endl;
	cout << "¬ведите x\n";
	double x;
	cin >> x;
	cout << "P1 (x) = " << P1.value(x) << endl;
	cout << "P2 (x) = " << P2.value(x) << endl;
	system("pause");
	return 0;
}
