#define _POSIX_SOURCE 1
// want to integrate ODEs
//
#include <unistd.h> // getopt
#include "myvalarray.h"
#include "rk4.h"

#include "init.h"
#include "display.h"


void usage( void ) {
    cout << "Usage: stepper [-q num-qubits] [-n num-steps]" 
         << endl;
    exit(1);
}

int main( int argc, char* argv[] ) {

    // some setup
    const int numSteps = 10000; 
    //double stepSize = .5 * 1/(double)numSteps;
    double stepSize = 0.000001;

    int opt;
    while ( (opt = getopt( argc, argv, "n:q:" )) != -1 ) {
        switch ( opt ) {
        case 'n':
            //const_cast<int>(numSteps) = optarg;
            cout << "numSteps = " << optarg << endl;
            break;
        case 'q':
            numQubits = atoi(optarg);
            cout << "numQubits = " << optarg << endl;
            break;
        default:
            usage();
        }
    }

    const int numEquations = getNumOfEqns( numQubits );

    // initial conditions
    double x = 0.0;
    valarray<double> y( 0.0, numEquations );
    init( &x, &y );

    for ( int i = 0; i < numSteps; i++ ){

        // take a step
        y += stepRk4( x, y, stepSize );
        x += stepSize;

#ifdef TELL_ME
//        printVals( x, y );
        showProgress(i,numSteps);

//        char line[80];
//        cin.getline(line,80);
#endif //TELL_ME

    }

}

