// derivs.h

#ifndef _DERIVS_H_
#define _DERIVS_H_

#include <valarray>

using namespace std;
extern valarray<double> dydx( const double x, const valarray<double>& y );

#endif //_DERIVS_H_
