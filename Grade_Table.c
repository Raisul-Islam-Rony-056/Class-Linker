#include "Grade_Table.h"
#include "Student_Table.h"
#include "Error.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define new_grade_memory_err "Memory Allocation Failed For New Grade"

/*
Parameter : 1. Address of the root node of the Grade Linked List
            2. ID of the student. It should be unique.

What the function does: This function checks if a grade node for a given student ID exists in the Grade Linked List.
                        It traverses the linked list, comparing each node's Student_Id with the given Student_Id.
                        If a match is found, it returns the address of the matching grade node.
                        If no match is found after traversing the entire list, it returns NULL.

Return Type: The return type of the function is the address of the grade node if it exists.
             If a grade node with the specified Student_Id is found, it returns the address of that node.
             Otherwise, it returns NULL.
*/
grade_t* Grade_Exists(grade_t *root, char * Student_Id)
{
    grade_t * temp=root;
    while(temp)
    {
        if(!strcmp(temp->Student_Id,Student_Id))
        {
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}
/*
Parameter : 1. Address of the root node of the Student Linked List
            2. ID of the student. It should be unique and already exist in the Student Linked List.
            3. Grade in English subject (integer).
            4. Grade in History subject (integer).
            5. Grade in Math subject (integer).

What the function does: This function creates a new grade node for a student. It uses dynamic memory
                        allocation while assigning memory for the node. It first checks if the
                        Student ID exists in the Student Linked List. If not, it displays an error
                        message and returns NULL. It then checks for any memory allocation errors. If
                        there are any, it displays an appropriate error message, frees the allocated
                        memory, and returns NULL. If the node creation is successful, it assigns the
                        grades to the new node and returns the address of the newly created node.

Return Type: The return type of the function is the address of the newly created Grade node.
             If the node creation is successful, it returns the address of the new node.
             Otherwise, it returns NULL.
*/
grade_t * Create_New_Grade(student_t * rootp, char* Student_Id, int_8 English, int_8 History, int_8 Math)
{
    grade_t * new_grade =(grade_t *)malloc(sizeof(grade_t));

    if(!Student_ID_Exists(rootp,Student_Id))
    {
        Error_Message(NULL,"Student ID Not Exist\n");
        free(new_grade);
        return NULL;
    }

    if(Error_Message(new_grade,new_grade_memory_err))
    {
        free(new_grade);
        return NULL;
    }
    new_grade->Student_Id=(char*)malloc(strlen(Student_Id) + 1);

    strcpy(new_grade->Student_Id, Student_Id);
    new_grade->English=English;
    new_grade->History = History;
    new_grade->Math =Math;
    new_grade->next = NULL;
    return new_grade;
}

/*
Parameter : 1. Address of the root node of the Student Linked List
            2. Address of the root pointer of the Grade Linked List
            3. ID of the student. It should be unique and already exist in the Student Linked List.
            4. Grade in English subject (integer).
            5. Grade in History subject (integer).
            6. Grade in Math subject (integer).

What the function does: This function adds a new grade node for a student to the Grade Linked List.
                        It first checks if a grade node for the given Student_Id already exists.
                        If it exists, it displays an error message and returns without adding a new grade.
                        If the grade node does not exist, it creates a new grade node using the Create_New_Grade function.
                        If the new grade node creation is successful, it inserts the new grade node in the
                        correct position in the Grade Linked List, maintaining the sorted order based on Student_Id.

Return Type: The function does not return a value.Return type is void.
*/


void Add_New_Grade(student_t * roots, grade_t ** rootp, char* Student_Id, int_8 English, int_8 History, int_8 Math)
{
    if(Grade_Exists(*rootp,Student_Id))
    {
        Error_Message(NULL,"Grade Already Exists\n");
        return;
    }
    grade_t * current;
    grade_t * new_grade=Create_New_Grade(roots, Student_Id,English,History,Math);

    if(!new_grade)
    {
        return;
    }

    while((current=*rootp)!=NULL && strcmp(current->Student_Id,Student_Id)<0)
    {
        rootp= & current->next;
    }

    new_grade->next=current;
    *rootp = new_grade;
    return;
}


/*
Parameter : 1. Address of the root pointer of the Grade Linked List
            2. ID of the student. It should be unique.

What the function does: This function deletes a grade node for a given student ID from the Grade Linked List.
                        It first checks if a grade node for the given Student_Id exists.
                        If the grade node does not exist, it displays an error message and returns without making any changes.
                        If the grade node exists, it removes the node from the list, frees the memory allocated for the node,
                        and updates the linked list to maintain its integrity.

Return Type: The function does not return a value. It modifies the Grade Linked List by deleting the specified node if it exists.
             If the grade node does not exist, the list remains unchanged.
*/

void Delete_Grade(grade_t **rootp, char * Student_Id)
{
    if(!Grade_Exists(*rootp, Student_Id))
    {
        Error_Message(NULL,"Grade Not Found, Deletion Cannot Be Performed\n");
        return;
    }
    grade_t * current;
    grade_t * dummy=(grade_t*)malloc(sizeof(grade_t));
    dummy->next=*rootp;
    current=dummy;

    while(current->next)
    {
        if(!strcmp(current->next->Student_Id,Student_Id))   // Fixed this condition
        {
            grade_t * temp=current->next;
            current->next=current->next->next;
            free(temp->Student_Id);
            free(temp);  // Free the memory of the node being deleted
            break;
        }
        current=current->next;
    }
    *rootp=dummy->next;
    free(dummy);
    return;
}

/*
Parameter : 1. Address of the root node of the Student Linked List
            2. Address of the root node of the Grade Linked List
            3. ID of the student. It should be unique and exist in the Grade Linked List.
            4. New grade in English subject (integer).
            5. New grade in History subject (integer).
            6. New grade in Math subject (integer).

What the function does: This function updates the grades (English, History, Math) for a student with a given Student_Id
                        in the Grade Linked List.
                        It first checks if a grade node for the given Student_Id exists in the Grade Linked List.
                        If the grade node does not exist, it displays an error message and returns without making any changes.
                        If the grade node exists, it traverses the linked list to find the node with the matching Student_Id
                        and updates the grades with the new values provided.

Return Type: The function does not return a value. It modifies the Grade Linked List by updating the grades of the specified student.
             If the grade node does not exist for the given Student_Id, the list remains unchanged.
*/


void Update_Grade(student_t * rootp, grade_t * root, char* Student_Id, int_8 new_english, int_8 new_history, int_8 new_math)
{
    if(!Grade_Exists(root,Student_Id))
    {
        Error_Message(NULL, "Not A Valid Student ID");
        return;
    }

    grade_t * temp = root;
    while(temp)
    {
        if(!strcmp(temp->Student_Id,Student_Id))
        {
            temp->English=new_english;
            temp->History=new_history;
            temp->Math=new_math;
            break;
        }
        temp=temp->next;
    }
    return;
}
/*
Parameter : 1. Address of the root node of the Student Linked List
            2. ID of the student whose name is to be retrieved. It should be unique and exist in the Student Linked List.

What the function does: This function retrieves the name of a student with a given Student_Id from the Student Linked List.
                        It traverses the linked list to find the node with the matching Student_Id.
                        If a node with the specified Student_Id is found, it returns a pointer to the name of the student.
                        If no node with the specified Student_Id is found, it returns NULL.

Return Type: The return type of the function is a pointer to the character array (string) containing the name of the student
*/

char * getStudent_Name(student_t * roots, char * Student_Id)
{
    student_t * current = roots;
    while(current)
    {
        if(!strcmp(current->ID,Student_Id))
        {
            return current->name;
        }
        current=current->next;
    }
    return NULL;
}

/*
Parameter : 1. Address of the root node of the Student Linked List
            2. Address of the root node of the Grade Linked List

What the function does: This function displays all student grades stored in the Grade Linked List.
                        It prints a header and a table format to display the student names, along with their grades
                        in English, History, and Math subjects.
                        It retrieves each student's name using the getStudent_Name function based on their Student_Id.
                        If a student's name cannot be found (likely due to an invalid Student_Id), it displays "Unknown".
                        The function iterates through the Grade Linked List and prints each student's name and their grades.

Return Type: The function does not return a value. It outputs the grades of all students in the specified format.
*/

void Display_All_Grade(student_t *roots, grade_t *root_g)
{
    printf("  -------------------------------------------------------------------------\n");
    printf("  |                              All Student Grades                       |\n");
    printf("  -------------------------------------------------------------------------\n");
    //printf("\n");

    printf("  -------------------------------------------------------------------------\n");
    printf("  | %-20s | %-20s | %-10s | %-10s |\n", "Student Name", "English", "History", "Math");
    printf("  -------------------------------------------------------------------------\n");

    grade_t *current = root_g;
    while (current)
    {
        char *name = getStudent_Name(roots, current->Student_Id);
        printf("  | %-20s | %-20d | %-10d | %-10d |\n", name, current->English, current->History, current->Math);
        printf("  -------------------------------------------------------------------------\n");
        current = current->next;
    }
}

