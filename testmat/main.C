//

#include <iostream>
#include <unistd.h> // getopt
#include <cmath>
#include <complex>

#include <tnt/tnt.h>
#include <tnt/cmat.h>
#include <tnt/fmat.h>
#include <tnt/vec.h>
using namespace TNT;

#include "fwrap.h"
#include "Matrices.h"
#include "Bures.h"

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

    get_eps();

    const int dimension = int( pow( 2, numQubits ) );
    const complex<double> zero(0.0,0.0);
    Matrix<complex<double> > A(dimension,dimension,zero);

    A(1,1) = 5;
    A(1,2) = complex<double>(2,-2);
    A(2,1) = complex<double>(2,2);
    A(2,2) = 4;

    cout << "A = " << A << endl;

    Fortran_Matrix<complex<double> > B(dimension,dimension,zero);
//    for ( int i = 1; i <= dimension; i++ ) {
//        B(i,i) = i;
//    }

    B(1,1) = 5;
    B(1,2) = complex<double>(2,-2);
    B(2,1) = complex<double>(2,2);
    B(2,2) = 4;

//    B(1,1) = 3;
//    B(1,2) = complex<double>(1,-2);
//    B(2,1) = complex<double>(1,2);
//    B(2,2) = 5;

//    B(1,1) = 15;
//    B(1,2) = complex<double>(5,-10);
//    B(1,3) = complex<double>(6,-6);
//    B(1,4) = complex<double>(-2,-6);
//    B(2,1) = complex<double>(5,10);
//    B(2,2) = 25;
//    B(2,3) = complex<double>(6,2);
//    B(2,4) = complex<double>(10,-10);
//    B(3,1) = complex<double>(6,6);
//    B(3,2) = complex<double>(6,-2);
//    B(3,3) = 12;
//    B(3,4) = complex<double>(4,-8);
//    B(4,1) = complex<double>(-2,6);
//    B(4,2) = complex<double>(10,10);
//    B(4,3) = complex<double>(4,8);
//    B(4,4) = 20;


    cout << "B = " << B << endl;


//    Fortran_Matrix<complex<double> > eigVects = B;
//    Vector<double> eigVals( dimension );
//    eigVals = Hermitian_eigenvalue_solve( eigVects );
//
//    cout << "eigVals = " << eigVals << endl;
//    cout << "B = " << B << endl;
//    cout << "eigVects = " << eigVects << endl;
//
//    cout << "diag = " << dagger(eigVects)*B*eigVects << endl;

    Matrix<complex<double> > C  = sqrt(A);
    cout << "sqrt(A) = " << C << endl;
    cout << "sqrt(A)*sqrt(A) = " << C*C << endl;
    cout << "diffs = " << C*C - A << endl;

    for ( int i = 0; i < numSteps; i++ ){

//        char line[80];
//        cin.getline(line,80);

    }

}

