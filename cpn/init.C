#define _POSIX_SOURCE 1
// init.C
//
#include <stdexcept>
#include <cmath> // pow
#include "myvalarray.h"

#include "init.h"

int numQubits = 8;

// initialize variables...
void init( double *const x, valarray<double> *const y ) {
    *x = 0.0;

    if ( y->size() % 4 ) throw;
    const int n = y->size() / 4;

    valarray<double>& ry = *y;
    try {
        // slices would be easier, but oh well...
        //valarray<double> z(1.0/(double)n, n);
        //valarray<double> z(1.0/sqrt( pow(2,n) ), n);
        valarray<double> z(1.0, n);
        valarray<double> p(0.0, n);
        p[0] = 0.1;
        //valarray<double> zbar(1.0/sqrt( pow(2,n) ), n);
        valarray<double> zbar(1.0, n);
        valarray<double> pbar(0.0, n);
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

extern const int getNumOfEqns( const int numBits ) {

    return (const int) 4 * ( (int)pow( 2, numBits ) - 1 );
    //return (const int) pow( 2, numBits + 1 );

}
