#!/usr/bin/perl -w

use strict;

my @steps = ( { "numSteps" => 1000, "stepSize" => 0.00005 },
              { "numSteps" => 500, "stepSize" => 0.0001 },
              { "numSteps" => 250, "stepSize" => 0.0002 } );

my @noiseBounds = ( 0.001, 0.0025, 0.005, 0.0075, 0.01 );

for my $numQubits (2..7) {
#for my $numQubits (2) {
    print "number of qubits is ",$numQubits,"\n";
    for my $bound (@noiseBounds) {
        print "\tnoise bound is ",$bound,"\n";
        for my $rh (@steps) {
            print "\t\tnumber of steps is ",$rh->{"numSteps"},"\n";
            print "\t\tstep size is ",$rh->{"stepSize"},"\n";
            my $ns = $rh->{"numSteps"};
            my $ss = $rh->{"stepSize"};
            system("./stepper -q$numQubits -u$bound -n$ns -s$ss") == 0
                or die "couldn't run stepper";
            print "";
        }
    }
}
