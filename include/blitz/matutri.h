/***************************************************************************
 * blitz/matutri.h      Declarations for UpperTriangular matrices
 *
 * $Id: matutri.h,v 1.1 2001-06-12 23:51:11 mmm Exp $
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
 * $Log: matutri.h,v $
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
 */

#ifndef BZ_MATUTRI_H
#define BZ_MATUTRI_H

#ifndef BZ_MSTRUCT_H
 #error <blitz/matutri.h> must be included via <blitz/mstruct.h>
#endif

BZ_NAMESPACE(blitz)

// Upper triangular, column major ordering
// [ 0 1 3 6 ]
// [ . 2 4 7 ]
// [ . . 5 8 ]
// [ . . . 9 ]

class UpperTriangularIterator {
public:
    UpperTriangularIterator(unsigned rows, unsigned cols)
    {
        BZPRECONDITION(rows == cols);
        size_ = rows;
        good_ = true;
        offset_ = 0;
        i_ = 0;
        j_ = 0;
    }
   
    operator _bz_bool() const
    { return good_; }

    void operator++()
    {
        BZPRECONDITION(good_);
        ++offset_;
        ++i_;
        if (i_ > j_)
        {
            i_ = 0;
            ++j_;
            if (j_ == size_)
                good_ = false;
        }
    }

    unsigned row() const
    { return i_; }

    unsigned col() const
    { return j_; }

    unsigned offset() const
    { return offset_; }

protected:
    unsigned size_;
    _bz_bool good_;
    unsigned offset_;
    unsigned i_, j_;
};

class UpperTriangular : public MatrixStructure {

public:
    typedef UpperTriangularIterator T_iterator;

    UpperTriangular()
        : size_(0)
    { }

    UpperTriangular(unsigned size)
        : size_(size)
    { }

    UpperTriangular(unsigned rows, unsigned cols)
        : size_(rows)
    {
        BZPRECONDITION(rows == cols);
    }

    unsigned columns() const
    { return size_; }

    unsigned coordToOffset(unsigned i, unsigned j) const
    {
        BZPRECONDITION(inRange(i,j));
        BZPRECONDITION(j >= i);
        return j*(j+1)/2 + i;
    }

    unsigned firstInRow(unsigned i) const
    { return 0; }

    template<class T_numtype>
    T_numtype get(const T_numtype * _bz_restrict data,
        unsigned i, unsigned j) const
    {
        BZPRECONDITION(inRange(i,j));
        if (j >= i)
            return data[coordToOffset(i,j)];
        else
            return ZeroElement<T_numtype>::zero();
    }

    template<class T_numtype>
    T_numtype& get(T_numtype * _bz_restrict data, unsigned i, unsigned j)
    {
        BZPRECONDITION(inRange(i,j));
        if (j >= i)
            return data[coordToOffset(i,j)];
        else
            return ZeroElement<T_numtype>::zero();
    }

    unsigned lastInRow(unsigned i) const
    { return size_ - 1; }

    unsigned firstInCol(unsigned j) const
    { return 0; }

    unsigned lastInCol(unsigned j) const
    { return j; }

    _bz_bool inRange(unsigned i, unsigned j) const
    {
        return (i < size_) && (j < size_);
    }

    unsigned numElements() const
    { return size_ * (size_ + 1) / 2; }

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

#endif // BZ_MATUTRI_H
