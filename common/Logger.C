// Logger.C

#include <iostream>
#include "Logger.h"

namespace SimTools {
    
    Logger* Logger::theLogger = 0;
    
    Logger* Logger::getInstance() {
        if ( ! theLogger ) {
            theLogger = new Logger();
        }
        return theLogger;
    }
    
    std::ostream& Logger::getStream() const {
        return stream;
    }
    
    void Logger::log(const LogLevel level, const std::string& message) const {
        getStream() << getLevelName(level) << ": " << message << std::endl;
    }
    
    void Logger::log(const std::string& message) const {
        log( DEBUG, message );
    }
    
    const std::string Logger::getLevelName(const LogLevel level) const {
        switch (level) {
            case ERROR:
                return "ERROR";
            case INFO:
                return "INFO";
            default:
                return "DEBUG";
        }
    }
    
}
