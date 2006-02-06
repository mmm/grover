// display.C
//

#include <sys/time.h> // all for getrusage and gettimeofday
#include <sys/resource.h>
#include <unistd.h>

#include "Bures.h"
#include "Matrices.h"
#include "fwrap.h"

#include "display.h"

using namespace std;

void showProgress( ostream& out, const int step, const int numSteps, const int numQubits ) {

    static timeval startTime;
    if ( 0 == step ) {
        //first time through
        gettimeofday( &startTime, NULL );
        out << "Stepper was started at timeofday: " 
             << startTime.tv_sec << " seconds, "
             << startTime.tv_usec << " microseconds."
             << endl;
        out << "Running " 
             << numQubits
             << " qubits... |";
        out.flush();
    }

    int aTenth = numSteps/10;
    if ( 0 == step%aTenth ) {
        out << "=";
        out.flush();
    }

    if ( step && 0 == step%(numSteps-1) ) {
        // end of the run.
        rusage usageStuff;
        if ( getrusage(RUSAGE_SELF,&usageStuff) ) {
            cerr << "stepper: can't get rusage" << endl;
        }
        timeval endTime;
        gettimeofday( &endTime, NULL );
        out << "> Done!" << endl;
        out << "Stepper finished at timeofday: " 
             << endTime.tv_sec << " seconds, "
             << endTime.tv_usec << " microseconds."
             << endl;
        out << " CPU time used: " << usageStuff.ru_utime.tv_sec
             << " seconds, " << usageStuff.ru_utime.tv_usec
             << " microseconds."
             << endl;
        timeval realTime = { 0 };
        timersub( &endTime, &startTime, &realTime );
        out << " Real time used: " 
             << realTime.tv_sec << " seconds, "
             << realTime.tv_usec << " microseconds."
             << endl;
    }

}

extern void writeDiffs( ofstream& outFile,
                        const double time,
                        const State *const rho1, 
                        const State *const rho2 ) {

    const Matrix<complex<double> >& mat2 = rho2->matrix();
    // errbnds on Bures?
    outFile << time * 100.0
            << ' '
            << distBures(*rho1,*rho2) 
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

extern void writeLeadingEVals( ofstream& outFile, 
                               const double time,
                               const State *const rho1, 
                               const State *const rho2 ) {

    const Matrix<complex<double> >& mat1 = rho1->matrix();
    const Matrix<complex<double> >& mat2 = rho2->matrix();
    outFile << time * 100.0
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
