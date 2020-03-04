#include "init.h"
#include "output.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;
extern courses course[200];

void output (int course_total) {
    string time;
    std::ofstream myfile;
    myfile.open ("output.txt");
    myfile << "\r\n" << setw(110) << "-----------------------------------------------" << "\r\n";
    myfile << "\r\n" << setw(110) << "School of Engineering, Undergraduate, Fall 2017" << "\r\n";
    myfile << "\r\n" << setw(110) << "-----------------------------------------------" << "\r\n";
    for (int k = 0; k < 200; k++) {
        myfile << "=";
    }
    myfile << "\r\n";
    myfile << setw(35) << "Course Title" << //12
    setw(24) << "|" <<
    setw(5) << "Days" << //4
    setw(2) << "|" <<
    setw(11) << "Time" << //4
    setw(8) << "|" <<
    setw(10) << "Capacity" << //8
    setw(3) << "|" <<
    setw(17) << "Faculty" << //7
    setw(12) << "|" <<
    setw(9) << "Room" << //4
    setw(6) << "|" <<
    setw(35) << "Student Groups" << "\r\n";  //14
    for (int k = 0; k < 200; k++) {
        myfile << "=";
    }
    myfile << "\r\n";
    for (int i = 0; i < course_total; i++) {
        switch(course[i].slot.hour) { 
            case 0:
                time = "09:00 - 11:00";
                break;
            case 1:
                time = "11:00 - 13:00";
                break;
            case 2:
                time = "14:00 - 16:00";
                break;
            case 3:
                time = "16:00 - 18:00";
                break;
            default:
                time = "Error";
                break;
        }
        myfile << left << setw(58) << course[i].title << "|" <<
        left << setw(6) << course[i].slot.day << "|" <<
        left << setw(18) << time << "|" <<
        left << setw(12) << course[i].size << "|" <<
        left << setw(28) << course[i].prof.name << "|" <<
        left << setw(14) << course[i].slot.room.name << "|";
        for (int j = 0; j < 15; j++) {
            if (course[i].group[j].name != " ") {
                if (j < 6) {
                    myfile << left << course[i].group[j].name << "  ";
                }
                else if (j == 6 ) {
                    myfile << "\r\n" <<
                    right << setw(59) << "|" <<
                    right << setw(7) <<  "|" <<
                    right << setw(19) << "|" <<
                    right << setw(13) << "|" <<
                    right << setw(29) << "|" <<
                    right << setw(15) << "|" <<
                    left << course[i].group[j].name << "  ";
                }
                else myfile << left << course[i].group[j].name << "  ";
            }
            else break;
        }
        myfile << "\r\n\r\n";
        for (int k = 0; k < 200; k++) {
            myfile << "-";
        }
        myfile << "\r\n\r\n";
    }
    myfile.close();
}

void userTalk(int course_total) {
    string wish, name, surname;
    int choice; bool cont = false;
    cout << "Welcome to the scheduling program ALA++!!!" << endl;
    cout << "*Timetable for all courses was successfully acomplished (see in file called \"output\" in \"txt\" folder)*" << endl;
    cout << "\n\t\tDo you want to see some specific timetables (yes/no): ";
    cin >> wish;
    if ((wish == "yes") || (wish == "Yes") || (wish == "Y")) {
        while (cont == false) {
            cout << "\n\t\t\t-Choose which schedule you want to display:" << endl;
            cout << "\n\t\t\t\t1. For a professor" << endl;
            cout << "\n\t\t\t\t2. For a group" << endl;
            cout << "\n\t\t\t\t3. For a room" << endl;
            cout << "\n\t\t\t-Enter your choice: ";
            cin >> choice;
            
            switch (choice) {
                case 1:
                    cout << "\n\t\t\t\tEnter professor's full name: ";
                    cin >> name >> surname;
                    name = name + " " + surname;
                    display(1, name, course_total);
                    cont = true;
                    break;
                case 2:
                    cout << "\n\t\t\t\tEnter group name: ";
                    cin >> name;
                    display(2, name, course_total);
                    cont = true;
                    break;
                case 3:
                    cout << "\n\t\t\t\tEnter room name: ";
                    cin >> name;
                    display(3, name, course_total);
                    cont = true;
                    break;
                default:
                    cout << "Incorrect input" << endl;
                    cout << "Try again" << endl;
                    break;
            }
        }
        cout << "\n\t\t\t\tFile was successfully created (see in \"UserOutput.txt\")";
    }
    cout << "\n\t\tThank you!" << endl;
}


void display(int type, string name, int course_total) {
    string time;
    std::ofstream myfile;
    myfile.open ("UserOutput.txt");
    myfile << "\r\n" << setw(110) << "--------------------------------" << "\r\n";
    myfile << "\r\n" << setw(95) << "Timetable for " << name << "\r\n";
    myfile << "\r\n" << setw(110) << "--------------------------------" << "\r\n";
    for (int k = 0; k < 200; k++) {
        myfile << "=";
    }
    myfile << "\r\n";
    myfile << setw(35) << "Course Title" << //12
    setw(24) << "|" <<
    setw(5) << "Days" << //4
    setw(2) << "|" <<
    setw(11) << "Time" << //4
    setw(8) << "|" <<
    setw(10) << "Capacity" << //8
    setw(3) << "|" <<
    setw(17) << "Faculty" << //7
    setw(12) << "|" <<
    setw(9) << "Room" << //4
    setw(6) << "|" <<
    setw(35) << "Student Groups" << "\r\n";  //14
    for (int k = 0; k < 200; k++) {
        myfile << "=";
    }
    myfile << "\r\n";
    switch (type) {
        case 1:
            for (int i = 0; i < course_total; i++) {
                if (name == course[i].prof.name ) {
                    switch(course[i].slot.hour) {
                        case 0:
                            time = "09:00 - 11:00";
                            break;
                        case 1:
                            time = "11:00 - 13:00";
                            break;
                        case 2:
                            time = "14:00 - 16:00";
                            break;
                        case 3:
                            time = "16:00 - 18:00";
                            break;
                        default:
                            time = "Error";
                            break;
                    }
                    myfile << left << setw(58) << course[i].title << "|" <<
                    left << setw(6) << course[i].slot.day << "|" <<
                    left << setw(18) << time << "|" <<
                    left << setw(12) << course[i].size << "|" <<
                    left << setw(28) << course[i].prof.name << "|" <<
                    left << setw(14) << course[i].slot.room.name << "|";
                    for (int j = 0; j < 15; j++) {
                        if (course[i].group[j].name != " ") {
                            if (j < 6) {
                                myfile << left << course[i].group[j].name << "  ";
                            }
                            else if (j == 6 ) {
                                myfile << "\r\n" <<
                                right << setw(59) << "|" <<
                                right << setw(7) <<  "|" <<
                                right << setw(19) << "|" <<
                                right << setw(13) << "|" <<
                                right << setw(29) << "|" <<
                                right << setw(15) << "|" <<
                                left << course[i].group[j].name << "  ";
                            }
                            else myfile << left << course[i].group[j].name << "  ";
                        }
                        else break;
                    }
                    myfile << "\r\n\r\n";
                    for (int k = 0; k < 200; k++) {
                        myfile << "-";
                    }
                    myfile << "\r\n\r\n";
                }
            }
            break;
        case 2:
            for (int i = 0; i < course_total; i++) {
                for (int j = 0; j < 15; j ++) {
                    if (name == course[i].group[j].name ) {
                        switch(course[i].slot.hour) {
                            case 0:
                                time = "09:00 - 11:00";
                                break;
                            case 1:
                                time = "11:00 - 13:00";
                                break;
                            case 2:
                                time = "14:00 - 16:00";
                                break;
                            case 3:
                                time = "16:00 - 18:00";
                                break;
                            default:
                                time = "Error";
                                break;
                        }
                        myfile << left << setw(58) << course[i].title << "|" <<
                        left << setw(6) << course[i].slot.day << "|" <<
                        left << setw(18) << time << "|" <<
                        left << setw(12) << course[i].size << "|" <<
                        left << setw(28) << course[i].prof.name << "|" <<
                        left << setw(14) << course[i].slot.room.name << "|";
                        for (int j = 0; j < 15; j++) {
                            if (course[i].group[j].name != " ") {
                                if (j < 6) {
                                    myfile << left << course[i].group[j].name << "  ";
                                }
                                else if (j == 6 ) {
                                    myfile << "\r\n" <<
                                    right << setw(59) << "|" <<
                                    right << setw(7) <<  "|" <<
                                    right << setw(19) << "|" <<
                                    right << setw(13) << "|" <<
                                    right << setw(29) << "|" <<
                                    right << setw(15) << "|" <<
                                    left << course[i].group[j].name << "  ";
                                }
                                else myfile << left << course[i].group[j].name << "  ";
                            }
                            else break;
                        }
                        myfile << "\r\n\r\n";
                        for (int k = 0; k < 200; k++) {
                            myfile << "-";
                        }
                        myfile << "\r\n\r\n";
                    }
                }
            }
            break;
        case 3:
            for (int i = 0; i < course_total; i++) {
                if (name == course[i].slot.room.name ) {
                    switch(course[i].slot.hour) {
                        case 0:
                            time = "09:00 - 11:00";
                            break;
                        case 1:
                            time = "11:00 - 13:00";
                            break;
                        case 2:
                            time = "14:00 - 16:00";
                            break;
                        case 3:
                            time = "16:00 - 18:00";
                            break;
                        default:
                            time = "Error";
                            break;
                    }
                    myfile << left << setw(58) << course[i].title << "|" <<
                    left << setw(6) << course[i].slot.day << "|" <<
                    left << setw(18) << time << "|" <<
                    left << setw(12) << course[i].size << "|" <<
                    left << setw(28) << course[i].prof.name << "|" <<
                    left << setw(14) << course[i].slot.room.name << "|";
                    for (int j = 0; j < 15; j++) {
                        if (course[i].group[j].name != " ") {
                            if (j < 6) {
                                myfile << left << course[i].group[j].name << "  ";
                            }
                            else if (j == 6 ) {
                                myfile << "\r\n" <<
                                right << setw(59) << "|" <<
                                right << setw(7) <<  "|" <<
                                right << setw(19) << "|" <<
                                right << setw(13) << "|" <<
                                right << setw(29) << "|" <<
                                right << setw(15) << "|" <<
                                left << course[i].group[j].name << "  ";
                            }
                            else myfile << left << course[i].group[j].name << "  ";
                        }
                        else break;
                    }
                    myfile << "\r\n\r\n";
                    for (int k = 0; k < 200; k++) {
                        myfile << "-";
                    }
                    myfile << "\r\n\r\n";
                }
            }
            break;
        default:
            break;
        }
    myfile.close();
}
