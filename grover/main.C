//
#include <string>
#include <fstream> 
#include <unistd.h> // getopt
#include <cmath> // pow
#include <time.h> // time

#include "display.h"

#include <random/uniform.h>
using namespace ranlib;

#include "Matrices.h"


void usage( void ) {
    cout << "Usage: stepper [-q num-qubits] [-n num-steps]" 
         << endl;
    exit(1);
}

int main( int argc, char* argv[] ) {

    // some setup

    const int numSteps = 10; 


    Uniform<double> uniformGenerator;
    //uniformGenerator.seed( static_cast<unsigned int>( time(0) ) );

    //const double upperBound = 0.0001; // biggest noise can get(???)
    //const double upperBound = 0.001; // biggest noise can get(???)
    //const double upperBound = 0.01; // biggest noise can get(???)
    const double upperBound = 0.0; // biggest noise can get(???)

    int opt,
        numQubits = 4;
    string outFile = "output/stepper.out";
    while ( (opt = getopt( argc, argv, "n:o:q:" )) != -1 ) {
        switch ( opt ) {
        case 'n':
            //const_cast<int>(numSteps) = optarg;
            cout << "numSteps = " << optarg << endl;
            break;
        case 'o':
            outFile = optarg;
            cout << "outFile = " << optarg << endl;
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

    // outputfile stuff
    char fileBase[2 + sizeof(int) + sizeof(double)] = "";
    sprintf( fileBase, "-%d-n%f", numQubits, upperBound );
    outFile += fileBase;
    cout << "outFile = " << outFile << endl;
    ofstream outFileStream( outFile.c_str() );
    if ( !outFileStream ) {
        cerr << "Oops!" << endl;
        exit(1);
    }


    // initial conditions
    Matrix<complex<double> > rho1( dimension, dimension, 
                                  complex<double>(1.0/dimension,0.0));
    Matrix<complex<double> > rho2( dimension, dimension, 
                                  complex<double>(1.0/dimension,0.0));
    Matrix<complex<double> > U_grover( dimension, dimension, complex<double>(0.0,0.0));
    Matrix<complex<double> > U_phase( dimension, dimension, complex<double>(0.0,0.0));
    for ( int i = 0; i< dimension; i++ ) {
        U_phase[i][i] = 1.0;
    }
    U_phase[0][0] = - U_phase[0][0];
    for ( int i = 0; i< dimension; i++ ) {
        for ( int j = 0; j< dimension; j++ ) {
            U_grover[i][j] = 2.0/dimension;
        }
    }
    for ( int i = 0; i< dimension; i++ ) {
        U_grover[i][i] = ( 2.0 - dimension )/dimension;
    }

    U_grover = U_grover * U_phase;


    try{
        for ( int i = 0; i < numSteps; i++ ){

            rho1 = U_grover * rho1 * dagger( U_grover );
            rho2 = U_grover * rho2 * dagger( U_grover ) 
                + randomMatrix(uniformGenerator, dimension, upperBound);

            //rho /= trace(rho);
            double tr = trace(rho2);
            for ( int i = 0; i<dimension; i++ ) {
                for ( int j = 0; j<dimension; j++ ) {
                    rho2[i][j] /= tr;
                }
            }

            cout << rho1[0][0] << endl;

//            char line[80];
//            cin.getline(line,80);
        }

    }
    catch( const exception& ex ) {
        cerr << "exception " << ex.what() << endl;
    }

    outFileStream.close();

}

