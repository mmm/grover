#define _POSIX_SOURCE 1
// derivs.C
//
#include <stdexcept>
#include "myvalarraydouble.h"

#include "derivs.h"


// return dy/dx for each particular equation
valarray_double dydx( const double x, const valarray_double& y ) {

    valarray_double tmpdydx(0.0,y.size());
    try {
        tmpdydx[0] = y[1];
        tmpdydx[1] = - y[0];
        
        //for ( unsigned int i = 0; i < y.size(); i++ ) {
        //    tmpdydx[i] = ( 1.0 - x + 4.0 * y[i] );
        //}
    }
    catch(out_of_range) {
        cerr << "oops" << endl;
        exit(1);
    }

    return tmpdydx;

//    return 1.0 - x + 4.0 * y;

}
