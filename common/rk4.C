// rk4.C
#include <valarray>

#include "derivs.h"
#include "rk4.h"


extern valarray<double> 
stepRk4( const double x, const valarray<double>& y, const double stepSize ) {
    
    valarray<double> k1 = stepSize * dydx( x, y );

    //valarray<double> tmp;
    //tmp = y + k1/2.0;
    //valarray<double> k2 = stepSize * dydx( x + stepSize/2.0, tmp );
    valarray<double> k2 = stepSize * dydx( x + stepSize/2.0, y + k1/2.0 );

    //tmp = y + k2/2.0;
    //valarray<double> k3 = stepSize * dydx( x + stepSize/2.0, tmp );
    valarray<double> k3 = stepSize * dydx( x + stepSize/2.0, y + k2/2.0 );

    //tmp = y + k3;
    //valarray<double> k4 = stepSize * dydx( x + stepSize, tmp );
    valarray<double> k4 = stepSize * dydx( x + stepSize, y + k3 );

    return k1/6.0 + k2/3.0 + k3/3.0 + k4/6.0;

}
