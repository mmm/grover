// Logger.h

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>

enum LogLevel { ERROR, INFO, DEBUG };

class Logger {
  public:
    static Logger* getInstance() {
        if ( ! theLogger ) {
            theLogger = new Logger();
        }
        return theLogger;
    }

  protected:
    Logger() {};

  private:
    static Logger* theLogger;

};


#endif // _LOGGER_H_
