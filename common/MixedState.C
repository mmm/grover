// State.C
#include <stdexcept>

#include "rk4.h"
#include "MixedState.h"
   
MixedState::~MixedState() {
    for ( int i = 0; i< _dimension; i++ ) {
        delete _pureStates[i];
    }
}

void MixedState::init( void ) {

    _lambda[0] = 1.0;

    try{
        valarray<double> z(1.0/sqrt(_dimension), _dimension - 1);
        valarray<double> w(0.0, _dimension - 1);
        //valarray<double> w(-10.0, _dimension - 1);
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

Matrix<complex<double> > MixedState::matrix( void ) const {

    Matrix<complex<double> > rho(_dimension,_dimension,0.0);

    for(int k=0; k<_dimension; k++) {

        const int n = _pureStates[k]->_data.size() / 4;
        valarray<complex<double> > states(0.0, _dimension);
        states[0] = complex<double>( 1.0/sqrt( _dimension ), 0.0 );
        for( int i = 0; i<n; i++ ) {
            states[i+1] = complex<double>( _pureStates[k]->_data[i], 
                            _pureStates[k]->_data[2*n+i] );
        }
        //normalize...
        states /= sqrt(abs(
                    static_cast<valarray<complex<double> > >(states) * 
                    static_cast<valarray<complex<double> > >(states.apply(conj))
                  ));
    
        Matrix<complex<double> > tmpMat(_dimension,_dimension,0.0);
        for (int i=0; i<_dimension; i++ ) {
            for (int j=0; j<_dimension; j++ ) {
                tmpMat(i+1,j+1) = _lambda[k]*states[i]*conj(states[j]);
            }
        }
        
        rho = rho + tmpMat;// no "+=" in TNT!

    }

    return rho;

}

void MixedState::print( const double t ) const {

    Matrix<complex<double> > rho = matrix();

    cout << "Density matrix is : " << rho << endl;

    complex<double> trace = 0.0;
    for (int i=1; i<_dimension+1; i++) {
        trace += rho(i,i);
    }
    cout << "with trace : " << abs(trace) << endl;

}
