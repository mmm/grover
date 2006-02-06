// Logger.h

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <iostream>

class Logger {
  public:
    Logger(): stream(std::cout) {};
    std::ostream& getStream();

  private:
    std::ostream& stream;

};


#endif // _LOGGER_H_
