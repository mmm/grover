#define _POSIX_SOURCE 1
// want to integrate ODEs
//
#include "myvalarray.h"
#include "rk4.h"

#include "init.h"
#include "cf.h"


int main() {

    // initial conditions
    double x = 0.0;
    double xtmp = 0.0;
    valarray<double> y1( 0.0, NUM_OF_EQNS );
    valarray<double> y2( 0.0, NUM_OF_EQNS );
    valarray<double> dytmp( 0.0, NUM_OF_EQNS );
    init( &x, &y1 );
    init( &x, &y2 );
    perturb( &x, &y2 );

    // some setup
    const int numSteps = 10000; 
    double stepSize = .5 * 1/(double)numSteps;
    //double stepSize = 0.001;

    for ( int i = 0; i < numSteps; i++ ){

        // take a step
        y1 += stepRk4( x, y1, stepSize );
        y2 += stepRk4( x, y2, stepSize );
        x += stepSize;

#ifdef TELL_ME
        //printVals( x, y1 );
        //printVals( x, y2 );
        //printDiffs( x, y1, y2 );
        printDeriv( xtmp, x, dytmp, y1, y2 );

        // wait between each line
//        char line[80];
//        cin.getline(line,80);

#endif //TELL_ME


    }

}
