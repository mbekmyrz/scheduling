#ifndef schedule_h
#define schedule_h

void registration(int room_total,int slot_total,int group_total,int instructor_total,int course_total);
int instructorIndex_find(int instructor_total, int courseIndex);
int groupIndex_find(int courseIndex, int i, int group_total);
int nextRandom(int slot_total, int courseIndex);
int nextRandomLab(int slot_total, int courseIndex);
int freeGroupSlot(int groupIndex);
int freeInstructorSlot(int instructorIndex);
void sortCoursesBySize(int course_total);

#endif
