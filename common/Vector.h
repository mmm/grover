//Vector.h

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <valarray>

class Vector: public valarray<double> {
  public:
    Vector(): valarray<double>() {};
    Vector(const valarray<double>& val): valarray<double>(val) {};
    explicit Vector(const double& val, size_t n): valarray<double>(val,n) {};
    Vector(const Vector& val): valarray<double>(val) {};
    //~Vector();
    Vector& operator=(const Vector& v);
    Vector& operator=(const valarray<double>& v);


    // make up an inner product...
    friend double std::operator*( const Vector& a, const Vector& b );
    friend Vector operator*(const Vector& v, const double a);
    friend valarray<double> operator*(const double a, const valarray<double>& v);
    friend Vector operator*(const double a, const Vector& v);
    friend Vector std::operator+( const Vector& a, const Vector& b );
    friend valarray<double> std::operator+( const valarray<double>& a, const valarray<double>& b );

};

#endif //_VECTOR_H_
