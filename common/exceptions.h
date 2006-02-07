// exceptions.h

#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <exception>

namespace SimTools {

    class Fpe: public std::exception {
      public:
        Fpe(const char* message): _message(message) {};
    
        // overrides exception::what()
        //const char* what(void) const;
    
      private:
        const char* _message;
    };

} 

#endif // _EXCEPTIONS_H_
