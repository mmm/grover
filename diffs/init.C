#define _POSIX_SOURCE 1
// init.C
//
#include <stdexcept>
#include "myvalarraydouble.h"

#include "derivs.h"


// initialize variables...
void init( double *const x, valarray_double *const y ) {
    *x = 0.0;

    if ( y->size() % 4 ) throw;
    const int n = y->size() / 4;

    valarray_double& ry = *y;
    try {
        // slices would be easier, but oh well...
        valarray_double z(0.0, n);
        valarray_double p(1.0, n);
        valarray_double zbar(0.0, n);
        valarray_double pbar(1.0, n);
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


// perturb variables...
void perturb( double *const x, valarray_double *const y ) {
    *x = 0.0;

    if ( y->size() % 4 ) throw;
    const int n = y->size() / 4;

    valarray_double& ry = *y;
    try {
        // slices would be easier, but oh well...
        valarray_double z(0.01, n);
        valarray_double p(1.0, n);
        valarray_double zbar(0.01, n);
        valarray_double pbar(1.0, n);
        for( int i = 0; i<n; i++ ) {
            ry[i] = z[i];
// leave p's alone for now...
//            ry[n+i] = p[i];
            ry[2*n+i] = zbar[i];
//            ry[3*n+i] = pbar[i];
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
