// gslMatrixUtils.h

#ifndef _GSL_MATRIX_UTILS_H_
#define _GSL_MATRIX_UTILS_H_

#include <complex>
using std::complex;

#include <tnt/tnt.h>
#include <tnt/tnt_cmat.h>
#include <tnt/tnt_fortran_array2d.h>

using namespace TNT;

extern const Matrix<complex<double> > gslMatrixSqrt( const Matrix<complex<double> >& mat ); 

extern const Vector<double> gslMatrixEigVals( const Matrix<complex<double> >& mat );

#endif // _GSL_MATRIX_UTILS_H_
