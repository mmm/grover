#define _POSIX_SOURCE 1
// myvalarraydouble.C

#include <cmath>
#include "myvalarraydouble.h"

///////////////
// lifecycle //
///////////////
valarray_double::valarray_double(const double& val, size_t n) {

    _data = new vector<double>(n,val);

}

valarray_double::valarray_double(const valarray_double& val) {

    _data = new vector<double>( *(val._data) );

}

valarray_double& valarray_double::operator=(const valarray_double& val) { 

    if ( this != &val ) {
        delete[] _data;
        _data = new vector<double>( *(val._data) );
    }
    return *this;

}

valarray_double::~valarray_double() { 

    delete _data; 

}


double& valarray_double::operator[](const size_t n) {

    //return _data->at(n);
    vector<double>& rd = *_data;
    return rd[n];

}

const double& valarray_double::operator[](const size_t n) const {

    //return _data->at(n);
    vector<double>& rd = *_data;
    return rd[n];

}


valarray_double& valarray_double::operator+=(const valarray_double& v) { 

    if ( v.size() != _data->size() ) throw;

    vector<double>::iterator dest = _data->begin();
    vector<double>::const_iterator src = v._data->begin();
    while( dest != _data->end() && src != v._data->end() ) {
        *dest += *src ;
        ++dest;
        ++src;
    }

    return *this;
}

valarray_double& valarray_double::operator+=(const double& d) { 

    vector<double>::iterator i = _data->begin();
    while( i != _data->end() ) {
        *i += d;
        ++i;
    }

    return *this;
}

valarray_double& valarray_double::operator-=(const valarray_double& v) { 

    if ( v.size() != _data->size() ) throw;

    vector<double>::iterator dest = _data->begin();
    vector<double>::const_iterator src = v._data->begin();
    while( dest != _data->end() && src != v._data->end() ) {
        *dest -= *src ;
        ++dest;
        ++src;
    }

    return *this;
}

valarray_double& valarray_double::operator-=(const double& d) { 

    vector<double>::iterator i = _data->begin();
    while( i != _data->end() ) {
        *i -= d;
        ++i;
    }

    return *this;
}

valarray_double& valarray_double::operator*=(const double& d) { 

    vector<double>::iterator i = _data->begin();
    while( i != _data->end() ) {
        *i *= d;
        ++i;
    }

    return *this;
}

valarray_double& valarray_double::operator/=(const double& d) { 

    //if ( abs(d) < numerical_limits<double>::epsilon ) throw;
    if ( fabs(d) <=  0.0 ) throw;

    vector<double>::iterator i = _data->begin();
    while( i != _data->end() ) {
        *i /= d;
        ++i;
    }

    return *this;
}


///////////////////
// outside things
///////////////////

valarray_double std::operator+( const valarray_double& a, const valarray_double& b ) {
    valarray_double r = a;
    return r += b;
}

valarray_double std::operator+( const double& d, const valarray_double& v ) {
    valarray_double r = v;
    return r += d;
}

valarray_double std::operator*( const double& d, const valarray_double& v ) {
    valarray_double r = v;
    return r *= d;
}

valarray_double std::operator/( const valarray_double& v, const double& d ) {
    valarray_double r = v;
    return r /= d;
}


double std::operator*( const valarray_double& a, const valarray_double& b ) {

    if ( a.size() != b.size() ) throw;

    vector<double>::const_iterator ci_a = a._data->begin();
    vector<double>::const_iterator ci_b = b._data->begin();
    double sum = 0.0;
    while( ci_a != a._data->end() && ci_b != b._data->end() ) {
        sum += (*ci_a) * (*ci_b) ;
        ++ci_a;
        ++ci_b;
    }

    return sum;

}
