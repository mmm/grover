//
#include <string>
#include <fstream> 
#include <unistd.h> // getopt
#include <cmath> // pow
#include <time.h> // time


#include <random/uniform.h>
using namespace ranlib;

#include "Matrices.h"
#include "display.h"

void usage( void ) {
    cout << "Usage: stepper [options]" << endl
         << "Where options are:" << endl
         << "-d prob-datafile " << endl
         << "-n num-steps"  << endl
         << "-o bures-datafile" << endl
         << "-q num-qubits"  << endl
         << "-u noise-threshold" << endl;
    exit(1);
}

int main( int argc, char* argv[] ) {

    int numQubits = 4;
    int numSteps = 10; 
    string outFileA = "output/Bures.out";
    string outFileB = "output/targetCoeff.out";
    double upperBound = 0.005; // biggest noise can get... kinda
                               // works between 0.001 and 0.01
    int opt = 0;
    while ( (opt = getopt( argc, argv, "d:n:o:q:u:" )) != -1 ) {
        switch ( opt ) {
        case 'd':
            outFileB = optarg;
            break;
        case 'n':
            numSteps = atoi(optarg);
            break;
        case 'o':
            outFileA = optarg;
            break;
        case 'q':
            numQubits = atoi(optarg);
            break;
        case 'u':
            upperBound = atof(optarg);
            break;
        default:
            usage();
        }
    }

    Uniform<double> uniformGenerator;
    //uniformGenerator.seed( static_cast<unsigned int>( time(0) ) );

    const int dimension = int( pow( 2, numQubits ) );

    // outputfile stuff
    char fileAppend[2 + sizeof(int) + sizeof(double)] = "";
    sprintf( fileAppend, "-%d-n%f", numQubits, upperBound );
    outFileA += fileAppend;
    outFileB += fileAppend;
    ofstream outFileStreamA( outFileA.c_str() );
    ofstream outFileStreamB( outFileB.c_str() );
    if ( !outFileStreamA || !outFileStreamB ) {
        cerr << "Oops!" << endl;
        exit(1);
    }

    cout << "Bures distance -v- time to " 
         <<  outFileA << endl;
    cout << "target state prob -v- time to " 
         <<  outFileB << endl;
    cout << "numQubits = " << numQubits << endl;
    cout << "numSteps = " << numSteps << endl;
    cout << "upper bound = " << upperBound << endl;


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

    printDiffs(outFileStreamA,0,rho1,rho2);
    printLeadingEVals(outFileStreamB,0,rho1,rho2);

    try{
        for ( int i = 0; i < numSteps; i++ ){

            rho1 = U_grover * rho1 * dagger( U_grover );
            rho2 = U_grover * rho2 * dagger( U_grover ) 
                + randomMatrix(uniformGenerator, dimension, upperBound);

            double tr = trace(rho2);
            for ( int k = 0; i<dimension; i++ ) {
                for ( int j = 0; j<dimension; j++ ) {
                    rho2[k][j] /= tr;
                }
            }

            printDiffs(outFileStreamA,i+1,rho1,rho2);
            printLeadingEVals(outFileStreamB,i+1,rho1,rho2);
            showProgress(i,numSteps,numQubits);

            //char line[80];
            //cin.getline(line,80);

        }

    }
    catch( const exception& ex ) {
        cerr << "exception " << ex.what() << endl;
    }

    outFileStreamA.close();
    outFileStreamB.close();

}

