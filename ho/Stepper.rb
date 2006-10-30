#!/usr/bin/ruby

require 'matrix'
require 'mathn'
require 'rk4'

if ARGV.size != 2
  STDERR.puts "#{$0}: Incorrect Arguments"
  STDERR.puts "Try #{$0} <num-steps> <step-size>."
  exit 1
end

numSteps = ARGV.shift.to_i
stepSize = ARGV.shift.to_f

x = 0.0
y = Vector[ 0.0, 0.0 ]

for i in 1..numSteps do

  y += stepRk4( x, y, stepSize )
  x += stepSize
  
#  showProgress( i, numSteps )
  puts "i = " + i.to_s
  puts "x = " + x.to_s
  print "y = "
  p y

end

