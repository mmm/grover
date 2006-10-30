
require 'derivs'

def stepRk4( x, y, stepSize )
  
#  k1 = Vector[stepSize,stepSize]
  k1 = dydx( x, y ) * stepSize
#  k2 = dydx( x + stepSize/2, y + k1 * 0.5 ) * stepSize 
#  k3 = dydx( x + stepSize/2, y + k2 * 0.5 ) * stepSize 
#  k4 = dydx( x + stepSize, y + k3 ) * stepSize 
#
#  return k1*(1/6) + k2*(1/3) + k3*(1/3) + k4*(1/6) 
  return k1

end
