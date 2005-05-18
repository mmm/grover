// Bures.C
//

#include <iostream>

#include "Matrices.h"

#include "exceptions.h"

#include "Bures.h"

extern double distBures( const Matrix<complex<double> >& mat1, 
                         const Matrix<complex<double> >& mat2 ) {

    //cout << "Bures distance called.. between " << mat1 << endl;
    //cout << "and " << mat2 << endl;

    double ret(0.0);
    try {

        Matrix<complex<double> > tmp1 = sqrt( mat1 );
        Matrix<complex<double> > tmp2 = sqrt( tmp1 * mat2 * tmp1 );
        double tmp = 1.0-trace(tmp2);
        ret = sqrt( 2.0 * std::abs(tmp) );
        if ( isnan( ret ) ) throw Fpe("From distBures");
    }
    catch ( const std::exception& ex ) {
        std::cerr << "Oops in distBures" << std::endl;
    }

    return ret;
}
