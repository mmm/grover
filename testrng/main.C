//

#include <iostream>
#include <unistd.h> // getopt
#include <cmath>
//#include <complex>

//#include <tnt/tnt.h>
//#include <tnt/cmat.h>
//#include <tnt/fmat.h>
//#include <tnt/vec.h>
//using namespace TNT;

#include <time.h>
#include <random/uniform.h>

using namespace ranlib;

void usage( void ) {
    cout << "Usage: stepper [-q num-qubits] [-n num-steps]" 
         << endl;
    exit(1);
}

int main( int argc, char* argv[] ) {

    // some setup
    const int numSteps = 10000; 

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

    //const int dimension = int( pow( 2, numQubits ) );

    Uniform<double> uniformGen;

    // maybe try seeding by time?
    uniformGen.seed( static_cast<unsigned int>( time(0) ) );

    double x = uniformGen.random();
    cout << "x = " << x << endl;

    for ( int i = 0; i < numSteps; i++ ){

        x = uniformGen.random();
        cout << "x = " << x << endl;

        char line[80];
        cin.getline(line,80);

    }

}

