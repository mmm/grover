// fwrap.h

#ifndef _FWRAP_H_
#define _FWRAP_H_

#include <complex>
#include <tnt/tnt.h>
#include <tnt/vec.h>
#include <tnt/fmat.h>

using namespace TNT;
//Vector<double> Hermitian_eigenvalue_solve(const Fortran_Matrix<std::complex<double> >& A);
Vector<double> Hermitian_eigenvalue_solve(Fortran_Matrix<std::complex<double> >& A);

void get_eps(void);

#endif // _FWRAP_H_
