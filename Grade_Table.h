#ifndef GRADE_TABLE_H_INCLUDED
#define GRADE_TABLE_H_INCLUDED
#include "Student_Table.h"
typedef char int_8;
typedef struct Grade_Table
{
    char* Student_Id;
    int_8 English;
    int_8 History;
    int_8 Math;
    struct Grade_Table * next;

} grade_t;

grade_t* Grade_Exists(grade_t *root, char * Student_Id);
grade_t * Create_New_Grade(student_t * rootp, char* Student_Id, int_8 English, int_8 History, int_8 Math);
void Add_New_Grade(student_t * roots, grade_t ** rootp, char* Student_Id, int_8 English, int_8 History, int_8 Math);
void Update_Grade(student_t * rootp,grade_t * root, char* Student_Id, int_8 new_english, int_8 new_history, int_8 new_math);
void Delete_Grade(grade_t **rootp, char * Student_Id);
void Display_All_Grade(student_t* roots,grade_t * root);


#endif // GRADE_TABLE_H_INCLUDED
