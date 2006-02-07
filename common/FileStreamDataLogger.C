// FileStreamDataLogger.C

#include "FileStreamDataLogger.h"

namespace SimTools {

    FileStreamDataLogger::FileStreamDataLogger(const std::string& fileName):
        dataStream(new std::ofstream(fileName.c_str())) 
    {
    }

    FileStreamDataLogger::~FileStreamDataLogger() {
        dataStream->close();
    }

    std::ofstream& FileStreamDataLogger::getDataStream() const {
        return *dataStream;
    }

}
