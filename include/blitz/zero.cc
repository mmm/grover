/*
 * $Id: zero.cc,v 1.1 2001-06-12 23:51:12 mmm Exp $
 *
 * Copyright (C) 1997 Todd Veldhuizen <tveldhui@seurat.uwaterloo.ca>
 * All rights reserved.  Please see <blitz/blitz.h> for terms and
 * conditions of use.
 *
 * $Log: zero.cc,v $
 * Revision 1.1  2001-06-12 23:51:12  mmm
 * *** empty log message ***
 *
 * Revision 1.3  1997/07/16 14:51:20  tveldhui
 * Update: Alpha release 0.2 (Arrays)
 *
 * Revision 1.2  1997/01/24 14:42:00  tveldhui
 * Periodic RCS update
 *
 */

#ifndef BZ_ZERO_H
 #include <blitz/zero.h>
#endif

#ifndef BZ_ZERO_CC
#define BZ_ZERO_CC

BZ_NAMESPACE(blitz)

template<class P_numtype>
P_numtype ZeroElement<P_numtype>::zero_ = 0;

#ifdef BZ_HAVE_COMPLEX

complex<float>  ZeroElement<complex<float> >::zero_ = 
    complex<float>(0.0f, 0.0f);

complex<double> ZeroElement<complex<double> >::zero_ =
    complex<double>(0.,0.);

complex<long double> ZeroElement<complex<long double> >::zero_ =
    complex<long double>(0.0L, 0.0L);

#endif // BZ_HAVE_COMPLEX

BZ_NAMESPACE_END

#endif // BZ_ZERO_CC

