#define _POSIX_SOURCE 1
// init.C
//
#include <stdexcept>
#include "myvalarraydouble.h"

#include "derivs.h"


// initialize variables...
void init( double *const x, valarray_double *const y ) {
    *x = 0.0;

    const int n = y->size() / 4;

    valarray_double& ry = *y;
    try {
        // slices would be easier, but oh well...
        valarray_double z(0.0, n);
        valarray_double w(1.0, n);
        valarray_double zbar(0.0, n);
        valarray_double wbar(1.0, n);
        for( int i = 0; i<n; i++ ) {
            ry[i] = z[i];
            ry[n+i] = w[i];
            ry[2*n+i] = zbar[i];
            ry[3*n+i] = wbar[i];
            //z[i] = ry[i];
            //w[i] = ry[n+i];
            //zbar[i] = ry[2*n+i];
            //wbar[i] = ry[3*n+i];
        }
    }
    catch(out_of_range) {
        cerr << "oops" << endl;
        exit(1);
    }
}
