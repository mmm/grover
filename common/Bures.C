// Bures.C
//
#include <iostream>
#include <tnt/fmat.h>
#include <tnt/lapack.h>

#include "Bures.h"

const double trace( const Matrix<complex<double> >& mat ) {

    if( mat.num_rows() != mat.num_cols() ) throw;

    double sum = 0.0;
    for( int i=0; i<mat.num_rows(); i++ ) {
        sum += abs(mat[i][i]);
    }

    return sum;

}

const Matrix<complex<double> >& sqrt( const Matrix<complex<double> >& mat ) {

    if( mat.num_rows() != mat.num_cols() ) throw;

    Fortran_Matrix<double> tmpMat( mat.num_rows(), mat.num_rows(), 0.0 );
    for( int i=1; i<=mat.num_rows(); i++ ) {
        for( int j=1; j<=mat.num_rows(); j++ ) {
            tmpMat(i,j) = abs( mat(i,j) );
        }
    }

    cout << "FortMat = " << tmpMat << endl;

    //valarray<complex<double> > eigVals( 0.0, mat.num_rows() );
    Vector<double> eigVals( mat.num_rows() );
    eigVals = Upper_symmetric_eigenvalue_solve( tmpMat );

    cout << "eigVals = " << eigVals << endl;

    return mat;

}


extern double distBures( const Matrix<complex<double> >& mat1, 
                         const Matrix<complex<double> >& mat2 ) {

    Matrix<complex<double> >& tmp = sqrt(mat2);

    return trace(tmp);

}
