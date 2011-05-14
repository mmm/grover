
# General

Active files are in `diffs` and `common` directories... the rest are just various tests of the framework.

    TODO: make it clear from the code what's real and what're tests

# Building

You need `gnu make` and `g++`.  There are required packages like `lapack` and `build-essentials`, as well as frozen libraries (mostly template libs) in the code... `blitz++` and `TNT`.

Just run `make` from the toplevel.

    TODO:
    - dependencies
    - autoconf stuff?


# Using

To run the grover stepper, start in the main `diffs` directory,

    cd diffs

adjust parameters for the runs you want to make

    vi runner.pl

and run

    ./runner.pl

Data's just dumped out to files in `diffs/output` for basic analysis and gnuplots.


## Run-Parameters

easiest is just to 

    cd diffs
    ./stepper -?

and you get

    DEBUG: Usage: stepper [options]
    Where options are:
    -d prob-output-datafile 
    -n num-steps
    -o bures-distances-output-datafile
    -q num-qubits
    -s step-size
    -u noise-threshold

