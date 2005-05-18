#ifndef _MYVALARRAY_H_
#define _MYVALARRAY_H_

#include <valarray>

using std::valarray;

namespace std {
inline double 
std::operator*( const valarray<double>& a, const valarray<double>& b ) {

    if ( a.size() != b.size() ) throw;

    double sum = 0.0;
    for ( unsigned int i = 0; i < a.size(); i++ ) {
        sum += a[i]*b[i];
    }

    return sum;
}
}

#include <complex>

namespace std {
inline complex<double> 
std::operator*( const valarray<complex<double> >& a, 
                const valarray<complex<double> >& b ) {

    if ( a.size() != b.size() ) throw;

    complex<double> sum = 0.0;
    for ( unsigned int i = 0; i < a.size(); i++ ) {
        sum += a[i]*b[i];
    }

    return sum;
}
}


#endif // _MYVALARRAY_H_

