// Bures.h

#ifndef _BURES_H_
#define _BURES_H_

#include <complex>

#include <tnt/tnt.h>
#include <tnt/cmat.h>

using namespace TNT;

extern double distBures( const Matrix<complex<double> >& mat1, 
                         const Matrix<complex<double> >& mat2 );

#endif // _BURES_H_
