// Vector.h

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <valarray>

class Vector: public valarray<double> {
  public:
    //valarray_double();
    explicit Vector(const double& val, size_t n): valarray<double>(val,n) {};
    //valarray_double(const valarray_double& val);
    //~valarray_double();
    //valarray_double& operator=(const valarray_double& v);

    // make up and inner product...
    friend double std::operator*( const Vector& a, const Vector& b );

};

#endif //_VECTOR_H_
