// State.C
#include <stdexcept>
#include <complex>
#include "rk4.h"

#include <tnt/tnt.h>
#include <tnt/cmat.h>
#include <tnt/fmat.h>

//#include <tnt/fortran.h>
//#include <tnt/lapack.h>
//#include <tnt/lu.h>

#include "MixedState.h"
   
using namespace TNT;

MixedState::~MixedState() {
    for ( int i = 0; i< _dimension; i++ ) {
        delete _pureStates[i];
    }
}

void MixedState::init( void ) {

    _lambda[0] = 1.0;

    try{
        valarray<double> z(0.0, _dimension - 1);
        valarray<double> w(0.0, _dimension - 1);
        valarray<double> zbar(0.0, _dimension - 1);
        valarray<double> wbar(0.0, _dimension - 1);

        for ( int i = 0; i< _dimension; i++ ) {
            _pureStates.push_back( new PureState(_dimension) );
            _pureStates[i]->init(z,w,zbar,wbar);
        }
    }
    catch(...) {
        cerr << "oops in Mixed::init" << endl;
        throw;
    }
}

void MixedState::step( const double time, const double stepSize ) {

    for ( int i = 0; i< _dimension; i++ ) {
        _pureStates[i]->step( time, stepSize );
    }

}

void MixedState::print( const double t ) const {

    Matrix<complex<double> > rho(_dimension,_dimension,0.0);

    for(int k=0; k<_dimension; k++) {

        const int n = _pureStates[k]->_data.size() / 4;
        valarray<complex<double> > states(0.0, _dimension);
        states[0] = 1.0/sqrt( _dimension );
        for( int i = 0; i<n; i++ ) {
            states[i+1] = _pureStates[k]->_data[i];
        }
        //normalize somehow...
        //states /= sqrt( (states * states.apply(conj)) );
    
        Matrix<complex<double> > tmpMat(_dimension,_dimension,0.0);
        for (int i=0; i<_dimension; i++ ) {
            for (int j=0; j<_dimension; j++ ) {
                tmpMat(i+1,j+1) = _lambda[k]*states[i]*states[j];
            }
        }
        
        rho = rho + tmpMat;// no fucking += in TNT!

    }

    cout << "Density matrix is : " << rho << endl;

    complex<double> trace = 0.0;
    for (int i=1; i<_dimension+1; i++) {
        trace += rho(i,i);
    }
    cout << "with trace : " << trace << endl;

//    Matrix<double> A(3, 3,
//                             " 8.1 1.2 4.3 "
//                             " 1.3 4.3 2.9 "
//                             " 0.4 1.3 6.1 ");
//
//    Subscript N = A.num_rows();
//    Subscript M = A.num_cols();
//    assert(M == N);
//
//    Vector<double> b(N, 1.0);   // b= [1,1,1,...]
//    Vector<Subscript> index(N);
//    Vector<double> x = b;
//
//    cout << "Original Matrix A: " << A << endl;
//    
//    Fortran_Matrix<double> B(3,3,0.0);
//    //Index1D I(1,3);
//    //Index1D J(1,3);
//    //B(I,J) = A(I,J);
//    for(int i=1; i<=N; i++) {
//        for(int j=1; j<=M; j++) {
//            B(i,j) = A(i,j);
//        }
//    }
//
//
//    cout << "Fortran Matrix B: " << B << endl;

}
