#define _POSIX_SOURCE 1
// cf.C
//
#include <iostream>
#include <math.h> // cos
#include "myvalarraydouble.h"

#include "cf.h"

void compareWithSoln( const double x, const valarray_double& y ) {

    // set precision...
    //cout.

    double y_soln = cos( x );

#ifdef TELL_ME
        cout << "x= " << x << "\t y= " << y[0] << "\t ";

        cout << "Soln differs by " 
             << y[0] - y_soln << endl;
//        cout << "exact y= " << y_soln << endl;
#endif //TELL_ME

}

void printVals( const double x, const valarray_double& y ) {
#ifdef TELL_ME
    cout << x 
        //<< " z= " 
         << " " 
         << y[0] 
         << " " 
        //<< " zbar= " 
         << y[2] 
         << " " 
        // << " w= " 
         << y[1] 
         << " " 
        //<< " wbar= " 
         << y[3] 
         << endl;
#endif //TELL_ME
}

double calcDiff( const double x, const valarray_double& y1, const valarray_double& y2 ) {
    return 0.0;
}


void printDiffs( const double x, const valarray_double& y1, const valarray_double& y2 ) {
#ifdef TELL_ME
    cout << x 
         << " " 
         << y2[0] - y1[0]  // z
         << " " 
         << y2[2] - y1[2]  // zbar
         << " "
         << endl;
#endif //TELL_ME
}

void printDeriv( const double xold, const double xnew, const valarray_double& dytmp,
                 const valarray_double& y1, const valarray_double& y2 ) {

    valarray_double deriv( 0.0, NUM_OF_EQNS );
#ifdef TELL_ME
    cout << xold
         << " " 
         << y2[0] - y1[0]  // z
         << " " 
         << y2[2] - y1[2]  // zbar
         << " "
         << endl;
#endif //TELL_ME
}
