//
#include <unistd.h> // getopt
#include <cmath> // pow

#include "PureState.h"
#include "MixedState.h"
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

    int opt,
        numQubits = 4;
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

    const int dimension = int( pow( 2, numQubits ) );

    // initial conditions
    double t = 0.0;
    State* rho1 = new PureState(dimension);
    rho1->init();
    State* rho2 = new MixedState(dimension);
    rho2->init();

    for ( int i = 0; i < numSteps; i++ ){

        // take a step
        rho1->step( t, stepSize );
        rho2->step( t, stepSize );
        t += stepSize;

#ifdef TELL_ME
        showProgress(i,numSteps,numQubits);
        if ( i == 0 || i == numSteps - 1 ) {
            rho1->print(t);
            rho2->print(t);
        }

//        char line[80];
//        cin.getline(line,80);
#endif //TELL_ME

    }

    delete rho1;
    delete rho2;

}

