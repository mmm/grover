// cf.h

#ifndef _CF_H_
#define _CF_H_

#include <valarray>

using namespace std;

extern void compareWithSoln( const double x, const std::valarray<double>& y );
extern void printVals( const double x, const std::valarray<double>& y );
extern void showProgress( const int step, const int numSteps );

#endif // _CF_H_

