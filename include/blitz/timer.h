/***************************************************************************
 * blitz/Timer.h        Timer class, for use in benchmarking
 *
 * $Id: timer.h,v 1.1 2001-06-12 23:51:11 mmm Exp $
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
 * $Log: timer.h,v $
 * Revision 1.1  2001-06-12 23:51:11  mmm
 * *** empty log message ***
 *
 * Revision 1.4  1998/03/14 00:04:47  tveldhui
 * 0.2-alpha-05
 *
 * Revision 1.3  1997/07/16 14:51:20  tveldhui
 * Update: Alpha release 0.2 (Arrays)
 *
 * Revision 1.2  1997/01/24 14:42:00  tveldhui
 * Periodic RCS update
 *
 */

// This class is not portable to non System V platforms.
// It will need to be rewritten for Windows, NT, Mac.
// NEEDS_WORK

#ifndef BZ_TIMER_H
#define BZ_TIMER_H

#ifndef BZ_BLITZ_H
 #include <blitz/blitz.h>
#endif

#ifdef BZ_HAVE_RUSAGE
 #include <sys/resource.h>
#else
 #include <time.h>
#endif

BZ_NAMESPACE(blitz)

class Timer {

public:
    Timer() 
    { 
        state_ = uninitialized;
    }

    void start()
    { 
        state_ = running;
        t1_ = systemTime();
    }

    void stop()
    {
        t2_ = systemTime();
        BZPRECONDITION(state_ == running);
        state_ = stopped;
    }

    long double elapsedSeconds()
    {
        BZPRECONDITION(state_ == stopped);
        return t2_ - t1_;
    }

private:
    Timer(Timer&) { }
    void operator=(Timer&) { }

    long double systemTime()
    {
#ifdef BZ_HAVE_RUSAGE
        getrusage(RUSAGE_SELF, &resourceUsage_);
        double seconds = resourceUsage_.ru_utime.tv_sec 
            + resourceUsage_.ru_stime.tv_sec;
        double micros  = resourceUsage_.ru_utime.tv_usec 
            + resourceUsage_.ru_stime.tv_usec;
        return seconds + micros/1.0e6;
#else
        return clock() / (long double) CLOCKS_PER_SEC;
#endif
    }

    enum { uninitialized, running, stopped } state_;

#ifdef BZ_HAVE_RUSAGE
    struct rusage resourceUsage_;
#endif

    long double t1_, t2_;
};

BZ_NAMESPACE_END

#endif // BZ_TIMER_H
