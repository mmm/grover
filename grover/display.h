// display.h

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <fstream>
#include <tnt/tnt.h>
#include <tnt/cmat.h>
using namespace TNT;

extern void showProgress( const int step, const int numSteps, const int numQubits );
extern void printDiffs( ofstream& outFile, 
                        const int iteration,
                        const Matrix<complex<double> >&  rho1, 
                        const Matrix<complex<double> >&  rho2 );
extern void printLeadingEVals( ofstream& outFile, 
                               const int iteration,
                               const Matrix<complex<double> >&  rho1, 
                               const Matrix<complex<double> >&  rho2 );

#endif // _DISPLAY_H_
