#ifndef init_h
#define init_h
#include "rooms.h"
#include "slots.h"
#include "groups.h"
#include "courses.h"

int countNumber(std::string fileName);
void roomsInput(std::string fileName);
void groupsInput(std::string fileName);
void instructorsInput(std::string fileName);
void coursesInput(std::string fileName);

void slotsInit(int room_total, int slot_total);
void groupSlotsInit(int group_total);
void instructorSlotsInit(int instructor_total);
void courseInstructorInit(int course_total, int instructor_total);
void courseGroupsInit(int course_total, int group_total);

#endif 
