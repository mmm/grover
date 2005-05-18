// fwrap.h

#ifndef _FWRAP_H_
#define _FWRAP_H_

#include <complex>
#include <tnt/tnt.h>
#include <tnt/tnt_vec.h>
#include <tnt/tnt_fortran_array2d.h>

using namespace TNT;
//Vector<double> Hermitian_eigenvalue_solve(const Fortran_Array2D<std::complex<double> >& A);
Vector<double> Hermitian_eigenvalue_solve(Fortran_Array2D<std::complex<double> >& A);

double get_eps(void);

#endif // _FWRAP_H_
