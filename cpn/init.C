#define _POSIX_SOURCE 1
// init.C
//
#include <stdexcept>
#include "myvalarray.h"

#include "derivs.h"


// initialize variables...
void init( double *const x, valarray<double> *const y ) {
    *x = 0.0;

    if ( y->size() % 4 ) throw;
    const int n = y->size() / 4;

    valarray<double>& ry = *y;
    try {
        // slices would be easier, but oh well...
        //valarray<double> z(1.0/(double)n, n);
        valarray<double> z(1.0/sqrt(n), n);
        valarray<double> p(1.0, n);
        valarray<double> zbar(0.0, n);
        valarray<double> pbar(1.0, n);
        for( int i = 0; i<n; i++ ) {
            ry[i] = z[i];
            ry[n+i] = p[i];
            ry[2*n+i] = zbar[i];
            ry[3*n+i] = pbar[i];
            //z[i] = ry[i];
            //p[i] = ry[n+i];
            //zbar[i] = ry[2*n+i];
            //pbar[i] = ry[3*n+i];
        }
    }
    catch(out_of_range) {
        cerr << "oops" << endl;
        exit(1);
    }
}
