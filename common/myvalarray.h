// myvalarray.h

#ifndef _MYVALARRAY_H_
#define _MYVALARRAY_H_

#include <vector>

template<class T>
class valarray {
  public:
    valarray();
    explicit valarray(const T& val, size_t n);
    valarray(const valarray& val);
    ~valarray();
    valarray& operator=(const valarray& v);

    T& operator[](const size_t n);
    const T& operator[](const size_t n) const;

    const size_t size() const { return _data->size(); };

    valarray& operator+=(const valarray& v);
    valarray& operator+=(const T& d);
    //valarray& operator+=(const double d);

    valarray& operator*=(const T& d);

    valarray& operator/=(const T& d);

  private:
    vector<T>* _data;
};


//operator+(valarray,valarray);
template<class T> valarray<T> std::operator+( const valarray<T>& a, const valarray<T>& b );
//operator+(double,valarray);
template<class T> valarray<T> std::operator+( const T& d, const valarray<T>& v );
//operator*(double,valarray);
template<class T> valarray<T> std::operator*( const T& d, const valarray<T>& v );
//operator/(valarray,double);
template<class T> valarray<T> std::operator/( const valarray<T>& v, const T& d );

#endif //_MYVALARRAY_H_
