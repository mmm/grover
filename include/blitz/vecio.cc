/*
 * $Id: vecio.cc,v 1.1 2001-06-12 23:51:12 mmm Exp $
 *
 * Copyright (C) 1997 Todd Veldhuizen <tveldhui@seurat.uwaterloo.ca>
 * All rights reserved.  Please see <blitz/blitz.h> for terms and
 * conditions of use.
 *
 * $Log: vecio.cc,v $
 * Revision 1.1  2001-06-12 23:51:12  mmm
 * *** empty log message ***
 *
 * Revision 1.5  1998/03/14 00:04:47  tveldhui
 * 0.2-alpha-05
 *
 * Revision 1.4  1997/07/16 14:51:20  tveldhui
 * Update: Alpha release 0.2 (Arrays)
 *
 * Revision 1.3  1997/01/24 14:42:00  tveldhui
 * Periodic RCS update
 *
 */

#ifndef BZ_VECIO_CC
#define BZ_VECIO_CC

#ifndef BZ_VECTOR_H
 #include <blitz/vector.h>
#endif

BZ_NAMESPACE(blitz)

// This version of operator<< is provided as a temporary measure
// only.  It will be revised in a future release.
// NEEDS_WORK

template<class P_numtype>
ostream& operator<<(ostream& os, const Vector<P_numtype>& x)
{
    os << "[ ";
    for (int i=0; i < x.length(); ++i)
    {
        os << setw(10) << x[i];
        if (!((i+1)%7))
            os << endl << "  ";
    }
    os << " ]";
    return os;
}

template<class P_expr>
ostream& operator<<(ostream& os, _bz_VecExpr<P_expr> expr)
{
    Vector<_bz_typename P_expr::T_numtype> result(expr);
    os << result;
    return os;
}

BZ_NAMESPACE_END

#endif // BZ_VECIO_CC
