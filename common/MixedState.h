// MixedState.h

#ifndef _MIXEDSTATE_H_
#define _MIXEDSTATE_H_

#include <vector>

#include "PureState.h"

class MixedState: public State {
  public:
    MixedState( const int dim ):
        State(dim), _lambda(dim,0.0) {};
    virtual ~MixedState();

    virtual Matrix<complex<double> > matrix( void ) const;

    virtual void init( void );
    virtual void step( const double time, const double stepSize );
    virtual void print( const double time ) const ;
  private:
    vector<double> _lambda;
    vector<PureState*> _pureStates;
};


#endif //_MIXEDSTATE_H_
