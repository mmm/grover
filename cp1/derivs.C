#define _POSIX_SOURCE 1
// derivs.C
//
#include <stdexcept>
#include "myvalarray.h"

#include "derivs.h"


// return dy/dx for each particular equation
valarray<double> dydx( const double x, const valarray<double>& y ) {

    if ( y.size() != 4 ) throw;

    valarray<double> tmpdydx(0.0,y.size());
    try {
        // slices would be easier, but oh well...
        double z = y[0];
        double p = y[1];
        double zbar = y[2];
        double pbar = y[3];
        
        double zdot = ( 1 + z*zbar ) * ( pbar + (pbar*zbar)*z );
        double pdot = 2 * zbar * ( p*pbar + (p*z)*(pbar*zbar) ) +
            ( 1 + z*zbar ) * ( (pbar*zbar)*z );
        double zbardot = ( 1 + z*zbar ) * ( p + (p*z)*zbar );
        double pbardot = 2 * z * ( p*pbar + (p*z)*(pbar*zbar) ) +
            ( 1 + z*zbar ) * ( (p*z)*zbar );

        // recombine into tmpdydx... again, slices would be easier
        tmpdydx[0] = zdot;
        tmpdydx[1] = pdot;
        tmpdydx[2] = zbardot;
        tmpdydx[3] = pbardot;

    }
    catch(out_of_range) {
        cerr << "oops" << endl;
        exit(1);
    }

    return tmpdydx;

}
