#ifndef groups_h
#define groups_h
#include "slots.h"
#include <string>

class groups { 
public:
    groups();
    std::string name;
    int size;
    class slots slot[20]; //5 days x 4 hour slots = 20 time slots per week
};

#endif 
