#define _POSIX_SOURCE 1
// myvalarray.C

#include "myvalarray.h"

///////////////
// lifecycle //
///////////////
//template<class T> valarray<T>::valarray(const T& val, size_t n): std::vector<T> (n,val,0) { }
template<class T> 
valarray<T>::valarray(const T& val, size_t n) {

    _data = new vector<T>(n,val,0);

}

template<class T> 
valarray<T>::valarray(const valarray<T>& val) {

    _data = new vector<T>( *(val._data) );
    
}

template<class T> 
valarray<T>& valarray<T>::operator=(const valarray<T>& val) { 

    if ( this != &val ) {
        delete[] _data;
        _data = new vector<T>( *(val._data) );
    }
    return *this;

}

template<class T> 
valarray<T>::~valarray() { 

    delete[] _data; 

}


template<class T> 
T& valarray<T>::operator[](const unsigned int n) { 

    //return _data->at(n);
    vector<T>& rd = *_data;
    return rd[n];

}

template<class T> 
const T& valarray<T>::operator[](const unsigned int n) const { 

    //return _data->at(n);
    vector<T>& rd = *_data;
    return rd[n];

}


template<class T> 
valarray<T>& valarray<T>::operator+=(const valarray<T>& v) { 

    if ( v.size() != _data->size() ) throw;

    typename vector<T>::iterator dest = _data->begin();
    typename vector<T>::const_iterator src = v._data->begin();
    while( dest != _data->end() && src != v._data->end() ) {
        *dest += *src ;
        ++dest;
        ++src;
    }

    return *this;
}

template<class T> 
valarray<T>& valarray<T>::operator+=(const T& d) { 

    typename vector<T>::iterator i = _data->begin();
    while( i != _data->end() ) {
        *i += d;
        ++i;
    }

    return *this;
}

template<class T> 
valarray<T>& valarray<T>::operator*=(const T& d) { 

    typename vector<T>::iterator i = _data->begin();
    while( i != _data->end() ) {
        *i *= d;
        ++i;
    }

    return *this;
}

template<class T> 
valarray<T>& valarray<T>::operator/=(const T& d) { 

    //if ( abs(d) < numerical_limits<double>::epsilon ) throw;
    if ( fabs(d) <=  0.0 ) throw;

    typename vector<T>::iterator i = _data->begin();
    while( i != _data->end() ) {
        *i /= d;
        ++i;
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
