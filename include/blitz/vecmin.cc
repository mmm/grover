/*
 * $Id: vecmin.cc,v 1.1 2001-06-12 23:51:12 mmm Exp $
 *
 * Copyright (C) 1997 Todd Veldhuizen <tveldhui@seurat.uwaterloo.ca>
 * All rights reserved.  Please see <blitz/blitz.h> for terms and
 * conditions of use.
 *
 * $Log: vecmin.cc,v $
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

#ifndef BZ_VECMIN_CC
#define BZ_VECMIN_CC

#ifndef BZ_VECGLOBS_H
 #error <blitz/vecmin.cc> must be included via <blitz/vecglobs.h>
#endif

BZ_NAMESPACE(blitz)

template<class P_expr>
inline
Extremum<_bz_typename P_expr::T_numtype, int> _bz_vec_min(P_expr vector)
{
    typedef _bz_typename P_expr::T_numtype T_numtype;

    T_numtype minValue = vector(0);
    int minIndex = 0;
    int length = vector._bz_suggestLength();

    if (vector._bz_hasFastAccess())
    {
        for (int i=1; i < length; ++i)
        {
            T_numtype value = vector._bz_fastAccess(i);
            if (value < minValue)
            {
                minValue = value;
                minIndex = i;
            }
        }
    }
    else {
        for (int i=1; i < length; ++i)
        {
            T_numtype value = vector(i);
            if (value < minValue)
            {
                minValue = value;
                minIndex = i;
            }
        }
    }

    return Extremum<T_numtype, int>(minValue, minIndex);
}

// min(vector)
template<class P_numtype>
inline
Extremum<P_numtype,int> min(const Vector<P_numtype>& x)
{
    return _bz_vec_min(x._bz_asVecExpr());
}

// min(expr)
template<class P_expr>
inline
Extremum<_bz_typename P_expr::T_numtype,int> min(_bz_VecExpr<P_expr> x)
{
    return _bz_vec_min(x);
}

// min(vecpick)
template<class P_numtype>
inline
Extremum<P_numtype, int> min(const VectorPick<P_numtype>& x)
{
    return _bz_vec_min(x._bz_asVecExpr());
}

// min(TinyVector)
template<class P_numtype, int N_length>
inline
Extremum<P_numtype, int> min(const TinyVector<P_numtype, N_length>& x)
{
    return _bz_vec_min(x._bz_asVecExpr());
}

// minIndex(vector)
template<class P_numtype>
inline
int  minIndex(const Vector<P_numtype>& x)
{
    return _bz_vec_min(x._bz_asVecExpr()).index();
}

// maxIndex(expr)
template<class P_expr>
inline
int  minIndex(_bz_VecExpr<P_expr> x)
{
    return _bz_vec_min(x).index();
}

// minIndex(vecpick)
template<class P_numtype>
int  minIndex(const VectorPick<P_numtype>& x)
{
    return _bz_vec_min(x._bz_asVecExpr()).index();
}

// minIndex(TinyVector)
template<class P_numtype, int N_length>
int minIndex(const TinyVector<P_numtype, N_length>& x)
{
    return _bz_vec_min(x._bz_asVecExpr()).index();
}

// minValue(vector)
template<class P_numtype>
inline
int  minValue(const Vector<P_numtype>& x)
{
    return _bz_vec_min(x._bz_asVecExpr()).value();
}

// minValue(expr)
template<class P_expr>
inline
int  minValue(_bz_VecExpr<P_expr> x)
{
    return _bz_vec_min(x).value();
}

// minValue(vecpick)
template<class P_numtype>
int  minValue(const VectorPick<P_numtype>& x)
{
    return _bz_vec_min(x._bz_asVecExpr()).value();
}

// minValue(TinyVector)
template<class P_numtype, int N_length>
int  minValue(const TinyVector<P_numtype, N_length>& x)
{
    return _bz_vec_min(x._bz_asVecExpr()).value();
}

BZ_NAMESPACE_END

#endif // BZ_VECMIN_CC
