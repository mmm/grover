#define _POSIX_SOURCE 1
// cf.C
//
#include <iostream>
#include <math.h> // cos
#include <valarray>

#include "cf.h"

void compareWithSoln( const double x, const valarray<double>& y ) {

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

void printVals( const double x, const valarray<double>& y ) {
#ifdef TELL_ME
    //cout << "x= " << x << "\t y= " << y[0] << "\t ";
    //cout << x << " " << y[0] << " " << y[1] << endl;
    cout << x << " " << y[0] << " " << y[1] << " " 
         //<< y*y 
         << y[0] * y[0] + y[1] * y[1]
         << endl;
    //cout << y[0] << " " << y[1] << endl;
#endif //TELL_ME
}
