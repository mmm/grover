// Matrices.C
//
#include <iostream>
#include <tnt/fmat.h>

#include "fwrap.h"

#include "Matrices.h"

const double trace( const Matrix<complex<double> >& mat ) {

    if( mat.num_rows() != mat.num_cols() ) throw("Matrices not square");

    double sum = 0.0;
    for( int i=0; i<mat.num_rows(); i++ ) {
        sum += abs(mat[i][i]);
    }

    return sum;

}

Fortran_Matrix<complex<double> > nan_to_zero( const Fortran_Matrix<complex<double> >& mat ) {

    Fortran_Matrix<complex<double> > tmp = mat;
    for(int i=1; i<=mat.num_rows(); i++) {
        for(int j=1; j<=mat.num_rows(); j++) {
            tmp(i,j) = complex<double>(
                //( mat(i,j).real() < 1e-20 )? 0.0 : mat(i,j).real(),
                //( mat(i,j).imag() < 1e-20 )? 0.0 : mat(i,j).imag()
                ( isnan( mat(i,j).real() ) )? 0.0 : mat(i,j).real(),
                ( isnan( mat(i,j).imag() ) )? 0.0 : mat(i,j).imag()
                );
        }
    }

    return tmp;

}

Fortran_Matrix<complex<double> > dagger( const Fortran_Matrix<complex<double> >& mat ) {

    Fortran_Matrix<complex<double> > tmp = mat;
    for(int i=1; i<=mat.num_rows(); i++) {
        for(int j=1; j<=mat.num_rows(); j++) {
            tmp(j,i) = conj( mat(i,j) );
        }
    }

    return tmp;

}


Fortran_Matrix<complex<double> > toFortranMatrix( const Matrix<complex<double> >& mat ) {

    Fortran_Matrix<complex<double> > tmpMat( mat.num_rows(), mat.num_rows(), 0.0 );
    for( int i=1; i<=mat.num_rows(); i++ ) {
        for( int j=1; j<=mat.num_rows(); j++ ) {
            tmpMat(i,j) = mat(i,j);
        }
    }
    return tmpMat;

}

Matrix<complex<double> > toCMatrix( const Fortran_Matrix<complex<double> >& mat ) {

    Matrix<complex<double> > tmpMat( mat.num_rows(), mat.num_rows(), 0.0 );
    for( int i=1; i<=mat.num_rows(); i++ ) {
        for( int j=1; j<=mat.num_rows(); j++ ) {
            tmpMat(i,j) = mat(i,j);
        }
    }
    return tmpMat;

}

// Make a diagonal matrix out of a vector of eigenvalues
const Matrix<complex<double> > makeMatrix( const Vector<double>& eigVals ) {

    Matrix<complex<double> > tmp( eigVals.size(), eigVals.size(), 0.0 );
    for( int i=0; i < eigVals.size(); i++ ) {
        tmp[i][i] = eigVals[i];
    }
    return tmp;
}

const Matrix<complex<double> > sqrt( const Matrix<complex<double> >& mat ) {

    if( mat.num_rows() != mat.num_cols() ) throw("Matrices not square");

    Fortran_Matrix<complex<double> > tmpMat = toFortranMatrix( mat );

    Vector<double> eigVals( mat.num_rows() );
    Fortran_Matrix<complex<double> > eigVects = nan_to_zero(tmpMat);
    eigVals = Hermitian_eigenvalue_solve( eigVects );

    Fortran_Matrix<complex<double> > tmpMat2 = dagger(eigVects)*tmpMat*eigVects;
    const complex<double> zero(0.0,0.0);
    Fortran_Matrix<complex<double> > out(mat.num_rows(),mat.num_rows(),zero);
    for (int i=1; i<=mat.num_rows(); i++ ) {
        out(i,i) = sqrt( tmpMat2(i,i) );
    }

    //return toCMatrix(eigVects*out*dagger(eigVects));
    return toCMatrix( nan_to_zero(eigVects*out*dagger(eigVects)) );

}

const bool has_a_nan( const Matrix<complex<double> >& mat ) {

    for( int i=0; i<mat.num_rows(); i++ ) {
        for( int j=0; j<mat.num_cols(); j++ ) {
            if ( isnan(mat[i][j].real()) || isnan(mat[i][j].imag()) ) 
                return true;
        }
    }
    return false;

}
