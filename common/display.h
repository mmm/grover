// display.h

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "myvalarray.h"

extern void printVals( const double x, const valarray<double>& y );
extern void showProgress( const int step, const int numSteps );
extern void printDensityMatrix( const double x, const valarray<double>& y );

#endif // _DISPLAY_H_
