#define _POSIX_SOURCE 1
// derivs.C
//
#include <stdexcept>
#include <valarray>

#include "derivs.h"


double std::operator*( const valarray<double>& a, const valarray<double>& b ) {

    if ( a.size() != b.size() ) throw;

    double sum = 0.0;
    for ( unsigned int i = 0; i < a.size(); i++ ) {
        sum += a[i]*b[i];
    }

    return sum;

}

// return dy/dx for each particular equation
valarray<double> dydx( const double x, const valarray<double>& y ) {

    if ( y.size() % 4 ) throw;

    const int n = y.size() / 4;


    valarray<double> tmpdydx(0.0,y.size());
    try {
        // slices would be easier, but oh well...
        valarray<double> z(0.0, n);
        valarray<double> w(0.0, n);
        valarray<double> zbar(0.0, n);
        valarray<double> wbar(0.0, n);
        for( int i = 0; i<n; i++ ) {
            z[i] = y[i];
            w[i] = y[n+i];
            zbar[i] = y[2*n+i];
            wbar[i] = y[3*n+i];
        }
        
        valarray<double> zdot(w);
        //valarray<double> zdot(0.0, n);
        //zdot = w;

        valarray<double> wdot(0.0, n);
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

        valarray<double> zbardot(wbar);
        //valarray<double> zbardot(0.0, n);
        //zbardot = wbar;

        valarray<double> wbardot(0.0, n);
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
