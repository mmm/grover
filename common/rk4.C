#define _POSIX_SOURCE 1
// rk4.C

#include "derivs.h"
#include "rk4.h"

// external fns

//extern void stepRk4( double *const x, double *const y, const double stepSize ) {
//    
//    double k1 = stepSize * dydx( *x, *y );
//    double k2 = stepSize * dydx( *x + stepSize/2.0, *y + k1/2.0 );
//    double k3 = stepSize * dydx( *x + stepSize/2.0, *y + k2/2.0 );
//    double k4 = stepSize * dydx( *x + stepSize, *y + k3 );
//
//    *y += k1/6.0 + k2/3.0 + k3/3.0 + k4/6.0;
//    *x += stepSize;
//
//}

extern valarray_double stepRk4( const double x, const valarray_double& y, const double stepSize ) {
    
    valarray_double k1 = stepSize * dydx( x, y );
    valarray_double k2 = stepSize * dydx( x + stepSize/2.0, y + k1/2.0 );
    valarray_double k3 = stepSize * dydx( x + stepSize/2.0, y + k2/2.0 );
    valarray_double k4 = stepSize * dydx( x + stepSize, y + k3 );

    return k1/6.0 + k2/3.0 + k3/3.0 + k4/6.0;

}
