// State.C
#include <stdexcept>
#include "rk4.h"

#include "PureState.h"
   
void PureState::init(void) { 


    if ( _data.size() % 4 ) throw;
    const int n = _data.size() / 4;

    try {
        valarray<double> z(1.0/sqrt(_dimension), n);
        valarray<double> w(-10.0, n);
        //valarray<double> w(0.0, n);
        valarray<double> zbar(0.0, n);
        valarray<double> wbar(0.0, n);
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
   
void PureState::init( const valarray<double> z_i,
                      const valarray<double> w_i,
                      const valarray<double> zbar_i,
                      const valarray<double> wbar_i ) { 


    if ( _data.size() % 4 ) throw;
    const int n = _data.size() / 4;

    try {
        for( int i = 0; i<n; i++ ) {
            _data[i] = z_i[i];
            _data[n+i] = w_i[i];
            _data[2*n+i] = zbar_i[i];
            _data[3*n+i] = wbar_i[i];
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

Matrix<complex<double> > PureState::matrix( void ) const {

    Matrix<complex<double> > rho(_dimension,_dimension,0.0);

    try {
        const int n = _data.size() / 4;
        valarray<complex<double> > states(0.0, _dimension);
        states[0] = complex<double>( 1.0/sqrt( _dimension ), 0.0 );
        for( int i = 0; i<n; i++ ) {
            states[i+1] = complex<double>( _data[i], _data[2*n+i] );
        }
        //normalize...
        states /= sqrt(abs(
                    static_cast<valarray<complex<double> > >(states) * 
                    static_cast<valarray<complex<double> > >(states.apply(conj))
                  ));
    
        for (int i=0; i<_dimension; i++ ) {
            for (int j=0; j<_dimension; j++ ) {
                rho(i+1,j+1) = states[i]*conj(states[j]);
            }
        }
    }
    catch(out_of_range) {
        cerr << "oops" << endl;
        exit(1);
    }

    return rho;

}

void PureState::print( const double t ) const { 

    Matrix<complex<double> > rho = matrix();

    cout << "Pure state density matrix is : " << rho << endl;

    complex<double> trace = 0.0;
    for (int i=1; i<_dimension+1; i++) {
        trace += rho(i,i);
    }
    cout << "with trace : " << abs(trace) << endl;

}

void PureState::perturb( Uniform<double>& generator, const double upperBound ) {

//    cout << "PureState random number = " 
//         << ( generator.random() - 0.5 ) * upperBound 
//         << endl;

    if ( _data.size() % 4 ) throw;
    const int n = _data.size() / 4;

    try {
        for( int i = 0; i<n; i++ ) {
            _data[i] += ( generator.random() - 0.5 ) * upperBound;
        }
        for( int i = 2*n; i<3*n; i++ ) {
            _data[i] += ( generator.random() - 0.5 ) * upperBound;
        }
    }
    catch(out_of_range) {
        cerr << "oops" << endl;
        exit(1);
    }

}
