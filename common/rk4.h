// rk4.h

#ifndef _RK4_H_
#define _RK4_H_

#include "myvalarraydouble.h"

//extern void stepRk4( double *const x, valarray<double> *const y, const double stepSize );
extern valarray_double stepRk4( const double x, const valarray_double& y, const double stepSize );

#endif //_RK4_H_
