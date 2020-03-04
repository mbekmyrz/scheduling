#include "init.h"
#include "schedule.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

extern rooms room[100];
extern slots slot[500];
extern groups group[100];
extern courses course[200];
extern instructors instructor[100];
int slotIndex;

void registration(int room_total,int slot_total,int group_total,int instructor_total,int course_total) {
    srand(static_cast<unsigned int>(time(0)));
    int courseIndex, groupIndex, instructorIndex, courseGrouptotal, freeCourseGroupNumber, freeInstructorSlotIndex = -1, freeGroupSlotIndex = -1;
    bool freeTimeFound;
    sortCoursesBySize(course_total); //sorts the courses with largest size into first place
    
    for (courseIndex = 0; courseIndex < course_total; courseIndex++) { //take one course
        instructorIndex = instructorIndex_find(instructor_total, courseIndex); //find corresponding parentInstructor of this courseInstructor
        freeTimeFound = false;
        while (freeTimeFound == false) { //searching for free time in GeneralSlots, InstrcutorSlots, GroupSlots
            courseGrouptotal = 0; freeCourseGroupNumber = 0;
            if (course[courseIndex].type == 3) {
                slotIndex = nextRandomLab(slot_total, courseIndex);  //search for a free lab froom if course is type of "Lab"
            }
            else slotIndex = nextRandom(slot_total, courseIndex); //searching for a free not lab room and time
            
            freeInstructorSlotIndex = freeInstructorSlot(instructorIndex);
            if (freeInstructorSlotIndex > 0) { //is this time free for instructor
                //check whether each group of this course is free at this time slot
                for (int i = 0; i < 15; i++) {
                    if (course[courseIndex].group[i].name != " ") { //run for each existing group of each course
                        courseGrouptotal++;
                        groupIndex = groupIndex_find(courseIndex, i, group_total); //find corresponding parentGroup of the courseGroup
                        freeGroupSlotIndex = freeGroupSlot(groupIndex);
                        if (freeGroupSlotIndex > 0) {
                            freeCourseGroupNumber++;
                        }
                    }
                    else break;
                }
                
                if (freeCourseGroupNumber == courseGrouptotal) { //if all groups are free at this time
                    freeTimeFound = true;
                }
            }
        }
        slot[slotIndex].busy = true; //make this slot busy for all
        course[courseIndex].slot = slot[slotIndex];
        instructor[instructorIndex].slot[freeInstructorSlotIndex] = slot[slotIndex];
        for (int i = 0; i < 15; i++) {
            if (course[courseIndex].group[i].name != " ") { //run for each existing group of each course
                groupIndex = groupIndex_find(courseIndex, i, group_total); //find corresponding parentGroup of the courseGroup
                group[groupIndex].slot[freeGroupSlotIndex].busy = true; //make parentGroup busy at this chosen slot
            }
            else break;
        }
    }
}

void sortCoursesBySize(int course_total) {
    class courses temp;
    for (int i = 0; i <  course_total; i++) {
        for (int j = 0; j < course_total; j++) {
            if (course[j].size < course[j+1].size) {
                temp = course[j];
                course[j] = course[j+1];
                course[j+1] = temp;
            }
        }
    }
}

int instructorIndex_find(int instructor_total,int courseIndex){
    for (int instructorIndex = 0; instructorIndex < instructor_total; instructorIndex++) { //all groups
        if (course[courseIndex].prof.name == instructor[instructorIndex].name) {
            return instructorIndex;
        }
    }
    return -1;
}

int groupIndex_find(int courseIndex, int i, int group_total) {
    for (int groupIndex = 0; groupIndex < group_total; groupIndex++) { //all groups
            if (course[courseIndex].group[i].name == group[groupIndex].name) {
                return groupIndex;
            }
        }
    return -1;
}

int nextRandom (int slot_total, int courseIndex) {
    slotIndex = rand() % slot_total;
    while(!(slot[slotIndex].room.lab == false && slot[slotIndex].room.capacity >= course[courseIndex].size && slot[slotIndex].busy == false)) {
        slotIndex++;
        if(slotIndex >= slot_total) {
            slotIndex = 0;
        }
    }
    return slotIndex;
}

int nextRandomLab (int slot_total, int courseIndex) {
    slotIndex = rand() % slot_total;
    while(!(slot[slotIndex].room.lab == true && slot[slotIndex].room.capacity >= course[courseIndex].size && slot[slotIndex].busy == false)) {
        slotIndex++;
        if(slotIndex >= slot_total) {
            slotIndex = 0;
        }
    }
    return slotIndex;
}

int freeGroupSlot(int groupIndex) {
    for (int freeSlotIndex = 0; freeSlotIndex < 20; freeSlotIndex++) {
        if (slot[slotIndex].day == group[groupIndex].slot[freeSlotIndex].day
            && slot[slotIndex].hour == group[groupIndex].slot[freeSlotIndex].hour
            && group[groupIndex].slot[freeSlotIndex].busy == false) {
            return freeSlotIndex;
        }
    }
    return -1;
}

int freeInstructorSlot(int instructorIndex) {
    for (int freeSlotIndex = 0; freeSlotIndex < 20; freeSlotIndex++) {
        if (slot[slotIndex].day == instructor[instructorIndex].slot[freeSlotIndex].day
            && slot[slotIndex].hour == instructor[instructorIndex].slot[freeSlotIndex].hour
            && instructor[instructorIndex].slot[freeSlotIndex].busy == false) {
            return freeSlotIndex;
        }
    }
    return -1;
}
