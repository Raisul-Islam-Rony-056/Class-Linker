#ifndef DEPARTMENT_TABLE_H_INCLUDED
#define DEPARTMENT_TABLE_H_INCLUDED
#include <stdint.h>
#include<stdbool.h>
#include "Student_Table.h"
typedef struct Department_Node
{
    int16_t ID;
    char * name;
    struct Department_Node * next;

} department_t;

department_t * Create_New_Department(department_t* root, char * name);
void Add_New_Department(department_t **rootp, char *name);
void Display_All_Department(student_t* roots,department_t * root);
void Delete_Department(department_t ** root, int16_t ID);
void Update_Department(department_t * root, int16_t ID, char * new_name);
int Department_Male_Student(student_t * root,int16_t ID);
int Department_Female_Student(student_t *root,int16_t ID);
department_t * Department_ID_Exists(department_t * root, int ID);


#endif // DEPARTMENT_TABLE_H_INCLUDED
