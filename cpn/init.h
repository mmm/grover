// init.h

#ifndef _INIT_H_
#define _INIT_H_

//const int numQubits = 8;
extern int numQubits;
//const int NUM_OF_EQNS = 1024;

#include "myvalarray.h"
extern void init( double *const x, valarray<double> *const y );
extern const int getNumOfEqns( const int numBits );

#endif //_INIT_H_
