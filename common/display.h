// display.h

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "State.h"

extern void showProgress( const int step, const int numSteps, const int numQubits );
extern void printDiffs( const State *const rho1, const State *const rho2 );

#endif // _DISPLAY_H_
