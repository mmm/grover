// State.h

#ifndef _STATE_H_
#define _STATE_H_

#include <vector>
#include "myvalarray.h"

class State {
  public:
    State(const int dim): 
        _dimension(dim) {};
    virtual ~State() {};
    virtual void init( void ) = 0;
    virtual void step( const double time, const double stepSize ) = 0;
    virtual void print( const double time ) const  = 0;
  protected:
    int _dimension;// of Hilbert space (_not_ projective Hilbert space!)
};

class PureState: public State {
  public:
    PureState( const int dim ): 
        State(dim), _data( double(0), 4*(dim-1) ) {};
    virtual ~PureState() {};

    virtual void init( void );
    virtual void step( const double time, const double stepSize );
    virtual void print( const double time ) const ;

//private:
    valarray<double>  _data;
};

class MixedState: public State {
  public:
    MixedState( const int dim ):
        State(dim), _lambda(dim,0.0) {};
    virtual ~MixedState();

    virtual void init( void );
    virtual void step( const double time, const double stepSize );
    virtual void print( const double time ) const ;
  private:
    vector<double> _lambda;
    vector<PureState*> _pureStates;
};

#endif //_STATE_H_
