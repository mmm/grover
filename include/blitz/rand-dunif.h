/***************************************************************************
 * blitz/rand-dunif.h    Discrete uniform generator
 *
 * $Id: rand-dunif.h,v 1.1 2001-06-12 23:51:11 mmm Exp $
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
 * $Log: rand-dunif.h,v $
 * Revision 1.1  2001-06-12 23:51:11  mmm
 * *** empty log message ***
 *
 * Revision 1.2  1998/03/14 00:04:47  tveldhui
 * 0.2-alpha-05
 *
 * Revision 1.1  1997/07/16 14:51:20  tveldhui
 * Update: Alpha release 0.2 (Arrays)
 *
 */

#ifndef BZ_RAND_DUNIF_H
#define BZ_RAND_DUNIF_H

#ifndef BZ_RANDOM_H
 #include <blitz/random.h>
#endif

#ifndef BZ_RAND_UNIFORM_H
 #include <blitz/rand-uniform.h>
#endif

#include <math.h>

BZ_NAMESPACE(blitz)

template<class P_uniform BZ_TEMPLATE_DEFAULT(Uniform)>
class DiscreteUniform {

public:
    typedef int T_numtype;
    typedef P_uniform T_uniform;

    DiscreteUniform(int low, int high, double=0)
        : low_(low), range_(high-low+1)
    { 
    }

    void randomize() 
    { 
        uniform_.randomize();
    }
  
    int random()
    { 
        return int(uniform_.random() * range_ + low_);
    } 

private:
    int low_, range_;
    T_uniform uniform_;
};

BZ_NAMESPACE_END

#endif // BZ_RAND_DUNIF_H

