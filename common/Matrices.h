// Matrices.h

#ifndef _MATRICES_H_
#define _MATRICES_H_

#include <complex>

#include <tnt/tnt.h>
#include <tnt/cmat.h>
#include <tnt/fmat.h>

using namespace TNT;

extern Fortran_Matrix<complex<double> > dagger( 
    const Fortran_Matrix<complex<double> >& mat );

const Matrix<complex<double> > sqrt( const Matrix<complex<double> >& mat );

extern const double trace( const Matrix<complex<double> >& mat );

#endif // _MATRICES_H_
