/*
 * $Id: tinyvecio.cc,v 1.1 2001-06-12 23:51:11 mmm Exp $
 *
 * Copyright (C) 1997 Todd Veldhuizen <tveldhui@seurat.uwaterloo.ca>
 * All rights reserved.  Please see <blitz/blitz.h> for terms and
 * conditions of use.
 *
 * $Log: tinyvecio.cc,v $
 * Revision 1.1  2001-06-12 23:51:11  mmm
 * *** empty log message ***
 *
 * Revision 1.2  1998/03/14 00:04:47  tveldhui
 * 0.2-alpha-05
 *
 * Revision 1.1  1997/07/16 14:51:20  tveldhui
 * Update: Alpha release 0.2 (Arrays)
 *
 */

#ifndef BZ_TINYVECIO_CC
#define BZ_TINYVECIO_CC

#ifndef BZ_TINYVEC_H
 #include <blitz/tinyvec.h>
#endif

BZ_NAMESPACE(blitz)

// NEEDS_WORK

template<class P_numtype, int N_length>
ostream& operator<<(ostream& os, const TinyVector<P_numtype, N_length>& x)
{
    os << "[ ";
    for (int i=0; i < N_length; ++i)
    {
        os << setw(10) << x[i];
        if (!((i+1)%7))
            os << endl << "  ";
    }
    os << " ]";
    return os;
}

BZ_NAMESPACE_END

#endif // BZ_TINYVECIO_CC
