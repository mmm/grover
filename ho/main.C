#define _POSIX_SOURCE 1
// want to integrate ODEs
//
#include <iostream>
#include "myvalarray.h"
//#include "euler.h"
#include "rk4.h"
//#include "adaptRk4.h"
//#include "lsodeStepper.h"

#include "derivs.h"
#include "init.h"
#include "cf.h"


int main() {

    // initial conditions
    double x = 0.0;
    valarray<double> y( 0.0, NUM_OF_EQNS );
    init( &x, &y );

//    cout << y.size() 
//         << " "
//         << y[0]
//         << " "
//         << y[1]
//         << endl;

    // some setup
    const int numSteps = 1000000; 
    //double stepSize = 1/(double)numSteps;
    double stepSize = 0.001;

    for ( int i = 0; i < numSteps; i++ ){

        // take a step
        //stepEuler( &x, &y, stepSize );
        //stepAdaptRk4( &x, &y, &stepSize );
        //stepLsode( &x, &y, &stepSize );

        y += stepRk4( x, y, stepSize );
        x += stepSize;

#ifdef TELL_ME
//        // we can solve this one, so...
//        if ( 0 == i%(numSteps/10) ) { 
//            compareWithSoln( x, y );
//        }
//        printVals( x, y );
        
//        char line[80];
//        cin.getline(line,80);

        showProgress( i, numSteps );
#endif //TELL_ME

    }

}
