#include "init.h"
#include "rooms.h"
#include "slots.h"
#include "groups.h"
#include "courses.h"

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

rooms room[100];
slots slot[1000];
groups group[100];
courses course[500];
instructors instructor[100];

std::string day[5] = {"M", "T", "W", "R", "F"};
int hour[4] = {0, 1, 2, 3};

int countNumber (std::string fileName) {
    std::fstream file (fileName);
    int number = 0;
    std::string line;
    if(file.is_open()){
        while (getline(file, line)){
            number++;
        }
        return number;
    }
    return  -1;
}

void roomsInput(std::string fileName) {
    int roomIndex = 0, size = 0;
    std::string name;
    std::fstream file (fileName);
    if(file.is_open() == false) {
        std::cout << "File " << fileName << " can not be opened";
    }
    
    while(file.is_open()) {
        while(!file.eof()) {
            getline(file, name, ',');
            file >> size;
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            room[roomIndex].name = name;
            room[roomIndex].capacity = size;
            if (name[0] == 'L') {
                room[roomIndex].lab = true;
            }
            roomIndex++;
        }
        file.close();
    }
}

void groupsInput(std::string fileName) {
    int groupIndex = 0, size = 0;
    std::string name;
    std::fstream file (fileName);
    if(file.is_open() == false) {
        std::cout << "File " << fileName << " can not be opened";
    }
    
    while(file.is_open()) {
        while(!file.eof()) {
            getline(file, name, ',');
            file >> size;
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            group[groupIndex].name = name;
            group[groupIndex].size = size;
            groupIndex++;
        }
        file.close();
    }
}

void instructorsInput(std::string fileName) {
    int instructorIndex = 0;
    std::string name;
    std::fstream file (fileName);
    if(file.is_open() == false) {
        std::cout << "File " << fileName << " can not be opened";
    }
    
    while(file.is_open()) {
        while(!file.eof()) {
            getline(file, name, ',');
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            instructor[instructorIndex].name = name;
            instructorIndex++;
        }
        file.close();
    }
}

void coursesInput(std::string fileName) {
    int i = 0, courseIndex = 0, groupIndex = 0, courseType = 0;
    std::string line, courseTitle, profName, groupName;
    std::fstream file (fileName);
    if(file.is_open() == false) {
        std::cout << "File " << fileName << " can not be opened";
    }
    
    while(file.is_open()) {
        while(!file.eof()) {
            getline(file, line);
            courseTitle = ""; profName = ""; groupName = "";
            i = 0; groupIndex = 0;
            
            //course title and type
            while (line[i] != ',') {
                courseTitle += line[i];
                i++;
            }
            if (courseTitle[0] == '\n') { //end.
                break;
            }
            switch (courseTitle[2]) {
                case 'c': //Lec
                    courseType = 1;
                    break;
                case 't': //Tut
                    courseType = 2;
                    break;
                case 'b': //Lab
                    courseType = 3;
                    break;
                default:
                    courseType = 0;
                    break;
            }
            course[courseIndex].title = courseTitle;
            course[courseIndex].type = courseType;
            i++;
            
            //prof
            while (line[i] != ',') {
                profName += line[i];
                i++;
            }
            course[courseIndex].prof.name = profName;
            i++;
            
            //groups
            while (line[i] != '\0') {
                groupName = "";
                while (line[i] != ',') {
                    groupName += line[i];
                    i++;
                }
                course[courseIndex].group[groupIndex].name = groupName;
                i++; groupIndex++;
            }
            
            courseIndex++;
        }
        file.close();
    }
}

void slotsInit(int room_total, int slot_total) {
    //time
    for (int i = 0; i < slot_total; i++) {
        slot[i].position = i;
        slot[i].day = day[i % 5];
        slot[i].hour = hour[(i / 5) % 4];
    }
    //rooms
    for (int i = 0; i < room_total; i++) {
        for (int j = i * 20; j < (i + 1) * 20; j++) {
            slot[j].room = room[i];
        }
    }
}

void groupSlotsInit(int group_total) {
    for (int i = 0; i < group_total; i++) {
        for (int j = 0; j < 20; j++) {
            group[i].slot[j].day = day[j % 5];
            group[i].slot[j].hour = hour[(j / 5) % 4];
        }
    }
}

void instructorSlotsInit(int instructor_total) {
    for (int i = 0; i < instructor_total; i++) {
        for (int j = 0; j < 20; j++) {
            instructor[i].slot[j].day = day[j % 5];
            instructor[i].slot[j].hour = hour[(j / 5) % 4];
        }
    }
}

void courseInstructorInit(int course_total, int instructor_total) {
    for (int i = 0; i < course_total; i++) {
        for (int j = 0; j < instructor_total; j++) {
            if (course[i].prof.name == instructor[j].name) {
                course[i].prof = instructor[j];
            }
        }
    }
}

void courseGroupsInit(int course_total, int group_total) {
    for (int i = 0; i < course_total; i++) {
        for (int j = 0; j < 15; j++) {
            for (int k = 0; k < group_total; k++) {
                if (course[i].group[j].name == group[k].name) {
                    course[i].group[j] = group[k];
                    course[i].size += group[k].size;
                }
            }
        }
    }
}
