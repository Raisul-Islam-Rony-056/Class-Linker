#include "Display.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
Parameters:
- root_d: Pointer to the root node of the department linked list.
- dept_id: Department ID for which the department name is to be retrieved.

What the function does:
Searches for a department with the specified department ID in the linked list of departments
starting from root_d. If found, returns the name of the department. If no department with
the specified ID is found, returns "N/A".

Return Type: char *
- Returns a pointer to the name of the department if found, otherwise returns "N/A".
*/

char *getDepartment_Name(department_t * root_d, int16_t dept_id)
{
    department_t * current=root_d;
    while(current)
    {
        if(current->ID==dept_id)
        {
            return current->name;
        }
        current=current->next;
    }
    return "N/A";
}

/*
Parameters:
- root_g: Pointer to the root node of the grade linked list.
- student_id: ID of the student whose marks are to be retrieved.

What the function does:
Searches for a student with the specified student ID in the linked list of grades
starting from root_g. If found, allocates memory for an integer array of size 3,
stores the English, History, and Math marks of the student in the array, and returns
a pointer to this array. If no student with the specified ID is found, returns an
integer array where each element is set to -1 to indicate marks are not found.

Return Type: int *
- Returns a pointer to an integer array containing the student's marks (English, History, Math),
  or returns an integer array [-1, -1, -1] if the student ID is not found.
- Note: Caller is responsible for freeing the memory allocated for the integer array after use.
*/

int * getMarks(grade_t * root_g, char * student_id)
{
    int *marks=(int *)malloc((3*sizeof(int)));
    grade_t * current=root_g;
    while(current)
    {
        if(!strcmp(current->Student_Id,student_id))
        {
            marks[0]=current->English;
            marks[1]=current->History;
            marks[2]=current->Math;
            return marks;
        }
        current=current->next;
    }
    marks[0]=-1;
    marks[1]=-1;
    marks[2]=-1;
    return marks;
}

/*
Parameters:
- root: Pointer to the root node of the student linked list.
- root_d: Pointer to the root node of the department linked list.
- root_g: Pointer to the root node of the grade linked list.

What the function does:
Displays all information about students including their ID, name, gender, department name,
and marks in English, History, and Math. It iterates through the student linked list (root),
retrieves marks using getMarks() function from the grade linked list (root_g) for each student,
and retrieves department names using getDepartment_Name() function from the department linked
list (root_d). If marks are not found for a student, it displays "-" for the marks.

Return Type: void
- Displays information directly using printf statements.
- No data is modified or returned; it purely outputs information to the console.
*/

void Display_All_Student(student_t *root, department_t *root_d, grade_t *root_g)
{
    printf("  ---------------------------------------------------------------------------------------------------\n");
    printf("  |                                    Display All Student                                          |\n");
    printf("  ---------------------------------------------------------------------------------------------------\n");

    printf("  ---------------------------------------------------------------------------------------------------\n");
    printf("  | %-10s | %-20s | %-6s | %-20s | %-7s | %-7s | %-7s |\n",
           "Student ID", "Student Name", "Gender", "Department Name", "English", "History", "Math");
    printf("  ---------------------------------------------------------------------------------------------------\n");

    student_t *temp = root;
    while (temp)
    {
        int *mark = getMarks(root_g, temp->ID);
        char *dept_name = getDepartment_Name(root_d, temp->department_id);
        if (mark[0] == -1)
        {
            printf("  | %-10s | %-20s | %-6s | %-20s | %-7s | %-7s | %-7s |\n",
                   temp->ID, temp->name, temp->gender, dept_name, "-", "-", "-");
            printf("  ---------------------------------------------------------------------------------------------------\n");
        }
        else
        {
            printf("  | %-10s | %-20s | %-6s | %-20s | %-7d | %-7d | %-7d |\n",
                   temp->ID, temp->name, temp->gender, dept_name, mark[0], mark[1], mark[2]);
            printf("  ---------------------------------------------------------------------------------------------------\n");
        }
        free(mark);
        temp = temp->next;
    }
    return;
}

/*
Parameters:
- root_g: Pointer to the root pointer of the grade linked list.
- rootp: Pointer to the root pointer of the student linked list.
- ID: Student ID to be deleted.

What the function does:
Deletes a student from the student linked list (rootp). It first checks if the student exists
using Student_ID_Exists() function. If the student is found, it deletes the corresponding
grades using Delete_Grade() function from the grade linked list (root_g). Then, it proceeds
to delete the student node from the student linked list. Memory allocated for the student node
(ID, name, gender) is freed to prevent memory leaks.

Return Type: void
- Modifies the student linked list and grade linked list indirectly by deleting nodes.
- Outputs error message if the student is not found and cannot be deleted.
*/

void Delete_Student(grade_t ** root_g, student_t ** rootp, char* ID)
{

    student_t * current;
    if(!(current = Student_ID_Exists(*rootp, ID)))
    {
        Error_Message(NULL,"Student Not Found, Cannot Delete The Student");
        return;
    }
    Delete_Grade(root_g,ID);
    student_t * dummy=(student_t*)malloc(sizeof(student_t));
    dummy->next=*rootp;
    current=dummy;
    while(current->next)
    {
        if(!strcmp(current->next->ID,ID))
        {
            student_t * temp=current->next;
            current->next=current->next->next;

            free(temp->ID);
            free(temp->name);
            free(temp->gender);

            break;
        }
        current=current->next;
    }
    *rootp=dummy->next;
    return;

}

