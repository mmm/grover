#define _POSIX_SOURCE 1
// derivs.C
//
#include <stdexcept>
#include <valarray>

#include "derivs.h"


// return dy/dx for each particular equation
valarray<double> dydx( const double x, const valarray<double>& y ) {

    valarray<double> tmpdydx(0.0,y.size());
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
