// Bures.h

#ifndef _BURES_H_
#define _BURES_H_

#include <complex>

#include <tnt/tnt.h>
#include <tnt/tnt_cmat.h>

using namespace TNT;

extern double distBures( const Matrix<std::complex<double> >& mat1, 
                         const Matrix<std::complex<double> >& mat2 );

#endif // _BURES_H_
