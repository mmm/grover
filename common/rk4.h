// rk4.h

#ifndef _RK4_H_
#define _RK4_H_

#include <valarray>
using std::valarray;

extern valarray<double> 
stepRk4( const double x, const valarray<double>& y, const double stepSize );

#endif //_RK4_H_
