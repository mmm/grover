// State.h

#ifndef _STATE_H_
#define _STATE_H_

#include <complex>

#include <tnt/tnt.h>
#include <tnt/cmat.h>
#include <tnt/fmat.h>

using namespace TNT;

class State {
  public:
    State(const int dim): 
        _dimension(dim) {};
    virtual ~State() {};

    virtual Matrix<complex<double> > matrix( void ) const = 0;

    virtual void init( void ) = 0;
    virtual void step( const double time, const double stepSize ) = 0;
    virtual void print( const double time ) const  = 0;
  protected:
    int _dimension;// of Hilbert space (_not_ projective Hilbert space!)
};


#endif //_STATE_H_