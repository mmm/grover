// cf.h

#ifndef _CF_H_
#define _CF_H_

#include "myvalarraydouble.h"

extern void compareWithSoln( const double x, const valarray_double& y );
extern void printVals( const double x, const valarray_double& y );
extern void printDiffs( const double x, const valarray_double& y1, const valarray_double& y2 );
extern void printDeriv( const double xold, const double xnew, const valarray_double& dytmp,
                 const valarray_double& y1, const valarray_double& y2 );

#endif // _CF_H_
