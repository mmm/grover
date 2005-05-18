// MixedState.h

#ifndef _MIXEDSTATE_H_
#define _MIXEDSTATE_H_

#include <vector>
#include <valarray>

#include "PureState.h"

class MixedState: public State {
  public:
    MixedState( const int dim ):
        State(dim), _lambda(0.0,dim) {};
    virtual ~MixedState();

    //accessors
    virtual Matrix<complex<double> > matrix( void ) const;
    virtual void print( const double time ) const ;

    //mutators
    virtual void init( void );
    virtual void step( const double time, const double stepSize );
    virtual void perturb( Uniform<double>& generator, const double upperBound );
  private:
    std::valarray<double> _lambda;
    std::vector<PureState*> _pureStates;
};


#endif //_MIXEDSTATE_H_
