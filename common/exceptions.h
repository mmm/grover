// exceptions.h

#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <exception>

class Fpe: public exception {
  public:
    Fpe(int index): _index(index) {};

    // overrides exception::what()
    const char* what(void) const;

  private:
    int _index;
};


#endif // _EXCEPTIONS_H_
