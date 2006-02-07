// FileStreamDataLogger.h

#ifndef _FILESTREAMDATALOGGER_H_
#define _FILESTREAMDATALOGGER_H_

#include <string>
#include <fstream>

namespace SimTools {

    class FileStreamDataLogger {
      public:
        FileStreamDataLogger(const std::string& fileName);
        virtual ~FileStreamDataLogger();
        std::ofstream& getDataStream() const;
    
      private:
        std::ofstream* dataStream;
    };

} 

#endif // _FILESTREAMDATALOGGER_H_
