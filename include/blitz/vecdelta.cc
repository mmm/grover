/*
 * $Id: vecdelta.cc,v 1.1 2001-06-12 23:51:12 mmm Exp $
 *
 * Copyright (C) 1997 Todd Veldhuizen <tveldhui@seurat.uwaterloo.ca>
 * All rights reserved.  Please see <blitz/blitz.h> for terms and
 * conditions of use.
 *
 * $Log: vecdelta.cc,v $
 * Revision 1.1  2001-06-12 23:51:12  mmm
 * *** empty log message ***
 *
 * Revision 1.4  1998/03/14 00:04:47  tveldhui
 * 0.2-alpha-05
 *
 * Revision 1.3  1997/07/16 14:51:20  tveldhui
 * Update: Alpha release 0.2 (Arrays)
 *
 * Revision 1.2  1997/01/24 14:42:00  tveldhui
 * Periodic RCS update
 *
 */

#ifndef BZ_VECDELTA_CC
#define BZ_VECDELTA_CC

#ifndef BZ_VECGLOBS_H
 #error <blitz/vecdelta.cc> must be included via <blitz/vecglobs.h>
#endif

BZ_NAMESPACE(blitz)

template<class P>
inline
Vector<BZ_DIFFTYPE(_bz_typename P::T_numtype)> _bz_vec_delta(P expr)
{
    typedef _bz_typename P::T_numtype   T_numtype;
    typedef BZ_DIFFTYPE(T_numtype)      T_difftype;

    int length = expr._bz_suggestLength();
    Vector<T_difftype> z(length);
    T_numtype currentElement = 0;
    T_numtype previousElement = 0;

    if (expr._bz_hasFastAccess())
    {
        for (int i=0; i < length; ++i)
        {
            currentElement = expr._bz_fastAccess(i);
            z[i] = currentElement - previousElement;
            previousElement = currentElement;
        }
    }
    else {
        for (int i=1; i < length; ++i)
        {
            currentElement = expr(i);
            z[i] = currentElement - previousElement;
            previousElement = currentElement;
        }
    }

    return z;
}

template<class P_numtype>
Vector<BZ_DIFFTYPE(P_numtype)> delta(const Vector<P_numtype>& x)
{
    return _bz_vec_delta(x);
}

// delta(expr)
template<class P_expr>
Vector<BZ_DIFFTYPE(_bz_typename P_expr::T_numtype)> delta(_bz_VecExpr<P_expr> x)
{
    return _bz_vec_delta(x);
}

// delta(vecpick)
template<class P_numtype>
Vector<BZ_DIFFTYPE(P_numtype)> delta(const VectorPick<P_numtype>& x)
{
    return _bz_vec_delta(x);
}

BZ_NAMESPACE_END

#endif // BZ_VECDELTA_CC

