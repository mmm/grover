// cf.h

#ifndef _CF_H_
#define _CF_H_

#include <valarray>

extern void compareWithSoln( const double x, const valarray<double>& y );
extern void printVals( const double x, const valarray<double>& y );
extern void printDiffs( const double x, const valarray<double>& y1, const valarray<double>& y2 );
extern void printDeriv( const double xold, const double xnew, const valarray<double>& dytmp,
                 const valarray<double>& y1, const valarray<double>& y2 );

#endif // _CF_H_
