// lsode.h
#ifndef _LSODE_H_
#define _LSODE_H_

// this is the march 30, 1987 version of
// lsode.. livermore solver for ordinary differential equations.
// this version is in double precision.
//
// lsode solves the initial value problem for stiff or nonstiff
// systems of first order ode-s,
//     dy/dt = f(t,y) ,  or, in component form,
//     dy(i)/dt = f(i) = f(i,t,y(1),y(2),...,y(neq)) (i = 1,...,neq).
// lsode is a package based on the gear and gearb packages, and on the
// october 23, 1978 version of the tentative odepack user interface
// standard, with minor modifications.

extern "C" double lsode_( 
    void* f,        // function f(t,y) for dy/dt
    int* neq,       // number of eqns 
    double* y,      // array of initial values
    double* t,      // initial t
    double* tout,   // first point where output is desired (.ne. t).
    int* itol,      // is atol a scalar (1) or array (2)
    double* rtol,   // relative tolerance parameter
    double* atol,   // absolute tolerance parameter (scalar or array).
                    //     ewt(i) = rtol*abs(y(i)) + atol     if itol = 1, or
                    //     ewt(i) = rtol*abs(y(i)) + atol(i)  if itol = 2.
    int* itask,     // =1 for normal computation of output values of y at t = tout.
    int* istate,    // integer flag (input and output).  set istate = 1.
    int* iopt,      // = 0 to indicate no optional inputs used.
    double* rwork,  // real work array of length at least..
                    //    20 + 16*neq                    for mf = 10,
                    //    22 +  9*neq + neq**2           for mf = 21 or 22,
                    //    22 + 10*neq + (2*ml + mu)*neq  for mf = 24 or 25.
    int* lrw,       // declared length of rwork (in user-s dimension).
    int* iwork,     // integer work array of length at least..
                    //    20        for mf = 10,
                    //    20 + neq  for mf = 21, 22, 24, or 25.
                    //   if mf = 24 or 25, input in iwork(1),iwork(2) the lower
                    //   and upper half-bandwidths ml,mu.
    int* liw,       // declared length of iwork (in user-s dimension).
    void* jac,      // name of subroutine for jacobian matrix (mf = 21 or 24).
                    //    if used, this name must be declared external in calling
                    //    program.  if not used, pass a dummy name.
    int* mf         // method flag.  standard values are..
                    //    10 for nonstiff (adams) method, no jacobian used.
                    //    21 for stiff (bdf) method, user-supplied full jacobian.
                    //    22 for stiff method, internally generated full jacobian.
                    //    24 for stiff method, user-supplied banded jacobian.
                    //    25 for stiff method, internally generated banded jacobian.
    );


//-----------------------------------------------------------------------
// summary of usage.
//
// communication between the user and the lsode package, for normal
// situations, is summarized here.  this summary describes only a subset
// of the full set of options available.  see the full description for
// details, including optional communication, nonstandard options,
// and instructions for special situations.  see also the example
// problem (with program and output) following this summary.
//
// a. first provide a subroutine of the form..
//               subroutine f (neq, t, y, ydot)
//               dimension y(neq), ydot(neq)
// which supplies the vector function f by loading ydot(i) with f(i).
//
// b. next determine (or guess) whether or not the problem is stiff.
// stiffness occurs when the jacobian matrix df/dy has an eigenvalue
// whose real part is negative and large in magnitude, compared to the
// reciprocal of the t span of interest.  if the problem is nonstiff,
// use a method flag mf = 10.  if it is stiff, there are four standard
// choices for mf, and lsode requires the jacobian matrix in some form.
// this matrix is regarded either as full (mf = 21 or 22),
// or banded (mf = 24 or 25).  in the banded case, lsode requires two
// half-bandwidth parameters ml and mu.  these are, respectively, the
// widths of the lower and upper parts of the band, excluding the main
// diagonal.  thus the band consists of the locations (i,j) with
// i-ml .le. j .le. i+mu, and the full bandwidth is ml+mu+1.
//
// c. if the problem is stiff, you are encouraged to supply the jacobian
// directly (mf = 21 or 24), but if this is not feasible, lsode will
// compute it internally by difference quotients (mf = 22 or 25).
// if you are supplying the jacobian, provide a subroutine of the form..
//               subroutine jac (neq, t, y, ml, mu, pd, nrowpd)
//               dimension y(neq), pd(nrowpd,neq)
// which supplies df/dy by loading pd as follows..
//     for a full jacobian (mf = 21), load pd(i,j) with df(i)/dy(j),
// the partial derivative of f(i) with respect to y(j).  (ignore the
// ml and mu arguments in this case.)
//     for a banded jacobian (mf = 24), load pd(i-j+mu+1,j) with
// df(i)/dy(j), i.e. load the diagonal lines of df/dy into the rows of
// pd from the top down.
//     in either case, only nonzero elements need be loaded.
//
// d. write a main program which calls subroutine lsode once for
// each point at which answers are desired.  this should also provide
// for possible use of logical unit 6 for output of error messages
// by lsode.  on the first call to lsode, supply arguments as follows..
// f      = name of subroutine for right-hand side vector f.
//          this name must be declared external in calling program.
// neq    = number of first order ode-s.
// y      = array of initial values, of length neq.
// t      = the initial value of the independent variable.
// tout   = first point where output is desired (.ne. t).
// itol   = 1 or 2 according as atol (below) is a scalar or array.
// rtol   = relative tolerance parameter (scalar).
// atol   = absolute tolerance parameter (scalar or array).
//          the estimated local error in y(i) will be controlled so as
//          to be roughly less (in magnitude) than
//             ewt(i) = rtol*abs(y(i)) + atol     if itol = 1, or
//             ewt(i) = rtol*abs(y(i)) + atol(i)  if itol = 2.
//          thus the local error test passes if, in each component,
//          either the absolute error is less than atol (or atol(i)),
//          or the relative error is less than rtol.
//          use rtol = 0.0 for pure absolute error control, and
//          use atol = 0.0 (or atol(i) = 0.0) for pure relative error
//          control.  caution.. actual (global) errors may exceed these
//          local tolerances, so choose them conservatively.
// itask  = 1 for normal computation of output values of y at t = tout.
// istate = integer flag (input and output).  set istate = 1.
// iopt   = 0 to indicate no optional inputs used.
// rwork  = real work array of length at least..
//             20 + 16*neq                    for mf = 10,
//             22 +  9*neq + neq**2           for mf = 21 or 22,
//             22 + 10*neq + (2*ml + mu)*neq  for mf = 24 or 25.
// lrw    = declared length of rwork (in user-s dimension).
// iwork  = integer work array of length at least..
//             20        for mf = 10,
//             20 + neq  for mf = 21, 22, 24, or 25.
//          if mf = 24 or 25, input in iwork(1),iwork(2) the lower
//          and upper half-bandwidths ml,mu.
// liw    = declared length of iwork (in user-s dimension).
// jac    = name of subroutine for jacobian matrix (mf = 21 or 24).
//          if used, this name must be declared external in calling
//          program.  if not used, pass a dummy name.
// mf     = method flag.  standard values are..
//          10 for nonstiff (adams) method, no jacobian used.
//          21 for stiff (bdf) method, user-supplied full jacobian.
//          22 for stiff method, internally generated full jacobian.
//          24 for stiff method, user-supplied banded jacobian.
//          25 for stiff method, internally generated banded jacobian.
// note that the main program must declare arrays y, rwork, iwork,
// and possibly atol.
//
// e. the output from the first call (or any call) is..
//      y = array of computed values of y(t) vector.
//      t = corresponding value of independent variable (normally tout).
// istate = 2  if lsode was successful, negative otherwise.
//          -1 means excess work done on this call (perhaps wrong mf).
//          -2 means excess accuracy requested (tolerances too small).
//          -3 means illegal input detected (see printed message).
//          -4 means repeated error test failures (check all inputs).
//          -5 means repeated convergence failures (perhaps bad jacobian
//             supplied or wrong choice of mf or tolerances).
//          -6 means error weight became zero during problem. (solution
//             component i vanished, and atol or atol(i) = 0.)
//
// f. to continue the integration after a successful return, simply
// reset tout and call lsode again.  no other parameters need be reset.
//

#endif //_LSODE_H_
