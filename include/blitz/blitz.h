/***************************************************************************
 * blitz/blitz.h      Includes all the important header files
 *
 * $Id: blitz.h,v 1.1 2001-06-12 23:51:10 mmm Exp $
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
 * $Log: blitz.h,v $
 * Revision 1.1  2001-06-12 23:51:10  mmm
 * *** empty log message ***
 *
 * Revision 1.7  1998/03/14 00:04:47  tveldhui
 * 0.2-alpha-05
 *
 * Revision 1.6  1997/07/16 14:51:20  tveldhui
 * Update: Alpha release 0.2 (Arrays)
 *
 * Revision 1.5  1997/01/24 14:42:00  tveldhui
 * Periodic RCS update
 *
 * Revision 1.4  1997/01/23 03:28:28  tveldhui
 * Periodic RCS update
 *
 * Revision 1.3  1997/01/13 22:19:58  tveldhui
 * Periodic RCS update
 *
 * Revision 1.2  1996/11/11 17:29:13  tveldhui
 * Periodic RCS update
 *
 * Revision 1.1  1996/04/14  21:13:00  todd
 * Initial revision
 *
 */

#ifndef BZ_BLITZ_H
#define BZ_BLITZ_H

/*
 * These symbols allow use of the IEEE and System V math libraries
 * (libm.a and libmsaa.a) on some platforms.
 */

#ifndef BZ_DISABLE_XOPEN_SOURCE
 #ifndef _ALL_SOURCE
  #define _ALL_SOURCE
 #endif
 #ifndef _XOPEN_SOURCE
  #define _XOPEN_SOURCE
 #endif
 #ifndef _XOPEN_SOURCE_EXTENDED
  #define _XOPEN_SOURCE_EXTENDED 1
 #endif
#endif

#include <blitz/compiler.h>          // Compiler-specific directives
#include <blitz/tuning.h>            // Performance tuning
#include <blitz/tau.h>               // Profiling

#include <string>
#include <stdio.h>                   // sprintf, etc.

#ifdef BZ_HAVE_STD
  #include <iostream>
  #include <iomanip>
#else
  #include <iostream.h>
  #include <iomanip.h>
#endif

#ifdef BZ_MATH_FN_IN_NAMESPACE_STD 
  #include <cmath>
#endif

#include <math.h>

#ifdef BZ_HAVE_COMPLEX
  #include <complex>
#endif

#define BZ_THROW                     // Needed in <blitz/numinquire.h>

BZ_NAMESPACE(blitz)

#ifdef BZ_HAVE_STD
 BZ_USING_NAMESPACE(std)
#endif

#ifdef BZ_GENERATE_GLOBAL_INSTANCES
 #define _bz_global
 #define BZ_GLOBAL_INIT(X)   =X
#else
 #define _bz_global extern
 #define BZ_GLOBAL_INIT(X) 
#endif

BZ_NAMESPACE_END

#include <blitz/bzdebug.h>           // Debugging macros

#endif // BZ_BLITZ_H
