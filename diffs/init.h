// init.h

#ifndef _INIT_H_
#define _INIT_H_

const int NUM_OF_EQNS = 4;

#include <valarray>
extern void init( double *const x, valarray<double> *const y );
extern void perturb( double *const x, valarray<double> *const y );

#endif //_INIT_H_
