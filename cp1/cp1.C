#define _POSIX_SOURCE 1
// cp1.C  want to integrate geodesic equations of motion 
// for the Fubini--Study metric on CP^1
//
#include <stdexcept>
#include "cp1.h"
#include "myvalarraydouble.h"


// return dy/dx for each particular equation
valarray_double dydx( const double x, const valarray_double& y ) {

    valarray_double dydx(0.0,y.size());
    try {
        for ( unsigned int i = 0; i < y.size(); i++ ) {
            dydx[i] = ( 1.0 - x + 4.0 * y[i] );
        }
    }
    catch(out_of_range) {
        cerr << "oops" << endl;
        exit(1);
    }

    return dydx;

//    return 1.0 - x + 4.0 * y;

}
