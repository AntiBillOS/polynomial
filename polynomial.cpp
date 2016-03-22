#include "Polynomial.h"
#include <string>
#include <algorithm>
using namespace std;

template <class T> Polynomial <T>::Polynomial  (T *arg, int count) {
	for (int i = 0; i < count; i ++)
		coeff.push_back(arg[i]);
	balance();
}

template <class T> T Polynomial <T>::value (T x) const {
	T cur = 1,res = 0;
	for (int i = 0; i < coeff.size(); i ++) {
		res += cur * coeff[i];
		cur *= x;
	}
	return res;
}

template <class T> void Polynomial <T>::balance () {
	int x;
	for (x = coeff.size() - 1; x > 0; x --)
		if (abs(coeff[x] - T(0)) >= eps) break;
	coeff.resize(x + 1);
	if (coeff.size() == 0) coeff.push_back(0);
}

template <class T> unsigned int Polynomial <T>::degree () const {
	return coeff.size() - 1;
}

template <class T> Polynomial<T>& Polynomial<T>::operator+= (const Polynomial <T> & arg) {
	int m = min(coeff.size(),arg.coeff.size());
	for (int i = 0; i < m; i ++)
		coeff[i] += arg.coeff[i];
	for (int i = m; i < arg.coeff.size(); i ++)
		coeff.push_back(arg.coeff[i]);
	balance();
	return *this;
}

template <class T> Polynomial<T>& Polynomial <T>::operator-= (const Polynomial <T> & arg) {
	int m = min(coeff.size(),arg.coeff.size());
	for (int i = 0; i < m; i ++)
		coeff[i] -= arg.coeff[i];
	for (int i = m; i < arg.coeff.size(); i ++)
		coeff.push_back(arg.coeff[i]);
	balance();
	return *this;
}

template <class T> Polynomial<T>& Polynomial <T> ::operator*= (const Polynomial <T> & arg) {
	int old_size = coeff.size();
	coeff.resize(old_size + arg.coeff.size() + 1);
	for (int i = coeff.size() - 1; i >= old_size; i --) coeff[i] = 0;
	for (int i = old_size - 1; i >= 0; i --) {
		for (int j = arg.coeff.size() - 1; j > 0; j --) 	
			coeff[i + j] += coeff[i] * arg.coeff[j];
		coeff[i] = coeff[i] * arg.coeff[0];
	}
	balance();
	return *this;
}

template <class T> Polynomial<T>& Polynomial <T>::minus_offset (const Polynomial <T> & arg) {
	if (arg.coeff.size() > coeff.size()) return *this;
	for (int i = 1; i <= arg.coeff.size(); i ++) 
		coeff[coeff.size() - i] -= arg.coeff[arg.coeff.size() - i];
	balance();
	return *this;
}


template <class T> Polynomial<T>& Polynomial <T>::operator%= (const Polynomial <T> & arg) {
	for (int i = coeff.size() - 1; i >= (int) arg.coeff.size() - 1; i --) {
		this->minus_offset(arg * (coeff[i] / arg.coeff[arg.coeff.size() - 1]));
	}
	return *this;
}

template <class T> Polynomial<T>& Polynomial <T>::operator/= (const Polynomial <T> & arg) {
	Polynomial <T>  c;
	c.coeff.clear();
	for (int i = coeff.size() - 1; i >= (int) arg.coeff.size() - 1; i --) {
		c.coeff.push_back(coeff[i] / arg.coeff[arg.coeff.size() - 1]);
		this->minus_offset(arg * (coeff[i] / arg.coeff[arg.coeff.size() - 1]));
	}
	reverse(c.coeff.begin(),c.coeff.end());
	c.balance();
	return *this = c;
}

template <class T> Polynomial <T>  operator- (const Polynomial <T>& arg) {
	Polynomial <T>  res;
	res.coeff.resize(arg.coeff.size());
	for (int i = 0; i < res.coeff.size(); i ++)
		res.coeff[i] = -arg.coeff[i];
	return res;
}


template <class T> ostream& operator<< (ostream& out, const Polynomial <T> & arg) {
	out << "{";
	for (int i = 0; i < arg.coeff.size() - 1; i ++) 
		out << arg.coeff[i] << ",";
	out << arg.coeff[arg.coeff.size() - 1] << "}";
	return out;
}

template <class T> istream& operator>> (istream& in, Polynomial <T> & arg) {
	char c;
	do in >> c; while (isspace(c));
	if (c != '{') {
		in.exceptions(istream::badbit);
		return in;
	}
	arg.coeff.clear();
	for (int i = 0; true; i ++) {
		T x; in >> x;
		arg.coeff.push_back(x);
		do in >> c; while (isspace(c));
		if (c == '}') break;
		if (c != ',') {
			in.exceptions(istream::badbit);
			return in;
		}
	}
	arg.balance();
	return in;
}


template <class T> Polynomial <T>  operator+ (const Polynomial <T> & a, const Polynomial <T> & b) {
	Polynomial <T>  c = a;
	c += b;
	return c;
}

template <class T> Polynomial <T>  operator- (const Polynomial <T> & a, const Polynomial <T> & b) {
	Polynomial <T>  c = a;
	c -= b;
	return c;
}

template <class T> Polynomial <T>  operator* (const Polynomial <T> & a, const Polynomial <T> & b) {
	Polynomial <T>  c = a;
	c *= b;
	return c;
}

template <class T> Polynomial <T>  operator% (const Polynomial <T> & a, const Polynomial <T> & b) {
	Polynomial <T>  c = a;
	c %= b;
	return c;
}

template <class T> Polynomial <T>  operator/ (const Polynomial <T> & a, const Polynomial <T> & b) {
	Polynomial <T>  c = a;
	c /= b;
	return c;
}
