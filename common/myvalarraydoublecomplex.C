#define _POSIX_SOURCE 1
// myvalarraydoublecomplex.C

#include "myvalarraydoublecomplex.h"

///////////////
// lifecycle //
///////////////
valarray_double_complex::valarray_double_complex(const double_complex& val, size_t n) {

    _data = new vector<double_complex>(n,val);

}

valarray_double_complex::valarray_double_complex(const valarray_double_complex& val) {

    _data = new vector<double_complex>( *(val._data) );

}

valarray_double_complex& valarray_double_complex::operator=(const valarray_double_complex& val) { 

    if ( this != &val ) {
        delete[] _data;
        _data = new vector<double_complex>( *(val._data) );
    }
    return *this;

}

valarray_double_complex::~valarray_double_complex() { 

    delete _data; 

}


double_complex& valarray_double_complex::operator[](const size_t n) {

    //return _data->at(n);
    vector<double_complex>& rd = *_data;
    return rd[n];

}

const double_complex& valarray_double_complex::operator[](const size_t n) const {

    //return _data->at(n);
    vector<double_complex>& rd = *_data;
    return rd[n];

}


valarray_double_complex& valarray_double_complex::operator+=(const valarray_double_complex& v) { 

    if ( v.size() != _data->size() ) throw;

    vector<double_complex>::iterator dest = _data->begin();
    vector<double_complex>::const_iterator src = v._data->begin();
    while( dest != _data->end() && src != v._data->end() ) {
        *dest += *src ;
        ++dest;
        ++src;
    }

    return *this;
}

valarray_double_complex& valarray_double_complex::operator+=(const double_complex& d) { 

    typename vector<double_complex>::iterator i = _data->begin();
    while( i != _data->end() ) {
        *i += d;
        ++i;
    }

    return *this;
}

valarray_double_complex& valarray_double_complex::operator*=(const double_complex& d) { 

    typename vector<double_complex>::iterator i = _data->begin();
    while( i != _data->end() ) {
        *i *= d;
        ++i;
    }

    return *this;
}

valarray_double_complex& valarray_double_complex::operator/=(const double_complex& d) { 

    //if ( abs(d) < numerical_limits<double_complex>::epsilon ) throw;
    if ( abs(d) <=  0.0 ) throw;

    typename vector<double_complex>::iterator i = _data->begin();
    while( i != _data->end() ) {
        *i /= d;
        ++i;
    }

    return *this;
}


///////////////////
// outside things
///////////////////

valarray_double_complex std::operator+( const valarray_double_complex& a, const valarray_double_complex& b ) {
    valarray_double_complex r = a;
    return r += b;
}

valarray_double_complex std::operator+( const double_complex& d, const valarray_double_complex& v ) {
    valarray_double_complex r = v;
    return r += d;
}

valarray_double_complex std::operator*( const double_complex& d, const valarray_double_complex& v ) {
    valarray_double_complex r = v;
    return r *= d;
}

valarray_double_complex std::operator/( const valarray_double_complex& v, const double_complex& d ) {
    valarray_double_complex r = v;
    return r /= d;
}


double_complex std::operator*( const valarray_double_complex& a, const valarray_double_complex& b ) {

    if ( a.size() != b.size() ) throw;

    vector<double_complex>::const_iterator ci_a = a._data->begin();
    vector<double_complex>::const_iterator ci_b = b._data->begin();
    double_complex sum = 0.0;
    while( ci_a != a._data->end() && ci_b != b._data->end() ) {
        sum += (*ci_a) * (*ci_b) ;
        ++ci_a;
        ++ci_b;
    }

    return sum;

}
