/***************************************************************************
 * blitz/update.h      Declaration of the _bz_XXXX updater classes
 *
 * $Id: update.h,v 1.1 2001-06-12 23:51:11 mmm Exp $
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
 * $Log: update.h,v $
 * Revision 1.1  2001-06-12 23:51:11  mmm
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
 * Revision 1.2  1997/01/23 03:28:28  tveldhui
 * Periodic RCS update
 *
 * Revision 1.1  1997/01/13 22:19:58  tveldhui
 * Periodic RCS update
 *
 *
 */

#ifndef BZ_UPDATE_H
#define BZ_UPDATE_H

#ifndef BZ_BLITZ_H
 #include <blitz/blitz.h>
#endif

BZ_NAMESPACE(blitz)

class _bz_updater_base { };

#define BZ_DECL_UPDATER(name,op,symbol)               \
  template<class X, class Y>                          \
  class name : public _bz_updater_base {              \
  public:                                             \
    static inline void update(X& _bz_restrict x, Y y) \
    { x op y; }                                       \
    static void prettyPrint(string& str)              \
    { str += symbol; }                                \
  }

template<class X, class Y>
class _bz_update : public _bz_updater_base {
  public:
    static inline void update(X& _bz_restrict x, Y y)
    { x = (X)y; }

    static void prettyPrint(string& str)
    { str += "="; }
};

BZ_DECL_UPDATER(_bz_plus_update, +=, "+=");
BZ_DECL_UPDATER(_bz_minus_update, -=, "-=");
BZ_DECL_UPDATER(_bz_multiply_update, *=, "*=");
BZ_DECL_UPDATER(_bz_divide_update, /=, "/=");
BZ_DECL_UPDATER(_bz_mod_update, %=, "%=");
BZ_DECL_UPDATER(_bz_xor_update, ^=, "^=");
BZ_DECL_UPDATER(_bz_bitand_update, &=, "&=");
BZ_DECL_UPDATER(_bz_bitor_update, |=, "|=");
BZ_DECL_UPDATER(_bz_shiftl_update, <<=, "<<=");
BZ_DECL_UPDATER(_bz_shiftr_update, >>=, ">>=");

BZ_NAMESPACE_END

#endif // BZ_UPDATE_H

