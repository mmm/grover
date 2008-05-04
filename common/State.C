// State.C
#include <stdexcept>
#include "rk4.h"

#include <tnt/tnt.h>
#include <tnt/tnt_cmat.h>
#include <tnt/tnt_fortran_array2d.h>

//#include <tnt/fortran.h>
//#include <tnt/lapack.h>
//#include <tnt/lu.h>

#include "State.h"
   
void PureState::init(void) { 


    if ( _data.size() % 4 ) throw;
    const int n = _data.size() / 4;

    try {
        valarray<double> z(1.0/sqrt(_dimension), n);
        valarray<double> w(-10.0, n);
        valarray<double> zbar(1.0/sqrt(_dimension), n);
        valarray<double> wbar(-10.0, n);
        for( int i = 0; i<n; i++ ) {
            _data[i] = z[i];
            _data[n+i] = w[i];
            _data[2*n+i] = zbar[i];
            _data[3*n+i] = wbar[i];
        }
    }
    catch(out_of_range) {
        cerr << "oops" << endl;
        exit(1);
    }

}

void PureState::step( const double time, const double stepSize ) { 

    _data += stepRk4( time, _data, stepSize );

}


void PureState::print( const double t ) const { 

    if ( _data.size() % 4 ) throw;

    const int n = _data.size() / 4;

    try {
        valarray<double> states(0.0, n+1);
        states[0] = 1.0/sqrt( _dimension );
        for( int i = 0; i<n; i++ ) {
            states[i+1] = _data[i];
        }

        // normalize
        states /= sqrt( states*states );
#ifdef TELL_ME
        //mmm use logger
//        //cout << "t= " << t << endl;
//        for(int i = 0; i< n+1; i++ ) {
//            cout << "states[" << i << "] = " << states[i] << endl;
//        }
//        //cout << "states*states = " << states*states << endl;
#endif //TELL_ME

    }
    catch(out_of_range) {
        //mmm use logger
        cerr << "oops" << endl;
        exit(1);
    }

}


MixedState::~MixedState() {
    for ( int i = 0; i< _dimension; i++ ) {
        delete _pureStates[i];
    }
}

void MixedState::init( void ) {

    _lambda[0] = 1.0;

    try{
        for ( int i = 0; i< _dimension; i++ ) {
            _pureStates.push_back( new PureState(_dimension) );
            _pureStates[i]->init();
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

using namespace TNT;
void MixedState::print( const double t ) const {

    Matrix<double> rho(_dimension,_dimension,0.0);

    for(int k=0; k<_dimension; k++) {

        const int n = _pureStates[k]->_data.size() / 4;
        valarray<double> states(0.0, n+1);
        states[0] = 1.0/sqrt( _dimension );
        for( int i = 0; i<n; i++ ) {
            states[i+1] = _pureStates[k]->_data[i];
        }
        // normalize
        states /= sqrt( states*states );
    
        Matrix<double> tmpMat(_dimension,_dimension,0.0);
        for (int i=0; i<_dimension; i++ ) {
            for (int j=0; j<_dimension; j++ ) {
                tmpMat(i+1,j+1) = _lambda[k]*states[i]*states[j];
            }
        }
        
        rho = rho + tmpMat;

    }

    //mmm use logger
    //cout << "Density matrix is : " << rho << endl;

    double trace = 0.0;
    for (int i=1; i<_dimension+1; i++) {
        trace += rho(i,i);
    }
    //mmm use logger
    //cout << "with trace : " << trace << endl;

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
