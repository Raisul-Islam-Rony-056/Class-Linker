#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED
#include "Student_Table.h"
#include "Department_Table.h"
#include "Grade_Table.h"

void Display_All_Student(student_t * root, department_t *root_d, grade_t * root_g);

void Delete_Student(grade_t ** root_g, student_t ** rootp, char* ID);

#endif // DISPLAY_H_INCLUDED
