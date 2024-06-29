#ifndef STUDENT_TABLE_H_INCLUDED
#define STUDENT_TABLE_H_INCLUDED
#include<stdint.h>


struct Department_Node;
struct Grade_Table;


typedef struct Student_Table
{
    char *ID;
    char * name;
    char * gender;
    int department_id;
    struct Student_Table * next;
} student_t;

student_t * Create_New_Student(student_t * root, char* ID, char * name, char * gender, int dept_id);
void Add_New_Student(student_t ** rootp, char* ID, char * name, char * gender, int dept_id);
void Update_Student(student_t * root, char * ID, char * new_name, int new_dept_id);
student_t* Student_ID_Exists(student_t * root, char * ID);


#endif // STUDENT_TABLE_H_INCLUDED
