#define _POSIX_SOURCE 1
// display.C
//
#include <iostream>

#include <sys/time.h> // all for getrusage and gettimeofday
#include <sys/resource.h>
#include <unistd.h>

#include "Bures.h"
#include "Matrices.h"
#include "fwrap.h"

#include "display.h"

void showProgress( const int step, const int numSteps, const int numQubits ) {

    static timeval startTime;
    if ( 0 == step ) {
        //first time through
        gettimeofday( &startTime, NULL );
        cout << "Stepper was started at timeofday: " 
             << startTime.tv_sec << " seconds, "
             << startTime.tv_usec << " microseconds."
             << endl;
        cout << "Running " 
             << numQubits
             << " qubits... |";
        cout.flush();
    }

//    int aTenth = numSteps/10;
//    if ( 0 == step%aTenth ) {
//        cout << "=";
//        cout.flush();
//    }
    cout << "=";
    cout.flush();

    if ( step && 0 == step%(numSteps-1) ) {
        // end of the run.
        rusage usageStuff;
        if ( getrusage(RUSAGE_SELF,&usageStuff) ) {
            cerr << "stepper: can't get rusage" << endl;
        }
        timeval endTime;
        gettimeofday( &endTime, NULL );
        cout << "> Done!" << endl;
        cout << "Stepper finished at timeofday: " 
             << endTime.tv_sec << " seconds, "
             << endTime.tv_usec << " microseconds."
             << endl;
        cout << " CPU time used: " << usageStuff.ru_utime.tv_sec
             << " seconds, " << usageStuff.ru_utime.tv_usec
             << " microseconds."
             << endl;
        timeval realTime = { 0 };
        timersub( &endTime, &startTime, &realTime );
        cout << " Real time used: " 
             << realTime.tv_sec << " seconds, "
             << realTime.tv_usec << " microseconds."
             << endl;
    }

}

extern void printDiffs( ofstream& outFile,
                        const int iteration,
                        const Matrix<complex<double> >& mat1,
                        const Matrix<complex<double> >& mat2 ) {

    // errbnds on Bures?
    outFile << iteration
            << ' '
            << distBures(mat1,mat2) 
            << ' ';
    
    const Vector<double> eVals = eigVals(mat2);
//    const double eValErrBnd = get_eps() * 
//        max( eVals[0], eVals[ eVals.size() - 1 ] ); 
// too small for now
    for ( int i=eVals.size() -1; i>=0; i-- ) {
        outFile << eVals[i]
                << ' ';
    }
    outFile << endl;

}

extern void printLeadingEVals( ofstream& outFile, 
                               const int iteration,
                               const Matrix<complex<double> >& mat1, 
                               const Matrix<complex<double> >& mat2 ) {

    outFile << iteration
            << ' '
            << mat1(1,1).real()
            << ' '
            << mat2(1,1).real();

    
//    const Vector<double> eVals1 = eigVals(mat1);
//    outFile << max( eVals1[0], eVals1[ eVals1.size() - 1 ] ) 
//            << ' ';
//    const Vector<double> eVals2 = eigVals(mat2);
//    outFile << max( eVals2[0], eVals2[ eVals2.size() - 1 ] ) 
//            << ' ';
    outFile << endl;

}
