/***************************************************************************
 * blitz/matdiag.h      Declarations for Diagonal matrices 
 *
 * $Id: matdiag.h,v 1.1 2001-06-12 23:51:11 mmm Exp $
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
 * $Log: matdiag.h,v $
 * Revision 1.1  2001-06-12 23:51:11  mmm
 * *** empty log message ***
 *
 * Revision 1.3  1998/03/14 00:04:47  tveldhui
 * 0.2-alpha-05
 *
 * Revision 1.2  1997/01/24 14:42:00  tveldhui
 * Periodic RCS update
 *
 * Revision 1.1  1997/01/13 22:19:58  tveldhui
 * Periodic RCS update
 *
 *
 */

#ifndef BZ_MATDIAG_H
#define BZ_MATDIAG_H

#ifndef BZ_MSTRUCT_H
 #error <blitz/matdiag.h> must be included via <blitz/mstruct.h>
#endif

BZ_NAMESPACE(blitz)

// Diagonal matrix
// [ 0 . . . ]
// [ . 1 . . ]
// [ . . 2 . ]
// [ . . . 3 ]

class DiagonalIterator {
public:
    DiagonalIterator(unsigned rows, unsigned cols)
    {
        BZPRECONDITION(rows == cols);
        size_ = rows;
        i_ = 0;
    }

    operator _bz_bool() const
    {
        return i_ < size_;
    }

    void operator++()
    {
        ++i_;
    }

    unsigned row() const
    { return i_; }

    unsigned col() const
    { return i_; }

    unsigned offset() const
    { return i_; }

protected:
    unsigned i_, size_;
};

class Diagonal : public MatrixStructure {

public:
    typedef DiagonalIterator T_iterator;

    Diagonal()
        : size_(0)
    { }

    Diagonal(unsigned size)
        : size_(size)
    { }

    Diagonal(unsigned rows, unsigned cols)
        : size_(rows)
    {
        BZPRECONDITION(rows == cols);
    }

    unsigned columns() const
    { return size_; }

    unsigned coordToOffset(unsigned i, unsigned j) const
    {
        BZPRECONDITION(inRange(i,j));
        BZPRECONDITION(i == j);
        return i;
    }

    unsigned firstInRow(unsigned i) const
    { return i; }

    template<class T_numtype>
    T_numtype get(const T_numtype * _bz_restrict data,
        unsigned i, unsigned j) const
    {
        BZPRECONDITION(inRange(i,j));
        if (i == j)
            return data[coordToOffset(i,j)];
        else
            return ZeroElement<T_numtype>::zero();
    }

    template<class T_numtype>
    T_numtype& get(T_numtype * _bz_restrict data, unsigned i, unsigned j)
    {
        BZPRECONDITION(inRange(i,j));
        if (i == j)
            return data[coordToOffset(i,j)];
        else
            return ZeroElement<T_numtype>::zero();
    }

    unsigned lastInRow(unsigned i) const
    { return i; }

    unsigned firstInCol(unsigned j) const
    { return j; }

    unsigned lastInCol(unsigned j) const
    { return j; }

    _bz_bool inRange(unsigned i, unsigned j) const
    {
        return (i < size_) && (j < size_);
    }

    unsigned numElements() const
    { return size_; }

    unsigned rows() const
    { return size_; }

    void resize(unsigned size)
    {
        size_ = size;
    }

    void resize(unsigned rows, unsigned cols)
    {
        BZPRECONDITION(rows == cols);
        size_  = rows;
    }

private:
    unsigned size_;
};

BZ_NAMESPACE_END

#endif // BZ_MATSYMM_H

