/***************************************************************************
 * blitz/mstruct.h      Matrix structure classes
 *
 * $Id: mstruct.h,v 1.1 2001-06-12 23:51:11 mmm Exp $
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
 *
 * Suggestions:          blitz-suggest@cybervision.com
 * Bugs:                 blitz-bugs@cybervision.com
 *
 * For more information, please see the Blitz++ Home Page:
 *    http://seurat.uwaterloo.ca/blitz/
 *
 ***************************************************************************
 * $Log: mstruct.h,v $
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
 * Revision 1.2  1997/01/13 22:19:58  tveldhui
 * Periodic RCS update
 *
 *
 */

#ifndef BZ_MSTRUCT_H
#define BZ_MSTRUCT_H

#ifndef BZ_BLITZ_H
 #include <blitz/blitz.h>
#endif

#ifndef BZ_ZERO_H
 #include <blitz/zero.h>
#endif

/*
 * Each matrix structure class encapsulates a storage format for matrix
 * data.  It is responsible for:
 * - Storing the size of the matrix
 * - Calculating how many unique elements the matrix will have
 * - Mapping indices (i,j) onto memory locations
 * - Performing any sign reversals or conjugations when matrix
 *   elements are retrieved (e.g. in a Hermitian or Skew symmetric
 *   matrix)
 *
 * Every matrix structure class must provide these methods:
 *
 * ctor()
 * ctor(unsigned rows, unsigned cols)
 * unsigned columns() const;
 * unsigned cols()    const;
 * unsigned firstInRow() const;
 * unsigned firstInCol() const;
 * template<class T> T& get(T* data, unsigned i, unsigned j);
 * template<class T> T  get(const T* data, unsigned i, unsigned j) const;
 * bool inRange(unsigned i, unsigned j) const
 * unsigned lastInRow() const;
 * unsigned lastInCol() const;
 * unsigned numElements() const;
 * void resize(unsigned rows, unsigned cols);
 * unsigned rows()    const;
 *
 * Each matrix structure class must declare a public type
 * T_iterator which is an iterator to scan through the unique
 * entries of the matrix.  The iterator class must provide
 * these methods:
 *
 * ctor(unsigned rows, unsigned cols)
 * unsigned offset() const
 * operator bool() const
 * unsigned row() const
 * unsigned col() const
 */

BZ_NAMESPACE(blitz)

class MatrixStructure { };

class AsymmetricMatrix : public MatrixStructure {
public:
    AsymmetricMatrix()
        : rows_(0), cols_(0)
    { }

    AsymmetricMatrix(unsigned rows, unsigned cols)
        : rows_(rows), cols_(cols)
    { }

    unsigned columns() const
    { return cols_; }

    unsigned cols() const
    { return cols_; }

    _bz_bool inRange(unsigned i, unsigned j) const
    {
        return (i < rows_) && (j < cols_);
    }

    void resize(unsigned rows, unsigned cols)
    {
        rows_ = rows;
        cols_ = cols;
    }

    unsigned rows() const
    { return rows_; }

protected:
    unsigned rows_, cols_;
};

// Still to be implemented:
// SkewSymmetric
// Hermitian
// Tridiagonal
// Banded<L,H>
// Upper bidiagonal
// Lower bidiagonal
// Upper Hessenberg
// Lower Hessenberg

BZ_NAMESPACE_END

#include <blitz/matgen.h>         // RowMajor and ColumnMajor general matrices
#include <blitz/matsymm.h>        // Symmetric
#include <blitz/matdiag.h>        // Diagonal
#include <blitz/mattoep.h>        // Toeplitz
#include <blitz/matltri.h>        // Lower triangular
#include <blitz/matutri.h>        // Upper triangular

#endif // BZ_MSTRUCT_H