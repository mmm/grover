#define _POSIX_SOURCE 1
// euler.C

#include "euler.h"

// static fns

static double dydx( const double x, const double y ) {

    return 1 - x + 4 * y;

}




// external fns

void stepEuler( double *const x, double *const y, const double stepSize ) {

    *y += stepSize * dydx( *x, *y );
    *x += stepSize;

}
