// PureState.h

#ifndef _PURESTATE_H_
#define _PURESTATE_H_

#include "myvalarray.h"
#include "State.h"

class PureState: public State {
  public:
    PureState( const int dim ): 
        State(dim), _data( double(0), 4*(dim-1) ) {};
    virtual ~PureState() {};

    //accessors
    virtual Matrix<complex<double> > matrix( void ) const;
    virtual void print( const double time ) const ;

    //mutators
    virtual void init( void );
    virtual void init( const valarray<double>& z_i,
                       const valarray<double>& w_i,
                       const valarray<double>& zbar_i,
                       const valarray<double>& wbar_i );
    virtual void step( const double time, const double stepSize );
    virtual void perturb( Uniform<double>& generator, const double upperBound );

//private:
    valarray<double>  _data;
};

#endif //_PURESTATE_H_
