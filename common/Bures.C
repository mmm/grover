// Bures.C
//
#include "Matrices.h"

#include "Bures.h"

extern double distBures( const Matrix<complex<double> >& mat1, 
                         const Matrix<complex<double> >& mat2 ) {

    //cout << "Bures distance called.. between " << mat1 << endl;
    //cout << "and " << mat2 << endl;


    Matrix<complex<double> > tmp1 = sqrt( mat1 );
    Matrix<complex<double> > tmp2 = sqrt( tmp1 * mat2 * tmp1 );
    double tmp = 1.0-trace(tmp2);
    tmp = (tmp>0.0)?tmp:-tmp;
    if( tmp < 10e-16 ) 
        return 0.0;
//    else return sqrt( 2.0 * ( 1.0 - trace(tmp2) ) );
    else {
        double junk1 = trace(tmp2);
        double junk2 = sqrt( 2.0 * ( 1.0 - junk1 ) );
        if ( isnan( junk2 ) ) throw;
        return junk2;
    }

}
