/***************************************************************************
 * blitz/benchext.h      BenchmarkExt classes (Benchmarks with external
 *                       control)
 *
 * Copyright (C) 1997,1998 Todd Veldhuizen <tveldhui@seurat.uwaterloo.ca>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Suggestions:          blitz-suggest@cybervision.com
 * Bugs:                 blitz-bugs@cybervision.com
 *
 * For more information, please see the Blitz++ Home Page:
 *    http://seurat.uwaterloo.ca/blitz/
 *
 ***************************************************************************
 * $Log: benchext.h,v $
 * Revision 1.1  2001-06-12 23:51:10  mmm
 * *** empty log message ***
 *
 * Revision 1.2  1998/03/14 00:04:47  tveldhui
 * 0.2-alpha-05
 *
 * Revision 1.1  1997/07/16 14:51:20  tveldhui
 * Update: Alpha release 0.2 (Arrays)
 *
 */

#ifndef BZ_BENCHEXT_H
#define BZ_BENCHEXT_H

#ifndef BZ_MATRIX_H
 #include <blitz/matrix.h>
#endif

#ifndef BZ_TIMER_H
 #include <blitz/timer.h>
#endif

#include <math.h>

// NEEDS_WORK: replace use of const char* with <string>, once standard
// library is widely supported.

BZ_NAMESPACE(blitz)

// Declaration of class BenchmarkExt<T>
// The template parameter T is the parameter type which is varied in
// the benchmark.  Typically T will be an unsigned, and will represent
// the length of a vector, size of an array, etc.

template<class P_parameter = unsigned>
class BenchmarkExt {

public:
    typedef P_parameter T_parameter;

    BenchmarkExt(const char* description, int numImplementations);

    ~BenchmarkExt();

    void setNumParameters(int numParameters);
    void setParameterVector(Vector<T_parameter> parms);
    void setParameterDescription(const char* string);
    void setIterations(Vector<long> iters);
    void setFlopsPerIteration(Vector<double> flopsPerIteration);
    void setRateDescription(const char* string);

    void beginBenchmarking();

    void beginImplementation(const char* description);

    _bz_bool doneImplementationBenchmark() const;

    T_parameter getParameter() const;
    long        getIterations() const;

    inline void start();
    inline void stop();

    void startOverhead();
    void stopOverhead();

    void endImplementation();

    void endBenchmarking();
 
    double getMflops(unsigned implementation, unsigned parameterNum) const;

    void saveMatlabGraph(const char* filename) const;

protected:
    BenchmarkExt(const BenchmarkExt<P_parameter>&) { }
    void operator=(const BenchmarkExt<P_parameter>&) { }

    enum { initializing, benchmarking, benchmarkingImplementation, 
       running, runningOverhead, done } state_;

    unsigned numImplementations_;
    unsigned implementationNumber_;

    const char* description_;
    Vector<const char*> implementationDescriptions_;

    Matrix<double,RowMajor> times_;       // Elapsed time

    Vector<T_parameter> parameters_;
    Vector<long> iterations_;
    Vector<double> flopsPerIteration_;

    Timer timer_;
    Timer overheadTimer_;

    const char* parameterDescription_;
    const char* rateDescription_;

    int numParameters_;
    int parameterNumber_;
};

BZ_NAMESPACE_END

#include <blitz/benchext.cc>  

#endif // BZ_BENCHEXT_H
