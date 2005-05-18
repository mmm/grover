// Matrices.h

#ifndef _MATRICES_H_
#define _MATRICES_H_

#include <complex>
using std::complex;

#include <tnt/tnt.h>
#include <tnt/tnt_cmat.h>
#include <tnt/tnt_fortran_array2d.h>

using namespace TNT;

#include <random/uniform.h>
using namespace ranlib;

extern Fortran_Array2D<complex<double> > 
           dagger( const Fortran_Array2D<complex<double> >& mat );

extern Matrix<complex<double> > 
           dagger( const Matrix<complex<double> >& mat );

extern const double trace( const Matrix<complex<double> >& mat );

extern const bool has_a_nan( const Matrix<complex<double> >& mat );

extern const Matrix<complex<double> > 
                 sqrt( const Matrix<complex<double> >& mat ); 

extern const Vector<double> 
                 eigVals( const Matrix<complex<double> >& mat );

extern const Matrix<complex<double> > 
                 randomMatrix( Uniform<double>& generator, 
                               const int dimension,
                               const double upperBound );

const static double ZERO = 1.0e-18;

#endif // _MATRICES_H_
