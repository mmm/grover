/***************************************************************************
 * blitz/shapecheck.h    Functions for checking conformability of arrays
 *
 * $Id: shapecheck.h,v 1.1 2001-06-12 23:51:11 mmm Exp $
 *
 * Copyright (C) 1997,1998 Todd Veldhuizen <tveldhui@seurat.uwaterloo.ca>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Suggestions:          blitz-suggest@cybervision.com
 * Bugs:                 blitz-bugs@cybervision.com
 *
 * For more information, please see the Blitz++ Home Page:
 *    http://seurat.uwaterloo.ca/blitz/
 *
 ***************************************************************************
 * $Log: shapecheck.h,v $
 * Revision 1.1  2001-06-12 23:51:11  mmm
 * *** empty log message ***
 *
 * Revision 1.1  1998/03/14 00:04:47  tveldhui
 * 0.2-alpha-05
 *
 */

#ifndef BZ_SHAPECHECK_H
#define BZ_SHAPECHECK_H

BZ_NAMESPACE(blitz)

/*
 * The function areShapesConformable(A,B) checks that the shapes 
 * A and B are conformable (i.e. the same size/geometry).  Typically 
 * the A and B parameters are of type TinyVector<int,N_rank> and represent 
 * the extent of the arrays.  It's possible that in the future jagged-edged
 * arrays will be supported, in which case shapes may be lists
 * of subdomains.
 */

template<class T_shape1, class T_shape2>
inline _bz_bool areShapesConformable(const T_shape1&, const T_shape2&)
{
    // If the shape objects are different types, this means
    // that the arrays are different ranks, or one is jagged
    // edged, etc.  In this case the two arrays are not
    // conformable.
    return _bz_false;
}

template<class T_shape>
inline _bz_bool areShapesConformable(const T_shape& a, const T_shape& b)
{
    // The shape objects are the same type, so compare them.

    // NEEDS_WORK-- once the "all" reduction is implemented, should
    // use it.
    // return all(a == b);

    for (int i=0; i < a.length(); ++i)
    {
        if (a[i] != b[i])
        {
            BZ_DEBUG_MESSAGE("Incompatible shapes detected: " << endl 
                 << a << endl << b << endl);
            return _bz_false;
        }
    }

    return _bz_true;
}

BZ_NAMESPACE_END

#endif
