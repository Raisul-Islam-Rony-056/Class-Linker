#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "Student_Table.h"
#include "Error.h"

#define student_memory_error "Memory Allocation Failed For New Student"
#define name_field_mem_error "Memory Allocation For Name Field Failed"
#define gender_field_mem_error "Memory Allocation For Gender Field Failed"

/*
Parameter : 1. Address of the root node of the Student Linked List
            2. ID of the student to check if its already exist or not.

What It Does : This function traverse the full student list staring from the root, to check
               whether any node already contains the ID that new student is giving, if yes then
               the function returns the address of the node. If the ID is not found on any node then
               the function returns NULL.

Return type : Return type is pointer to Student Node.
*/
student_t * Student_ID_Exists(student_t * root, char* ID)
{
    student_t * temp = root;
    while(temp)
    {
        if(!strcmp(temp->ID, ID))
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

/*
Parameter : 1. Address of the root node of the Student Linked List
            2. ID of the student. It should be unique.
            3. Name of the student. Must be less than 20 character
            4. Gender of the student. Male or Female
            5. The department of the student

What the function does: This function creates a new student node. It uses dynamic memory
                        allocation while assigning memory for the node. It checks if the
                        ID is already exist or not, checks for the name length is less than
                        20 or not. If the node creation is successful then it returns the
                        address of the newly created node otherwise return null.
Return Type: The return type of the function is the address of the node.If the node creation is
              successful then it returns the address of the newly created node otherwise return null
*/
student_t * Create_New_Student(student_t * root, char* ID, char * name, char * gender, int dept_id)
{
    if(Student_ID_Exists(root, ID))
    {
        return NULL;
    }
    student_t * new_student = (student_t*)malloc(sizeof(student_t));
    if(Error_Message(new_student, student_memory_error))
    {
        return NULL;
    }
    new_student->ID = (char *)malloc(strlen(ID) + 1);
    new_student->name = (char *)malloc(strlen(name) + 1);
    new_student->gender = (char *)malloc(strlen(gender) + 1);

    if(Error_Message(new_student->name, name_field_mem_error) || Error_Message(new_student->gender, gender_field_mem_error))
    {
        free(new_student->ID);
        free(new_student->name);
        free(new_student->gender);
        return NULL;
    }

    strcpy(new_student->ID, ID);
    strcpy(new_student->name, name);
    strcpy(new_student->gender, gender);
    new_student->department_id = dept_id;
    new_student->next = NULL;

    return new_student;
}

/*
Parameter : 1. Address of the root node of the Student Linked List
            2. ID of the student. It should be unique.
            3. Name of the student. Must be less than 20 character
            4. Gender of the student. Male or Female
            5. The department of the student.

What It Does : This Function is basically inserting a new student information to the existing student list.
               This function follows sorted insertion to the student list based on the student ID.

Return Type: The function returns nothing. Return type is void.
*/
void Add_New_Student(student_t ** rootp, char* ID, char * name, char * gender, int dept_id)
{
    student_t * current;
    student_t * new_student;
    new_student = Create_New_Student(*rootp, ID, name, gender, dept_id);

    if(!new_student)
    {
        return;
    }
    while((current = *rootp) != NULL && strcmp(current->ID, ID) < 0)
    {
        rootp = &current->next;
    }
    new_student->next = current;
    *rootp = new_student;
}

/*
Parameter :1. Root node of the Student list
           2. ID of the student
           3. New Name of the student
           4. New department ID of the student

What It Does : This function takes the ID of the student whose name and
               department ID will be updated. Then change the student name to new name.
               Department ID to new_dept_id

Return type : This function returns nothing. Return type is void.
*/
void Update_Student(student_t * root, char* ID, char * new_name, int new_dept_id)
{
    student_t * temp;
    if(!(temp = Student_ID_Exists(root, ID)))
    {
        Error_Message(temp,"Student Not Found, Cannot Update The Student");
        return;
    }
    strcpy(temp->name, new_name);
    temp->department_id = new_dept_id;
    return;
}


