#define _POSIX_SOURCE 1
// display.C
//
#include <iostream>

#include <sys/time.h> // all for getrusage and gettimeofday
#include <sys/resource.h>
#include <unistd.h>

#include "myvalarray.h"
#include "init.h"
#include "display.h"


void printVals( const double x, const valarray<double>& y ) {
#ifdef TELL_ME
    //cout << "x= " << x << "\t y= " << y[0] << "\t ";
    //cout << x << " " << y[0] << " " << y[1] << endl;
    cout << x 
        //<< " z= " 
         << " " 
         << y[0] 
         << " " 
        //<< " zbar= " 
         << y[2] 
         << " " 
        // << " w= " 
         << y[1] 
         << " " 
        //<< " wbar= " 
         << y[3] 
         << endl;
    //cout << y[0] << " " << y[1] << endl;
#endif //TELL_ME
}

void showProgress( const int step, const int numSteps ) {

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
