#define _POSIX_SOURCE 1
// myvalarray.C

#include "myvalarray.h"

///////////////
// lifecycle //
///////////////
//template<class T> valarray<T>::valarray(const T& val, size_t n): std::vector<T> (n,val,0) { }
template<class T> valarray<T>::valarray(const T& val, size_t n) {

    _data = new vector<T>(n,val,0);

}

template<class T> valarray<T>::valarray(const valarray<T>& val) {

}

template<class T> valarray<T>& valarray<T>::operator=(const valarray<T>& val) { 

}

template<class T> valarray<T>::~valarray() { 

    delete[] _data; 

}


template<class T> T& valarray<T>::operator[](const unsigned int n) { }

template<class T> const T& valarray<T>::operator[](const unsigned int n) const { }


template<class T> valarray<T>& valarray<T>::operator+=(const valarray<T>& v) { 
    //check if d.size() == this->size()?
    if ( v.size() != _data->size() ) throw;

    typename vector<T>::const_iterator ci = _data->begin();
    while( ci != _data->end() ) {
        *ci += v;
        ++ci;
    }

    return *this;
}

template<class T> valarray<T>& valarray<T>::operator+=(const T& d) { 
//template<class T> valarray<T>& valarray<T>::operator+=(const double d) { 

    typename vector<T>::const_iterator ci = _data->begin();
    while( ci != _data->end() ) {
        *ci += d;
        ++ci;
    }

    return *this;
}

template<class T> valarray<T>& valarray<T>::operator*=(const T& d) { 

    typename vector<T>::const_iterator ci = _data->begin();
    while( ci != _data->end() ) {
        *ci *= d;
        ++ci;
    }

    return *this;
}

template<class T> valarray<T>& valarray<T>::operator/=(const T& d) { 

    //if ( abs(d) < numerical_limits<double>::epsilon ) throw;
    if ( abs(d) <=  0.0 ) throw;

    typename vector<T>::const_iterator ci = _data->begin();
    while( ci != _data->end() ) {
        *ci /= d;
        ++ci;
    }

    return *this;
}


///////////////////
// outside things
///////////////////

template<class T> 
valarray<T> std::operator+( const valarray<T>& a, const valarray<T>& b ) {
    valarray<T> r = a;
    return r += b;
}

template<class T> 
valarray<T> std::operator+( const T& d, const valarray<T>& v ) {
    valarray<T> r = v;
    return r += d;
}

template<class T> 
valarray<T> std::operator*( const T& d, const valarray<T>& v ) {
    valarray<T> r = v;
    return r *= d;
}

template<class T> 
valarray<T> std::operator/( const valarray<T>& v, const T& d ) {
    valarray<T> r = v;
    return r /= d;
}
