// exceptions.C
#include <iostream>

#include "exceptions.h"


const char* Fpe::what(void) const {
    cerr << Fpe::_message << endl;
    return "Oops... in Fpe::what";
}
