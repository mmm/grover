#define _POSIX_SOURCE 1
// myvalarray.C

#include "myvalarray.h"

///////////////////
// outside things
///////////////////

double std::operator*( const valarray<double>& a, const valarray<double>& b ) {

    if ( a.size() != b.size() ) throw;

    double sum = 0.0;
    for ( unsigned int i = 0; i < a.size(); i++ ) {
        sum += a[i]*b[i];
    }

    return sum;

}

//double std::operator*( const valarray<complex<double> >& a, const valarray<complex<double> >& b ) {
//
//    if ( a.size() != b.size() ) throw;
//
//    double sum = 0.0;
//    for ( unsigned int i = 0; i < a.size(); i++ ) {
//        sum += a[i]*b[i];
//    }
//
//    return sum;
//
//}


//double std::operator*( const valarray_double& a, const valarray_double& b ) {
//
//    if ( a.size() != b.size() ) throw;
//
//    vector<double>::const_iterator ci_a = a._data->begin();
//    vector<double>::const_iterator ci_b = b._data->begin();
//    double sum = 0.0;
//    while( ci_a != a._data->end() && ci_b != b._data->end() ) {
//        sum += (*ci_a) * (*ci_b) ;
//        ++ci_a;
//        ++ci_b;
//    }
//
//    return sum;
//
//}
