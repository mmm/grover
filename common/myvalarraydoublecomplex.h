// myvalarray.h

#ifndef _MYVALARRAYDOUBLECOMPLEX_H_
#define _MYVALARRAYDOUBLECOMPLEX_H_

#include <vector>
#include <complex>

class valarray_double_complex {
  public:
    valarray_double_complex();
    explicit valarray_double_complex(const double_complex& val, size_t n);
    valarray_double_complex(const valarray_double_complex& val);
    ~valarray_double_complex();
    valarray_double_complex& operator=(const valarray_double_complex& v);

    double_complex& operator[](const size_t n);
    const double_complex& operator[](const size_t n) const;

    const size_t size() const { return _data->size(); };

    valarray_double_complex& operator+=(const valarray_double_complex& v);
    valarray_double_complex& operator+=(const double_complex& d);
    //valarray_double_complex& operator+=(const double_complex d);

    valarray_double_complex& operator*=(const double_complex& d);

    valarray_double_complex& operator/=(const double_complex& d);

    // make up and inner product...
    friend double_complex std::operator*( const valarray_double_complex& a, const valarray_double_complex& b );

  private:
    vector<double_complex>* _data;
};

//operator+(valarray,valarray);
valarray_double_complex std::operator+( const valarray_double_complex& a, const valarray_double_complex& b );
//operator+(double_complex,valarray);
valarray_double_complex std::operator+( const double_complex& d, const valarray_double_complex& v );
//operator*(double_complex,valarray);
valarray_double_complex std::operator*( const double_complex& d, const valarray_double_complex& v );
//operator/(valarray,double_complex);
valarray_double_complex std::operator/( const valarray_double_complex& v, const double_complex& d );

#endif //_MYVALARRAYDOUBLECOMPLEX_H_
