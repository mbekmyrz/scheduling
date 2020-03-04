#include "slots.h"
#include <stdio.h>
#include <string>

slots::slots() {
    position = 0;
    day = " ";
    hour = 0;
    busy = false;  //initialize all slots as free/not busy
}


