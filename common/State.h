// State.h

#ifndef _STATE_H_
#define _STATE_H_

#include <complex>
using std::complex;

#include <tnt/tnt.h>
#include <tnt/tnt_cmat.h>
#include <tnt/tnt_fortran_array2d.h>
using namespace TNT;

#include <random/uniform.h>
using namespace ranlib;

class State {
  public:
    State(const int dim): 
        _dimension(dim) {};
    virtual ~State() {};

    //accessors
    virtual Matrix<complex<double> > matrix( void ) const = 0;
    virtual void print( const double time ) const  = 0;

    //mutators
    virtual void init( void ) = 0;
    virtual void step( const double time, const double stepSize ) = 0;
    virtual void perturb( Uniform<double>& generator, 
                          const double upperBound ) = 0;
  protected:
    int _dimension;// of Hilbert space (_not_ projective Hilbert space!)
};

#endif //_STATE_H_
