/***************************************************************************
 * blitz/zero.h          Zero elements
 *
 * $Id: zero.h,v 1.1 2001-06-12 23:51:12 mmm Exp $
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
 * $Log: zero.h,v $
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
 * Revision 1.1  1997/01/13 22:19:58  tveldhui
 * Periodic RCS update
 *
 *
 ***************************************************************************
 *
 * The purpose of the ZeroElement class is to provide an lvalue for
 * non-const element access of matrices with zero elements.  For
 * example, a tridiagonal matrix has many elements which are
 * always zero:
 *
 * [ x x 0 0 ]
 * [ x x x 0 ]
 * [ 0 x x x ]
 * [ 0 0 x x ]
 *
 * To implement an operator()(int i, int j) for a tridiagonal
 * matrix which may be used as an lvalue
 *
 * e.g. Matrix<double, Tridiagonal> M(4,4);
 *      M(1,2) = 3.0L;
 *
 * some way of returning an lvalue for the zero elements is needed.
 * (Either that, or an intermediate class must be returned -- but
 * this is less efficient).  The solution used for the Blitz++
 * library is to have a unique zero element for each numeric
 * type (float, double, etc.).  This zero element is then
 * returned as an lvalue when needed.
 *
 * The disadvantage is the possibility of setting the global
 * zero-element to something non-zero.  
 */

#ifndef BZ_ZERO_H
#define BZ_ZERO_H

#ifndef BZ_BLITZ_H
 #include <blitz/blitz.h>
#endif

BZ_NAMESPACE(blitz)

template<class P_numtype>
class ZeroElement {
public:
    typedef P_numtype T_numtype;

    static T_numtype& zero()
    { 
        return zero_; 
    }

private:
    static T_numtype zero_;
};

// Specialization of ZeroElement for complex<float>, complex<double>,
// and complex<long double>

#define BZZERO_DECLARE(T)            \
  template<>                         \
  class ZeroElement<T > {            \
  public:                            \
    static T& getZero()              \
    { return zero_; }                \
  private:                           \
    static T zero_;                  \
  }

#ifdef BZ_HAVE_COMPLEX
  BZZERO_DECLARE(complex<float>);
  BZZERO_DECLARE(complex<double>);
  BZZERO_DECLARE(complex<long double>);
#endif // BZ_HAVE_COMPLEX

BZ_NAMESPACE_END

#include <blitz/zero.cc>

#endif // BZ_ZERO_H

