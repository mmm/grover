#define _POSIX_SOURCE 1
// derivs.C
//
#include <stdexcept>
#include "myvalarray.h"

#include "derivs.h"

// return dy/dx for each particular equation
valarray<double> dydx( const double x, const valarray<double>& y ) {

    if ( y.size() % 4 ) throw;

    const int n = y.size() / 4;


    valarray<double> tmpdydx(0.0,y.size());
    try {
        // slices would be easier, 
//        slice_array<double>& z = y[slice(0,n-1,1)];
//        slice_array<double>& w = y[slice(n,2*n-1,1)];
//        slice_array<double>& zbar = y[slice(2*n,3*n-1,1)];
//        slice_array<double>& wbar = y[slice(3*n,4*n-1,1)];
        //but oh well...
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

        valarray<double> wdot(0.0, n);
        // calculate dot products first...
        double zdotzbar = z*zbar;
        double wdotw = w*w;
        double zdotw = z*w;
        double zbardotw = zbar*w;
        double zbardotzbar = zbar*zbar;
        for( int i = 0; i<n; i++ ) {
            wdot[i] = 
                ( zbar[i] * ( 
                    ( 1 + zdotzbar )*(wdotw) - 2*(zdotw)*(zbardotw)
                  )
                  + w[i] * (
                      ( 1 + zdotzbar )*(zbardotw)
                    )
                  + z[i] * (
                      ( 1 + zdotzbar )*(
                          (zbardotw)*(zbardotw)
                          + (zbardotzbar)*(wdotw)
                      )
                      - 2*(zbardotzbar)*(zdotw)*(zbardotw)
                    )
                ) / ( 1 + zdotzbar )*( 1 + zdotzbar );
        }

        valarray<double> zbardot(wbar);

        valarray<double> wbardot(0.0, n);
        // calculate dot products first...
        double wbardotwbar = wbar*wbar;
        double zbardotwbar = zbar*wbar;
        double zdotwbar = z*wbar;
        double zdotz = z*z;
        for( int i = 0; i<n; i++ ) {
            wbardot[i] = 
                ( z[i] * ( 
                    ( 1 + zdotzbar )*(wbardotwbar) - 2*(zbardotwbar)*(zdotwbar)
                  )
                  + wbar[i] * (
                      ( 1 + zdotzbar )*(zdotwbar)
                    )
                  + zbar[i] * (
                      ( 1 + zdotzbar )*(
                          (zdotwbar)*(zdotwbar)
                          + (zdotz)*(wbardotwbar)
                      )
                      - 2*(zdotz)*(zbardotwbar)*(zdotwbar)
                    )
                ) / ( 1 + zdotzbar )*( 1 + zdotzbar );
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
