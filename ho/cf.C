#define _POSIX_SOURCE 1
// cf.C
//
#include <iostream>

#include <math.h> // cos

#include <sys/time.h> // all for getrusage and gettimeofday
#include <sys/resource.h>
#include <unistd.h>

#include "myvalarray.h"


#include "cf.h"

void compareWithSoln( const double x, const valarray<double>& y ) {

    // set precision...
    //cout.

    double y_soln = cos( x );

#ifdef TELL_ME
        cout << "x= " << x << "\t y= " << y[0] << "\t ";

        cout << "Soln differs by " 
             << y[0] - y_soln << endl;
//        cout << "exact y= " << y_soln << endl;
#endif //TELL_ME

}

void printVals( const double x, const valarray<double>& y ) {
#ifdef TELL_ME
    //cout << "x= " << x << "\t y= " << y[0] << "\t ";
    //cout << x << " " << y[0] << " " << y[1] << endl;
    cout << x << " " << y[0] << " " << y[1] << " " 
         //<< y*y 
         << y[0] * y[0] + y[1] * y[1]
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
        cout << "Running... |";
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
