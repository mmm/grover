// derivs.C
//
#include <iostream>
#include <stdexcept>
#include <valarray>
#include <numeric>

#include "derivs.h"

using namespace std;

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
        double zdotzbar = 
            std::inner_product(&z[0],&z[z.size()],&zbar[0],double(0));
        double wdotw = 
            std::inner_product(&w[0],&w[w.size()],&w[0],double(0));
        double zdotw = 
            std::inner_product(&z[0],&z[z.size()],&w[0],double(0));
        double zbardotw = 
            std::inner_product(&zbar[0],&zbar[zbar.size()],&w[0],double(0));
        double zbardotzbar = 
            std::inner_product(&zbar[0],&zbar[zbar.size()],&zbar[0],double(0));
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
        double wbardotwbar = 
            std::inner_product(&wbar[0],&wbar[wbar.size()],&wbar[0],double(0));
        double zbardotwbar = 
            std::inner_product(&zbar[0],&zbar[zbar.size()],&wbar[0],double(0));
        double zdotwbar = 
            std::inner_product(&z[0],&z[z.size()],&wbar[0],double(0));
        double zdotz = 
            std::inner_product(&z[0],&z[z.size()],&z[0],double(0));
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
