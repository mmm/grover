// Bures.C
//
#include <iostream>
#include <tnt/fmat.h>

//#include <tnt/lapack.h>
//#include "mylapack.h"
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


Fortran_Matrix<complex<double> > toFortranMatrix( const Matrix<complex<double> >& mat ) {

    Fortran_Matrix<complex<double> > tmpMat( mat.num_rows(), mat.num_rows(), 0.0 );
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
    cout << "FortMat = " << tmpMat << endl;

    Vector<double> eigVals( mat.num_rows() );
    Matrix<double> eigVects( mat.num_rows(), mat.num_rows(), 0.0 );
    //eigVals = Upper_symmetric_eigenvalue_solve( tmpMat );
    eigVals = Hermitian_eigenvalue_solve( tmpMat );

//    Matrix<complex<double> > U = makematrix( eigVects );

    cout << "eigVals = " << eigVals << endl;

    return mat;

}


extern double distBures( const Matrix<complex<double> >& mat1, 
                         const Matrix<complex<double> >& mat2 ) {

    //Matrix<complex<double> > tmp1 = sqrt( mat1 );
    //Matrix<complex<double> > tmp2 = sqrt( tmp1 * mat2 * tmp1 );
    //return sqrt( 2 * ( 1 - trace(tmp2) ) );
    return trace(sqrt(mat2));

}
