// fwrap.C
// Fortran Wrappers
#include <iostream>
#include <complex>

#include <tnt/tnt.h>
#include <tnt/tnt_vec.h>
#include <tnt/tnt_fortran_array2d.h>

//#include <tnt/fortran.h>
//#include "fortran.h"

using namespace TNT;

#define F77_DGESV   dgesv_
#define F77_DGELS   dgels_
#define F77_DSYEV   dsyev_
#define F77_DGEEV   dgeev_
#define F77_ZHEEV   zheev_
#define F77_ZHEEVD  zheevd_
#define F77_DLAMCH  dlamch_

extern "C"
{

    // linear equations (general) using LU factorizaiton
    //
    void F77_DGESV(cfi_ N, cfi_ nrhs, fda_ A, cfi_ lda,
        fia_ ipiv, fda_ b, cfi_ ldb, fi_ info);

    // solve linear least squares using QR or LU factorization
    //
    void F77_DGELS(cfch_ trans, cfi_ M, 
        cfi_ N, cfi_ nrhs, fda_ A, cfi_ lda, fda_ B, cfi_ ldb, fda_ work, 
            cfi_ lwork, fi_ info);

    // solve symmetric eigenvalues
    //
    void F77_DSYEV( cfch_ jobz, cfch_ uplo, cfi_ N, fda_  A, cfi_ lda, 
        fda_ W, fda_ work, cfi_ lwork, fi_ info);

    // solve unsymmetric eigenvalues
    //
    void F77_DGEEV(cfch_ jobvl, cfch_ jobvr, cfi_ N, fda_ A, cfi_ lda,
        fda_ wr, fda_ wi, fda_ vl, cfi_ ldvl, fda_ vr, 
        cfi_ ldvr, fda_ work, cfi_ lwork, fi_ info);

    // solve complex Hermitian eigenvalues and eigenvectors
    //
//    void F77_ZHEEV( cfch_ jobz, cfch_ uplo, cfi_ N, fda_  A, cfi_ lda, 
//        fda_ W, fda_ work, cfi_ lwork, fda_ rwork, fi_ info);
    void F77_ZHEEV( cfch_ jobz, cfch_ uplo, cfi_ N, fda_  A, cfi_ lda, 
        fda_ W, fda_ work, cfi_ lwork, fda_ rwork, fi_ info);

    // solve complex Hermitian eigenvalues and eigenvectors
    // with divide and conquer
    //
    void F77_ZHEEVD(cfch_ jobz, cfch_ uplo, cfi_ N, fda_  A, cfi_ lda, 
        fda_ W, fda_ work, cfi_ lwork, fda_ rwork, cfi_ lrwork, fi_ iwork, 
            cfi_ liwork, fi_ info);

    Fortran_double F77_DLAMCH(cfch_ ch);

}

// solve linear equations using LU factorization

using namespace TNT;

Vector<double> Lapack_LU_linear_solve(const Fortran_Array2D<double> &A,
    const Vector<double> &b)
{
    const Fortran_integer one=1;
    Subscript M=A.num_rows();
    Subscript N=A.num_cols();

    Fortran_Array2D<double> Tmp(A);
    Vector<double> x(b);
    Vector<Fortran_integer> index(M);
    Fortran_integer info = 0;

    F77_DGESV(&N, &one, &Tmp(1,1), &M, &index(1), &x(1), &M, &info);    

    if (info != 0) return Vector<double>(0);
    else
        return x;
}

// solve linear least squares problem using QR factorization
//
Vector<double> Lapack_LLS_QR_linear_solve(const Fortran_Array2D<double> &A,
    const Vector<double> &b)
{
    const Fortran_integer one=1;
    Subscript M=A.num_rows();
    Subscript N=A.num_cols();

    Fortran_Array2D<double> Tmp(A);
    Vector<double> x(b);
    Fortran_integer info = 0;

    char transp = 'N';
    Fortran_integer lwork = 5 * (M+N);      // temporary work space
    Vector<double> work(lwork);

    F77_DGELS(&transp, &M, &N, &one, &Tmp(1,1), &M, &x(1), &M,  &work(1),
        &lwork, &info); 

    if (info != 0) return Vector<double>(0);
    else
        return x;
}

// *********************** Eigenvalue problems *******************

// solve symmetric eigenvalue problem (eigenvalues only)
//
Vector<double> Upper_symmetric_eigenvalue_solve(const Fortran_Array2D<double> &A)
{
    char jobz = 'N';
    char uplo = 'U';
    Subscript N = A.num_rows();

    assert(N == A.num_cols());

    Vector<double> eigvals(N);
    Fortran_integer worksize = 3*N;
    Fortran_integer info = 0;
    Vector<double> work(worksize);
    Fortran_Array2D<double> Tmp = A;

    F77_DSYEV(&jobz, &uplo, &N, &Tmp(1,1), &N, eigvals.begin(), work.begin(),
        &worksize, &info);

    if (info != 0) return Vector<double>();
    else
        return eigvals;
}


// solve unsymmetric eigenvalue problems 
//
int eigenvalue_solve(const Fortran_Array2D<double> &A, 
        Vector<double> &wr, Vector<double> &wi)
{
    char jobvl = 'N';
    char jobvr = 'N';

    Fortran_integer N = A.num_rows();


    assert(N == A.num_cols());
    
    if (N<1) return 1;

    Fortran_Array2D<double> vl(1,N);  /* should be NxN ? **** */
    Fortran_Array2D<double> vr(1,N);  
    Fortran_integer one = 1;

    Fortran_integer worksize = 5*N;
    Fortran_integer info = 0;
    Vector<double> work(worksize, 0.0);
    Fortran_Array2D<double> Tmp = A;

    wr.newsize(N);
    wi.newsize(N);

//  void F77_DGEEV(cfch_ jobvl, cfch_ jobvr, cfi_ N, fda_ A, cfi_ lda,
//      fda_ wr, fda_ wi, fda_ vl, cfi_ ldvl, fda_ vr, 
//      cfi_ ldvr, fda_ work, cfi_ lwork, fi_ info);

    F77_DGEEV(&jobvl, &jobvr, &N, &Tmp(1,1), &N, &(wr(1)),
        &(wi(1)), &(vl(1,1)), &one, &(vr(1,1)), &one,
        &(work(1)), &worksize, &info);

    return (info==0 ? 0: 1);
}


// solve complex Hermitian eigenvalues and eigenvectors
//
// returns eigVects in A
Vector<double> 
Hermitian_eigenvalue_solve( Fortran_Array2D<std::complex<double> >& A)
{

    char jobz = 'V';
    char uplo = 'U';
    Subscript N = A.num_rows();

    assert(N == A.num_cols());

    Vector<double> eigvals(N);
    //Fortran_integer worksize = 3*N;
    Fortran_integer worksize = 6*N;
    Vector<complex<double> > work(worksize);
    //Fortran_integer rworksize = 3*N;
    Fortran_integer rworksize = 6*N;
    Vector<double> rwork(rworksize);
    Fortran_integer info = 0;

//    void F77_DSYEV( cfch_ jobz, cfch_ uplo, cfi_ N, fda_  A, cfi_ lda, 
//        fda_ W, fda_ work, cfi_ lwork, fda_ rwork, fi_ info);
    F77_ZHEEV(&jobz, &uplo, &N, (fda_)(&A(1,1)), 
              &N, eigvals.begin(), (fda_)(work.begin()),
              &worksize, rwork.begin(), &info);

    if (info != 0) return Vector<double>();
    else
        return eigvals;
}

double get_eps(void) {

    char ch = 'E';
    return F77_DLAMCH(&ch);

}

