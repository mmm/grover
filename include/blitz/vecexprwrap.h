/***************************************************************************
 * blitz/vecexprwrap.h   Vector expression templates wrapper class
 *
 * $Id: vecexprwrap.h,v 1.1 2001-06-12 23:51:12 mmm Exp $
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
 * $Log: vecexprwrap.h,v $
 * Revision 1.1  2001-06-12 23:51:12  mmm
 * *** empty log message ***
 *
 * Revision 1.2  1998/03/14 00:04:47  tveldhui
 * 0.2-alpha-05
 *
 * Revision 1.1  1997/07/16 14:51:20  tveldhui
 * Update: Alpha release 0.2 (Arrays)
 *
 */

#ifndef BZ_VECEXPRWRAP_H
#define BZ_VECEXPRWRAP_H

#ifndef BZ_BLITZ_H
 #include <blitz/blitz.h>
#endif

BZ_NAMESPACE(blitz)

template<class P_expr>
class _bz_VecExpr {

public:
    typedef P_expr T_expr;
    typedef _bz_typename T_expr::T_numtype T_numtype;

#ifdef BZ_PASS_EXPR_BY_VALUE
    _bz_VecExpr(T_expr a)
        : iter_(a)
    { }
#else
    _bz_VecExpr(const T_expr& a)
        : iter_(a)
    { }
#endif

#ifdef BZ_MANUAL_VECEXPR_COPY_CONSTRUCTOR
    _bz_VecExpr(const _bz_VecExpr<T_expr>& a)
        : iter_(a.iter_)
    { }
#endif

    T_numtype operator[](int i) const
    { return iter_[i]; }

    T_numtype operator()(int i) const
    { return iter_(i); }

    int length(int recommendedLength) const
    { return iter_.length(recommendedLength); }

    enum { _bz_staticLengthCount = BZ_ENUM_CAST(P_expr::_bz_staticLengthCount),
           _bz_dynamicLengthCount = BZ_ENUM_CAST(P_expr::_bz_dynamicLengthCount),
           _bz_staticLength = BZ_ENUM_CAST(P_expr::_bz_staticLength) };

    int _bz_suggestLength() const
    { return iter_._bz_suggestLength(); }

    _bz_bool _bz_hasFastAccess() const
    { return iter_._bz_hasFastAccess(); }

    T_numtype _bz_fastAccess(int i) const
    { return iter_._bz_fastAccess(i); }

private:
    _bz_VecExpr();

    T_expr iter_;
};

BZ_NAMESPACE_END

#endif // BZ_VECEXPRWRAP_H
