// Logger.h

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>

enum LogLevel { ERROR, INFO, DEBUG };

class Logger {
  public:
    static Logger* getInstance();
    std::ostream& getStream();
    void log(const LogLevel level, const std::string& message);
    void log(const std::string& message);

  protected:
    Logger(): stream(std::cout) {};

  private:
    static Logger* theLogger;
    std::ostream& stream;

};


#endif // _LOGGER_H_
