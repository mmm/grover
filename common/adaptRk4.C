#define _POSIX_SOURCE 1
// adaptRk4.C

#ifdef TELL_ME
#include <iostream>
#endif //TELL_ME

#include <stdio.h> // perror
#include <cmath> // abs

#include "adaptRk4.h"


//---- static fns ---------------

// return dy/dx for this particular equation
static double dydx( const double x, const double y ) {

    return 1.0 - x + 4.0 * y;

}


static void stepRKCashKarp( const double *const x, 
                            double *const y, 
                            const double stepSize,
                            double *const yerr ) {


    if ( !x || !y || !yerr ) {
        perror("void ptr in stepRKCashKarp"); // throw stuff
        exit(1);
    }

    const static double a2 = 0.2;
    const static double a3 = 0.3;
    const static double a4 = 0.6;
    const static double a5 = 1.0;
    const static double a6 = 0.875;
    const static double b21 = 0.2;
    const static double b31 = 3.0/40.0;
    const static double b32 = 9.0/40.0;
    const static double b41 = 0.3;
    const static double b42 = -0.9;
    const static double b43 = 1.2;
    const static double b51 = -11.0/54.0;
    const static double b52 = 2.5;
    const static double b53 = -70.0/27.0;
    const static double b54 = 35.0/27.0;
    const static double b61 = 1631.0/55296.0;
    const static double b62 = 175.0/512.0;
    const static double b63 = 575.0/13824.0;
    const static double b64 = 44275.0/110592.0;
    const static double b65 = 253.0/4096.0;
    const static double c1 = 37.0/378.0;
    const static double c3 = 250.0/621.0;
    const static double c4 = 125.0/594.0;
    const static double c6 = 512.0/1771.0;
    const static double dc1 = c1 - 2825.0/27648.0;
    const static double dc3 = c3 - 18575.0/48384.0;
    const static double dc4 = c4 - 13525.0/55296.0;
    const static double dc5 = -277.0/14336.0;
    const static double dc6 = c6 - 0.25;

    const double k1 = stepSize * dydx( *x, *y );
    const double k2 = stepSize * dydx( *x + a2 * stepSize, 
                                 *y + b21 * k1 );
    const double k3 = stepSize * dydx( *x + a3 * stepSize, 
                                 *y + b31 * k1 + b32 * k2 );
    const double k4 = stepSize * dydx( *x + a4 * stepSize, 
                                 *y + b41 * k1 + b42 * k2 + b43 * k3 );
    const double k5 = stepSize * dydx( *x + a5 * stepSize, 
                                 *y + b51 * k1 + b52 * k2 + b53 * k3 + b54 * k4 );
    const double k6 = stepSize * dydx( *x + a6 * stepSize, 
                                 *y + b61 * k1 + b62 * k2 + b63 * k3 + b64 * k4 + b65 * k5 );

    //*y += c1 * k1 + c2 * k2 + c3 * k3 + c4 * k4 + c5 * k5 + c6 * k6;
    *y += c1 * k1 + c3 * k3 + c4 * k4 + c6 * k6;

//No!!!!!!
//    *x += stepSize;

    *yerr = dc1 * k1 + dc3 * k3 + dc4 * k4 + dc5 * k5 + dc6 * k6;

}

inline double max(double a, double b){
    return (a>=b)? a: b;
}
inline double min(double a, double b){
    return (a<=b)? a: b;
}


//---- external fns -------------

extern void stepAdaptRk4( double *const x, double *const y, double *const tryStepSize ) {

    ////////////////////////////////////////////////////////
    //maybe
    //try a step
    //while truncation error > 1.0
    //    shrink step size
    //    step again
    //if truncation error really small
    //    grow stepsize for next time
    ////////////////////////////////////////////////////////
    double stepSize = *tryStepSize;
    double yerr = 0.0; // place to keep the absolute truncation error

    // take a tentative Cash-Karp RK5 step...
    stepRKCashKarp( x, y, stepSize, &yerr );

    // get a handle on truncation error
    const double *const yscal = y;  // fixed scale for now
    //double truncError = abs(yerr/(*yscal)); 
    double truncError = 0.0;
    truncError = max( truncError, abs(yerr/(*yscal)) ); 
    const static double epsilon = 1e-6;
    truncError /= epsilon; // scale to relative tolerance

#ifdef TELL_ME
    cout << "trunc error is " << truncError << endl;
    cout << "x is " << *x << endl;
    cout << "y is " << *y << endl;
//    //cout << "y should be " << *y << endl;
    cout << "yerr is " << yerr << endl;
#endif // TELL_ME



//
//    // we'd like to be able to shrink/grow stepsize at will...
//    const static double SAFETY = 0.9;
//    const static double GROW_POWER = -0.2;
//    const static double SHRINK_POWER = -0.25;
//    const static double ERROR_CONDITION = 1.89e-4; // ??
//
//    // too much error?
//    while ( truncError > 1.0 ) {
//#ifdef TELL_ME
//        cout << "Trunc error too big!" << endl;
//        perror("Trunc error Too Big!");
//        exit(1);
//#endif // TELL_ME
//        
//        //////////////////
//        //reduce step size
//        //////////////////
//        const double tmpStepSize = SAFETY * stepSize * pow( truncError, SHRINK_POWER );
//        //..no more than a power of ten
//        stepSize = ( stepSize >= 0.0 ? max( tmpStepSize, 0.1 * stepSize ): 
//                                       min( tmpStepSize, 0.1 * stepSize ) );
//        // sanity check
//        //const double xtmp = (*x) + stepSize;
//        //if ( xtmp == *x ) perror("stepsize underflow in stepAdaptRk4");
//        if ( (*x + stepSize) == *x ) {
//            perror("stepsize underflow in stepAdaptRk4");
//            exit(1);
//            //throw an underflowStepsize exception
//        }
//
//        /////////////
//        // step again
//        /////////////
//        stepRKCashKarp( x, y, stepSize, &yerr );
//
//        ////////////////
//        // recheck error
//        ////////////////
//        truncError = max( truncError, abs(yerr/(*yscal)) );
//        truncError /= epsilon; // scale to relative tolerance
//        
//    }
//
//        // grow stepsize for next iteration
//        // ERROR_CONDITION = (5/SAFETY)^(1/GROW_POWER) ???
//        if ( truncError > ERROR_CONDITION ) {
//            *tryStepSize = stepSize * SAFETY * pow( truncError, GROW_POWER );
//        }
//        else {
//            // no more than a factor of five increase
//            *tryStepSize = stepSize * 5.0;
//#ifdef TELL_ME
//            cout << "truncerror way small!" 
//                 << "Making step size " << *tryStepSize << endl;
//
//#endif // TELL_ME
//        }
//
    // update the step size actually taken
    *x += stepSize;

}
