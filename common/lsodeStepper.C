#define _POSIX_SOURCE 1
// lsodeStepper.C

#include "lsodeStepper.h"
#include "lsode.h"



// static stuff

int neq = 1;
int itol = 1;
double rtol = 0.05;
double atol = 0.05;
int itask = 1;
int istate = 1;    
int iopt = 0;
const int lrw = 36;
double rwork[lrw] = { 0 };
const int liw = 20;
int iwork[liw] = { 0 };
int mf = 10;
double xtemp;


static double dydx( const double x, const double y ) {

    return 1.0 - x + 4.0 * y;

}



// external fns

extern void stepLsode( double *const x, double *const y, double *const stepSize ) {
    
    xtemp = *x + *stepSize;
    lsode_(dydx, &neq, y, x, &xtemp, &itol, &rtol, &atol,
           &itask, &istate, &iopt, rwork, const_cast<int *>(&lrw), 
           iwork, const_cast<int *>(&liw), 0, &mf );

}
