#!/usr/bin/perl -w

#cat targetCoeff.out-8-n0.001000-s0.000050 | perl -e '$max=0.0; while(<>) { @row = split; $max=($row[1]>$max)?$row[1]:$max;print $row[1],"\n"; print "max is ",$max,"\n";}'

$max=0.0; 
$maxtime=0.0;

while(<>) { 
    @row = split; 
    $max= ($row[2]>$max)? $row[2]: $max;
#    print $row[2],"\n"; 
#    print "max is ",$max,"\n";
}

#print "max is ",$max,"\n";
print " ",$max,"\n";

