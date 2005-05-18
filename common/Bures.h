// Bures.h

#ifndef _BURES_H_
#define _BURES_H_

#include <complex>
using std::complex;

#include <tnt/tnt.h>
#include <tnt/tnt_cmat.h>
using namespace TNT;

#include "State.h"

extern double distBures( const State& state1,
                         const State& state2 );

#endif // _BURES_H_
