// Bures.C
//
#include <tnt/fmat.h>

#include "fwrap.h"

#include "Bures.h"

const double trace( const Matrix<complex<double> >& mat ) {

    if( mat.num_rows() != mat.num_cols() ) throw;

    double sum = 0.0;
    for( int i=0; i<mat.num_rows(); i++ ) {
        sum += abs(mat[i][i]);
    }

    return sum;

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

    if( mat.num_rows() != mat.num_cols() ) throw;

    Fortran_Matrix<complex<double> > tmpMat = toFortranMatrix( mat );

    Vector<double> eigVals( mat.num_rows() );
    Fortran_Matrix<complex<double> > eigVects = tmpMat;
    eigVals = Hermitian_eigenvalue_solve( eigVects );

    Fortran_Matrix<complex<double> > tmpMat2 = dagger(eigVects)*tmpMat*eigVects;
    const complex<double> zero(0.0,0.0);
    Fortran_Matrix<complex<double> > out(mat.num_rows(),mat.num_rows(),zero);
    for (int i=1; i<=mat.num_rows(); i++ ) {
        out(i,i) = sqrt( tmpMat2(i,i) );
    }

    return toCMatrix(eigVects*out*dagger(eigVects));

}


extern double distBures( const Matrix<complex<double> >& mat1, 
                         const Matrix<complex<double> >& mat2 ) {

    Matrix<complex<double> > tmp1 = sqrt( mat1 );
    Matrix<complex<double> > tmp2 = sqrt( tmp1 * mat2 * tmp1 );
    double tmp = 1.0-trace(tmp2);
    tmp = (tmp>0.0)?tmp:-tmp;
    if( tmp < 10e-16 ) 
        return 0.0;
    else return sqrt( 2.0 * ( 1.0 - trace(tmp2) ) );

}
