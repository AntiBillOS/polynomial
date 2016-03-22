#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

template <class T> class Polynomial {
private:
	static const double eps = 0.00000000001;
	vector <T> coeff;
	Polynomial <T> & minus_offset (const Polynomial <T> &);
	void balance ();
public:
	Polynomial (T arg = 0) {coeff.push_back(arg);}
	Polynomial (T *arg, int count);
	T value (T) const;
	unsigned int degree () const;
	Polynomial <T>& operator+= (const Polynomial <T> &);
	Polynomial <T>& operator-= (const Polynomial <T> &);
	Polynomial <T>& operator*= (const Polynomial <T> &);
	Polynomial <T>& operator/= (const Polynomial <T> &);
	Polynomial <T>& operator%= (const Polynomial <T> &);
	template <class TT> friend Polynomial <TT>  operator- (const Polynomial <TT> &);
	template <class TT> friend ostream& operator<< (ostream&,const Polynomial <TT> &);
	template <class TT> friend istream& operator>> (istream&,Polynomial <TT> &);
};		

template <class T> Polynomial <T>  operator/ (const Polynomial <T> &,const Polynomial <T> &);
template <class T> Polynomial <T>  operator+ (const Polynomial <T> &,const Polynomial <T> &);
template <class T> Polynomial <T>  operator- (const Polynomial <T> &,const Polynomial <T> &);
template <class T> Polynomial <T>  operator* (const Polynomial <T> &,const Polynomial <T> &);
template <class T> Polynomial <T>  operator% (const Polynomial <T> &,const Polynomial <T> &);

inline double abs (double a) {
	return a > 0 ? a : -a;
}


#endif
