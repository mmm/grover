
# Building

You need `gcc` and `g++`... the rest is packages like `lapack` and `build-essentials`.

Just run `make` from the toplevel.

TODO:

- add external dependencies
- put in autoconf stuff eventually


# Using

To run the grover stepper, 

    cd grover/diffs
    vi runner.pl
    ./runner.pl

Data's just dumped out to files in `grover/diffs/output'


## Parameters

TODO: more docs on parameters

easiest is just to 

    cd grover/diffs
    ./stepper -?

and it should tell you more

    DEBUG: Usage: stepper [options]
    Where options are:
    -d prob-output-datafile 
    -n num-steps
    -o bures-distances-output-datafile
    -q num-qubits
    -s step-size
    -u noise-threshold

