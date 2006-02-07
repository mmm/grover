// Logger.C

#include <iostream>
#include "Logger.h"

Logger* Logger::theLogger = 0;

Logger* Logger::getInstance() {
    if ( ! theLogger ) {
        theLogger = new Logger();
    }
    return theLogger;
}

std::ostream& Logger::getStream() {
    return stream;
}

void Logger::log(const LogLevel level, const std::string& message) {
    getStream() << level << ": " << message << std::endl;
}

void Logger::log(const std::string& message) {
    log( DEBUG, message );
}


