// Bures.h

#ifndef _BURES_H_
#define _BURES_H_

#include <complex>

#include <tnt/tnt.h>
#include <tnt/cmat.h>
#include <tnt/fmat.h>

using namespace TNT;

extern Fortran_Matrix<complex<double> > dagger( 
    const Fortran_Matrix<complex<double> >& mat );
//extern Fortran_Matrix<complex<double> > zero_out( 
//    const Fortran_Matrix<complex<double> >& mat );

const Matrix<complex<double> > sqrt( const Matrix<complex<double> >& mat );

extern double distBures( const Matrix<complex<double> >& mat1, 
                         const Matrix<complex<double> >& mat2 );
extern const double trace( const Matrix<complex<double> >& mat );

#endif // _BURES_H_
