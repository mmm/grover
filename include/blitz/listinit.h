/***************************************************************************
 * blitz/listinit.h      Classes for initialization lists
 *
 * $Id: listinit.h,v 1.1 2001-06-12 23:51:10 mmm Exp $
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
 * $Log: listinit.h,v $
 * Revision 1.1  2001-06-12 23:51:10  mmm
 * *** empty log message ***
 *
 * Revision 1.2  1998/03/14 00:04:47  tveldhui
 * 0.2-alpha-05
 *
 * Revision 1.1  1997/07/16 14:51:20  tveldhui
 * Update: Alpha release 0.2 (Arrays)
 *
 */

/*
 * Initialization lists provide a convenient way to set the elements
 * of an array.  For example,
 *
 * Array<int,2> A(3,3);
 * A = 1, 0, 0,
 *     0, 1, 0,
 *     0, 0, 1;
 */

#ifndef BZ_LISTINIT_H
#define BZ_LISTINIT_H

BZ_NAMESPACE(blitz)

template<class T_numtype, class T_iterator>
class ListInitializer {

public:
    ListInitializer(T_iterator iter)
        : iter_(iter)
    {
    }

    ListInitializer<T_numtype, T_iterator> operator,(T_numtype x)
    {
        *iter_ = x;
        return ListInitializer<T_numtype, T_iterator>(iter_ + 1);
    }

private:
    ListInitializer();

protected:
    T_iterator iter_;
};

template<class T_array, class T_iterator = _bz_typename T_array::T_numtype*>
class ListInitializationSwitch {

public:
    typedef _bz_typename T_array::T_numtype T_numtype;

    ListInitializationSwitch(const ListInitializationSwitch<T_array>& lis)
        : array_(lis.array_), value_(lis.value_), 
          wipeOnDestruct_(_bz_true)
    {
        lis.disable();
    }

    ListInitializationSwitch(T_array& array, T_numtype value)
        : array_(array), value_(value), wipeOnDestruct_(_bz_true)
    { }

    ~ListInitializationSwitch()
    {
        if (wipeOnDestruct_)
            array_.initialize(value_);
    }

    ListInitializer<T_numtype, T_iterator> operator,(T_numtype x)
    {
        wipeOnDestruct_ = _bz_false;
        T_iterator iter = array_.getInitializationIterator();
        *iter = value_;
        T_iterator iter2 = iter + 1;
        *iter2 = x;
        return ListInitializer<T_numtype, T_iterator>(iter2 + 1);
    }

    void disable() const
    {
        wipeOnDestruct_ = _bz_false;
    }

private:
    ListInitializationSwitch();

protected:
    T_array& array_;
    T_numtype value_;
    mutable _bz_bool wipeOnDestruct_;
};

BZ_NAMESPACE_END

#endif // BZ_LISTINIT_H

