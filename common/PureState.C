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
        cout << "t= " << t << endl;
        for(int i = 0; i< n+1; i++ ) {
            cout << "states[" << i << "] = " << states[i] << endl;
        }
        cout << "states*states = " << states*states << endl;
#endif //TELL_ME

    }
    catch(out_of_range) {
        cerr << "oops" << endl;
        exit(1);
    }

}
