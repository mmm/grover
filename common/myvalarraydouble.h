// myvalarray.h

#ifndef _MYVALARRAYDOUBLE_H_
#define _MYVALARRAYDOUBLE_H_

#include <vector>

class valarray_double {
  public:
    valarray_double();
    explicit valarray_double(const double& val, size_t n);
    valarray_double(const valarray_double& val);
    ~valarray_double();
    valarray_double& operator=(const valarray_double& v);

    double& operator[](const size_t n);
    const double& operator[](const size_t n) const;

    const size_t size() const { return _data->size(); };

    valarray_double& operator+=(const valarray_double& v);
    valarray_double& operator+=(const double& d);
    //valarray_double& operator+=(const double d);

    valarray_double& operator*=(const double& d);

    valarray_double& operator/=(const double& d);

    // make up and inner product...
    friend double std::operator*( const valarray_double& a, const valarray_double& b );

  private:
    vector<double>* _data;
};

//operator+(valarray,valarray);
valarray_double std::operator+( const valarray_double& a, const valarray_double& b );
//operator+(double,valarray);
valarray_double std::operator+( const double& d, const valarray_double& v );
//operator*(double,valarray);
valarray_double std::operator*( const double& d, const valarray_double& v );
//operator/(valarray,double);
valarray_double std::operator/( const valarray_double& v, const double& d );

#endif //_MYVALARRAYDOUBLE_H_
