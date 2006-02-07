// Matrices.C
//
#include <iostream>
#include <tnt/tnt_fortran_array2d.h>

//#include "fwrap.h"
#include "gslMatrixUtils.h"
#include "exceptions.h"

#include "Matrices.h"

using namespace SimTools;

const double trace( const Matrix<complex<double> >& mat ) {

    if( mat.num_rows() != mat.num_cols() ) throw("Matrices not square");

    double sum = 0.0;
    for( int i=0; i<mat.num_rows(); i++ ) {
        sum += abs(mat[i][i]);
    }

    return sum;

}

Fortran_Array2D<complex<double> > 
nan_to_zero( const Fortran_Array2D<complex<double> >& mat ) {

    Fortran_Array2D<complex<double> > tmp = mat;
    for(int i=1; i<=mat.dim1(); i++) {
        for(int j=1; j<=mat.dim1(); j++) {
            tmp(i,j) = complex<double>(
                ( isnan( mat(i,j).real() ) )? 0.0 : mat(i,j).real(),
                ( isnan( mat(i,j).imag() ) )? 0.0 : mat(i,j).imag()
                );
        }
    }

    return tmp;

}

Fortran_Array2D<complex<double> > 
dagger( const Fortran_Array2D<complex<double> >& mat ) {

    Fortran_Array2D<complex<double> > tmp = mat;
    for(int i=1; i<=mat.dim1(); i++) {
        for(int j=1; j<=mat.dim1(); j++) {
            tmp(j,i) = conj( mat(i,j) );
        }
    }

    return tmp;

}

Matrix<complex<double> > 
dagger( const Matrix<complex<double> >& mat ) {

    Matrix<complex<double> > tmp = mat;
    for(int i=0; i<mat.num_rows(); i++) {
        for(int j=0; j<mat.num_rows(); j++) {
            tmp[j][i] = conj( mat[i][j] );
        }
    }

    return tmp;

}

Fortran_Array2D<complex<double> > 
toFortranMatrix( const Matrix<complex<double> >& mat ) {

    Fortran_Array2D<complex<double> > tmpMat( mat.num_rows(), 
                                             mat.num_rows(), 
                                             0.0 );
    for( int i=1; i<=mat.num_rows(); i++ ) {
        for( int j=1; j<=mat.num_rows(); j++ ) {
            tmpMat(i,j) = mat(i,j);
        }
    }
    return tmpMat;

}

Matrix<complex<double> > 
toCMatrix( const Fortran_Array2D<complex<double> >& mat ) {

    Matrix<complex<double> > tmpMat( mat.dim1(), mat.dim1(), 0.0 );
    for( int i=1; i<=mat.dim1(); i++ ) {
        for( int j=1; j<=mat.dim1(); j++ ) {
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

const Matrix<complex<double> > 
sqrt( const Matrix<complex<double> >& mat ) {

    return gslMatrixSqrt( mat );

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

const Vector<double> eigVals( const Matrix<complex<double> >& mat ) {

    return gslMatrixEigVals( mat );

}

const Matrix<complex<double> > randomMatrix( Uniform<double>& generator, 
                                             const int dimension,
                                             const double upperBound ) {

    Matrix<complex<double> > tmp( dimension, dimension,
                                  complex<double>(0.0,0.0) );
    for ( int i=0; i<dimension; i++ ) {
        tmp[i][i] = generator.random();
        for ( int j=0; j<i; j++ ) {
            tmp[j][i] = complex<double>( generator.random() - 0.5,
                                         generator.random() - 0.5 );
            tmp[i][j] = conj( tmp[j][i] );
        }
    }

    double trace = 0.0;
    for ( int i=0; i<dimension; i++ ) {
        trace += tmp[i][i].real();
    }

    if ( trace < ZERO ) throw Fpe("trace too small");

    for ( int i=0; i<dimension; i++ ) {
        for ( int j=0; j<dimension; j++ ) {
            tmp[i][j] /= trace;
            tmp[i][j] *= upperBound;
        }
    }

    return tmp;

}
