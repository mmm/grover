#define _POSIX_SOURCE 1
// display.C
//
#include <iostream>
#include <stdexcept>

#include <sys/time.h> // all for getrusage and gettimeofday
#include <sys/resource.h>
#include <unistd.h>

#include "myvalarray.h"
#include "display.h"


void printVals( const double x, const valarray<double>& y ) {
#ifdef TELL_ME
    cout << "x= " << x << endl;
    for ( unsigned int i = 0; i < y.size(); i++ ) {
        cout << "y[" << i << "] = " << y[i] << endl;
    }
#endif //TELL_ME
}

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

void printDensityMatrix( const double x, const valarray<double>& y ) {

    if ( y.size() % 4 ) throw;

    const int n = y.size() / 4;

    try {
        // slices would be easier, but oh well...
//        valarray<double> states(0.0, 2*n);
//        for( int i = 0; i<n; i++ ) {
//            states[i] = y[i];
//            states[i+n] = y[2*n+i];
//        }
//
//#ifdef TELL_ME
//        cout << "x= " << x << endl;
//        for(int i = 0; i< 2*n; i++ ) {
//            cout << "states[" << i << "] = " << states[i] << endl;
//        }
//#endif //TELL_ME
        valarray<double> states(0.0, n+1);
        //states[0] = 1.0/sqrt( pow(2,n) );
        states[0] = 1.0;
        for( int i = 0; i<n; i++ ) {
            states[i+1] = y[i];
        }

        // normalize
        states /= sqrt( 1 + states*states );
#ifdef TELL_ME
        cout << "x= " << x << endl;
        for(int i = 0; i< n+1; i++ ) {
            cout << "states[" << i << "] = " << states[i] << endl;
        }
#endif //TELL_ME

    }
    catch(out_of_range) {
        cerr << "oops" << endl;
        exit(1);
    }

}
