// Matrices.h

#ifndef _MATRICES_H_
#define _MATRICES_H_

#include <complex>

#include <tnt/tnt.h>
#include <tnt/cmat.h>
#include <tnt/fmat.h>

using namespace TNT;

#include <random/uniform.h>
using namespace ranlib;

extern Fortran_Matrix<complex<double> > dagger( 
    const Fortran_Matrix<complex<double> >& mat );
extern Matrix<complex<double> > dagger( 
    const Matrix<complex<double> >& mat );


extern const double trace( const Matrix<complex<double> >& mat );

extern const bool has_a_nan( const Matrix<complex<double> >& mat );

extern const Matrix<complex<double> > sqrt( const Matrix<complex<double> >& mat );

extern const Vector<double> eigVals( const Matrix<complex<double> >& mat );

extern const Matrix<complex<double> > randomMatrix( Uniform<double>& generator, 
                                                    const int dimension,
                                                    const double upperBound );

const static double ZERO = 1.0e-18;

#endif // _MATRICES_H_
