#define _POSIX_SOURCE 1
// init.C
//
#include <stdexcept>
#include "myvalarray.h"

#include "derivs.h"


// initialize variables...
void init( double *const x, valarray<double> *const y ) {
    *x = 0.0;

    if ( y->size() != 4 ) throw;

    valarray<double>& ry = *y;
    try {
        // slices would be easier, but oh well...
        double z = 0.0;
        double p = 1.0;
        double zbar = 0.0;
        double pbar = -1.0;
        ry[0] = z;
        ry[1] = p;
        ry[2] = zbar;
        ry[3] = pbar;
    }
    catch(out_of_range) {
        cerr << "oops" << endl;
        exit(1);
    }
}
