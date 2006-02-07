// Logger.h

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <iostream>
#include <string>

namespace SimTools {
    
    enum LogLevel { ERROR, INFO, DEBUG };
    
    class Logger {
      public:
        static Logger* getInstance();
        std::ostream& getStream() const;
        void log(const LogLevel level, const std::string& message) const;
        void log(const std::string& message) const;
        const std::string getLevelName(const LogLevel level) const;
    
      protected:
        Logger(): stream(std::cout) {};
    
      private:
        static Logger* theLogger;
        std::ostream& stream;
    
    };
    
    inline void log(const std::string& message) {
        Logger* logger = Logger::getInstance();
        logger->log(message);
    }
    
}

#endif // _LOGGER_H_
