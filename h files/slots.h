#ifndef slots_h
#define slots_h
#include "rooms.h"
#include <string>

class slots { //slots for all (time and space)
public:
    slots();
    int position;
    std::string day;
    int hour;
    class rooms room;
    bool busy;
};

#endif 
