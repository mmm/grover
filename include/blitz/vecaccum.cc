/*
 * $Id: vecaccum.cc,v 1.1 2001-06-12 23:51:11 mmm Exp $
 *
 * Copyright (C) 1997 Todd Veldhuizen <tveldhui@seurat.uwaterloo.ca>
 * All rights reserved.  Please see <blitz/blitz.h> for terms and
 * conditions of use.
 *
 * $Log: vecaccum.cc,v $
 * Revision 1.1  2001-06-12 23:51:11  mmm
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

#ifndef BZ_VECACCUM_CC
#define BZ_VECACCUM_CC

#ifndef BZ_VECGLOBS_H
 #error <blitz/vecaccum.cc> must be included via <blitz/vecglobs.h>
#endif

BZ_NAMESPACE(blitz)

template<class P>
inline
Vector<BZ_SUMTYPE(_bz_typename P::T_numtype)> _bz_vec_accumulate(P expr)
{
    typedef BZ_SUMTYPE(_bz_typename P::T_numtype) T_sumtype;
    int length = expr._bz_suggestLength();
    Vector<T_sumtype> z(length);
    T_sumtype sum = 0;

    if (expr._bz_hasFastAccess())
    {
        for (int i=0; i < length; ++i)
        {
            sum += expr._bz_fastAccess(i);
            z[i] = sum;
        }
    }
    else {
        for (int i=0; i < length; ++i)
        {
            sum += expr(i);
            z[i] = sum;
        }
    }

    return z;
}
template<class P_numtype>
Vector<BZ_SUMTYPE(P_numtype)> accumulate(const Vector<P_numtype>& x)
{
    return _bz_vec_accumulate(x);
}

template<class P_expr>
Vector<BZ_SUMTYPE(_bz_typename P_expr::T_numtype)>
accumulate(_bz_VecExpr<P_expr> x)
{
    return _bz_vec_accumulate(x);
}

template<class P_numtype>
Vector<BZ_SUMTYPE(P_numtype)> accumulate(const VectorPick<P_numtype>& x)
{
    return _bz_vec_accumulate(x);
}

BZ_NAMESPACE_END

#endif // BZ_VECACCUM_CC

