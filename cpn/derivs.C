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
        valarray_double w(0.0, n);
        valarray_double zbar(0.0, n);
        valarray_double wbar(0.0, n);
        for( int i = 0; i<n; i++ ) {
            z[i] = y[i];
            w[i] = y[n+i];
            zbar[i] = y[2*n+i];
            wbar[i] = y[3*n+i];
        }
        
        valarray_double zdot(w);
        //valarray_double zdot(0.0, n);
        //zdot = w;

        valarray_double wdot(0.0, n);
        for( int i = 0; i<n; i++ ) {
            wdot[i] = 
                ( zbar[i] * ( 
                    ( 1 + z*zbar )*(w*w) - 2*(z*w)*(zbar*w)
                  )
                  + w[i] * (
                      ( 1 + z*zbar )*(zbar*w)
                    )
                  + z[i] * (
                      ( 1 + z*zbar )*(
                          (zbar*w)*(zbar*w)
                          + (zbar*zbar)*(w*w)
                      )
                      - 2*(zbar*zbar)*(z*w)*(zbar*w)
                    )
                ) / ( 1 + z*zbar )*( 1 + z*zbar );
        }

        valarray_double zbardot(wbar);
        //valarray_double zbardot(0.0, n);
        //zbardot = wbar;

        valarray_double wbardot(0.0, n);
        for( int i = 0; i<n; i++ ) {
            wbardot[i] = 
                ( z[i] * ( 
                    ( 1 + z*zbar )*(wbar*wbar) - 2*(zbar*wbar)*(z*wbar)
                  )
                  + wbar[i] * (
                      ( 1 + z*zbar )*(z*wbar)
                    )
                  + zbar[i] * (
                      ( 1 + z*zbar )*(
                          (z*wbar)*(z*wbar)
                          + (z*z)*(wbar*wbar)
                      )
                      - 2*(z*z)*(zbar*wbar)*(z*wbar)
                    )
                ) / ( 1 + z*zbar )*( 1 + z*zbar );
        }

        // recombine into tmpdydx... again, slices would be easier
        for( int i = 0; i<n; i++ ) {
            tmpdydx[i] = zdot[i];
            tmpdydx[n+i] = wdot[i];
            tmpdydx[2*n+i] = zbardot[i];
            tmpdydx[3*n+i] = wbardot[i];
        }

    }
    catch(out_of_range) {
        cerr << "oops" << endl;
        exit(1);
    }

    return tmpdydx;

}
