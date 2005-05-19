// gslMatrixUtils.C
//
#include <iostream>

#include "exceptions.h"

#include "Matrices.h"
#include "gslMatrixUtils.h"


Matrix<complex<double> > 
nan_to_zero( const Matrix<complex<double> >& mat ) {

    Matrix<complex<double> > tmp = mat;
    for(int i=1; i<=mat.num_rows(); i++) {
        for(int j=1; j<=mat.num_rows(); j++) {
            tmp(i,j) = complex<double>(
                ( isnan( mat(i,j).real() ) )? 0.0 : mat(i,j).real(),
                ( isnan( mat(i,j).imag() ) )? 0.0 : mat(i,j).imag()
                );
        }
    }

    return tmp;

}

const Matrix<complex<double> > 
gslMatrixSqrt( const Matrix<complex<double> >& mat ) {

    if( mat.num_rows() != mat.num_cols() ) throw("Matrices not square");



    

    Vector<double> eigVals( mat.num_rows() );
    Matrix<complex<double> > eigVects = nan_to_zero(mat);
//    eigVals = Hermitian_eigenvalue_solve( eigVects );

    Matrix<complex<double> > tmpMat2 = 
        dagger(eigVects)*mat*eigVects;
    const complex<double> zero(0.0,0.0);
    Matrix<complex<double> > out(mat.num_rows(),
                                         mat.num_rows(),
                                         zero);
    for (int i=1; i<=mat.num_rows(); i++ ) {
        out(i,i) = sqrt( tmpMat2(i,i) );
    }

    return nan_to_zero(eigVects*out*dagger(eigVects));

}

const Vector<double> gslMatrixEigVals( const Matrix<complex<double> >& mat ) {

    if( mat.num_rows() != mat.num_cols() ) throw("Matrices not square");

    Vector<double> eigVals( mat.num_rows() );
    Matrix<complex<double> > eigVects = nan_to_zero(mat);
//    eigVals = Hermitian_eigenvalue_solve( eigVects );

    return eigVals;

}


