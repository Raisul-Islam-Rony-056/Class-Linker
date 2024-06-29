#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED
#include "Department_Table.h"
#include "Grade_Table.h"
#include "Student_Table.h"
#include "Display.h"
#include "Error.h"
typedef struct Rankstudent
{
    char * student_name;
    char * student_id;
    char * department_name;
    int department_id;
    int English;
    int History;
    int Math;
    int total_marks;
    struct Rankstudent * next;

} rank_student_t;

rank_student_t * Create_New_Rankstudent(char * student_name, char * student_id, char * department_name, int department_id, int English,
                                        int History, int Math);


#endif // RANKING_H_INCLUDED
