// display.h

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <iostream>
#include <fstream>
#include "State.h"

extern void showProgress( std::ostream& out, 
                          const int step, 
                          const int numSteps, 
                          const int numQubits );
extern void printDiffs( std::ofstream& outFile, 
                        const double time,
                        const State *const rho1, 
                        const State *const rho2 );
extern void printLeadingEVals( std::ofstream& outFile, 
                               const double time,
                               const State *const rho1, 
                               const State *const rho2 );

#endif // _DISPLAY_H_
