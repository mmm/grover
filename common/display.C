#define _POSIX_SOURCE 1
// display.C
//
#include <iostream>

#include <sys/time.h> // all for getrusage and gettimeofday
#include <sys/resource.h>
#include <unistd.h>

#include "Bures.h"
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

    int aTenth = numSteps/10;
    if ( 0 == step%aTenth ) {
        cout << "=";
        cout.flush();
    }

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
                        const double time,
                        const State *const rho1, 
                        const State *const rho2 ) {

    const Matrix<complex<double> >& mat1 = rho1->matrix();
    const Matrix<complex<double> >& mat2 = rho2->matrix();

    //cout << "Bures distance between rho1 and rho2 = " 
    //     << distBures(mat1,mat2) << endl;

    //outFile << "At time " << time 
    //        << ", the Bures distance between rho1 and rho2 is: " 
    //        << distBures(mat1,mat2) << endl;
    outFile << time * 100.0
            << ' '
            << distBures(mat1,mat2) 
//            << ' '
//            << log( distBures(mat1,mat2) )
            << endl;
}
