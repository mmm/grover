#define _POSIX_SOURCE 1
// init.C
//
#include "myvalarraydouble.h"

#include "derivs.h"


// initialize variables...
void init( double *const x, valarray_double *const y ) {
    *x = 0.0;
    (*y)[0] = 1.0;
    (*y)[1] = 0.0;
}
