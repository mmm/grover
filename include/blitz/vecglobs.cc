/*
 * $Id: vecglobs.cc,v 1.1 2001-06-12 23:51:12 mmm Exp $
 *
 * Copyright (C) 1997 Todd Veldhuizen <tveldhui@seurat.uwaterloo.ca>
 * All rights reserved.  Please see <blitz/blitz.h> for terms and
 * conditions of use.
 *
 * $Log: vecglobs.cc,v $
 * Revision 1.1  2001-06-12 23:51:12  mmm
 * *** empty log message ***
 *
 * Revision 1.3  1997/07/16 14:51:20  tveldhui
 * Update: Alpha release 0.2 (Arrays)
 *
 * Revision 1.2  1997/01/24 14:42:00  tveldhui
 * Periodic RCS update
 *
 */

#ifndef BZ_VECGLOBS_CC
#define BZ_VECGLOBS_CC

#ifndef BZ_VECGLOBS_H
 #include <blitz/vecglobs.h>
#endif

#include <blitz/vecaccum.cc>    // accumulate()
#include <blitz/vecdelta.cc>    // delta()
#include <blitz/vecmin.cc>      // min(), minValue(), minIndex()
#include <blitz/vecmax.cc>      // max(), maxValue(), maxIndex()
#include <blitz/vecsum.cc>      // sum(), mean()
#include <blitz/vecdot.cc>      // dot()
#include <blitz/vecnorm.cc>     // norm()
#include <blitz/vecnorm1.cc>    // norm1()
#include <blitz/vecany.cc>      // any()
#include <blitz/vecall.cc>      // all()
#include <blitz/veccount.cc>    // count()

#endif // BZ_VECGLOBS_CC
