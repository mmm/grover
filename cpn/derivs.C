#define _POSIX_SOURCE 1
// derivs.C
//
#include <stdexcept>
#include "myvalarraydouble.h"

#include "derivs.h"


// return dy/dx for each particular equation
valarray_double dydx( const double x, const valarray_double& y ) {

    if ( y.size() % 4 ) throw;

    const int n = y.size() / 4;


    valarray_double tmpdydx(0.0,y.size());
    try {
        // slices would be easier, but oh well...
        valarray_double z(0.0, n);
        valarray_double p(0.0, n);
        valarray_double zbar(0.0, n);
        valarray_double pbar(0.0, n);
        for( int i = 0; i<n; i++ ) {
            z[i] = y[i];
            p[i] = y[n+i];
            zbar[i] = y[2*n+i];
            pbar[i] = y[3*n+i];
        }
        
        valarray_double zdot(0.0, n);
        for( int i = 0; i<n; i++ ) {
            zdot[i] = ( 1 + z*zbar ) * ( pbar[i] + (pbar*zbar)*z[i] ); 
        }
        valarray_double pdot(0.0, n);
        for( int i = 0; i<n; i++ ) {
            pdot[i] = 2 * zbar[i] * ( p*pbar + (p*z)*(pbar*zbar) ) +
                ( 1 + z*zbar ) * ( (pbar*zbar)*z[i] );
        }
        valarray_double zbardot(0.0, n);
        for( int i = 0; i<n; i++ ) {
            zbardot[i] = ( 1 + z*zbar ) * ( p[i] + (p*z)*zbar[i] ); 
        }
        valarray_double pbardot(0.0, n);
        for( int i = 0; i<n; i++ ) {
            pbardot[i] = 2 * z[i] * ( p*pbar + (p*z)*(pbar*zbar) ) +
                ( 1 + z*zbar ) * ( (p*z)*zbar[i] );
        }

        // recombine into tmpdydx... again, slices would be easier
        for( int i = 0; i<n; i++ ) {
            tmpdydx[i] = zdot[i];
            tmpdydx[n+i] = pdot[i];
            tmpdydx[2*n+i] = zbardot[i];
            tmpdydx[3*n+i] = pbardot[i];
        }

    }
    catch(out_of_range) {
        cerr << "oops" << endl;
        exit(1);
    }

    return tmpdydx;

}
