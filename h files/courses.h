#ifndef courses_h
#define courses_h
#include "groups.h"
#include "slots.h"
#include <string>

class instructors {
public:
    instructors();
    std::string name;
    class slots slot[20];
};

class courses {
public:
    courses();
    std::string title;
    int type; //1 - Lec, 2 - Tut, 3 - Lab
    int size;
    class instructors prof;
    class groups group[15];
    class slots slot;
};

#endif 
