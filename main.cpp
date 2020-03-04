#include <iostream>
#include <stdlib.h>
#include <string>
#include "init.h" //input data processing and initialization happens there
#include "schedule.h" //registration happens there
#include "output.h" //output processing happens there

int main() {
    //counts the number of lines in a file -> total number of objects (rooms, groups, instructors, courses)
    int room_total = countNumber("Rooms.txt");
    int slot_total = room_total * 20; //5 days x 4 time slots per day = 20 slots, each day - each room - each hour slot
    int group_total = countNumber("Groups.txt");
    int instructor_total = countNumber("Instructors.txt");
    int course_total = countNumber("Courses.txt");
    
    //input of information from a file
    roomsInput("Rooms.txt"); //reads room name and its capacity
    groupsInput("Groups.txt"); //reads group name and its size
    instructorsInput("Instructors.txt"); //reads instructor name
    coursesInput("Courses.txt"); //reads course name, instructor name and groups' names
    
    //connecting objects with each other
    slotsInit(room_total, slot_total); //initialization of GENERAL time and space(room) slots availabe for all groups
    groupSlotsInit(group_total); //initialization of time slots for EACH group (20 slots per week)
    instructorSlotsInit(instructor_total); //initialization of time slots for EACH instructor (20 slots per week)
    courseInstructorInit(course_total, instructor_total); //initialization of courses and instructors who teach them
    courseGroupsInit(course_total, group_total); //initialization of courses and groups wchich attend them
    
    registration(room_total,slot_total,group_total,instructor_total,course_total); //register time and room for each course
    output(course_total); //print the result in output file
    userTalk(course_total); //takes some user input from console
    return 0;
}
