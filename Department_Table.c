#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Department_Table.h"
#include "Error.h"
#define new_dept_mem_error "Memory Allocation Failed For Creating New Department"
#define name_mem_error "Memory Allocation Failed For Name Field Of Department"

/*
Parameter : 1. Address of the root node of the Student Linked List
            2. ID of the student to check if its already exist or not.

What It Does : This function traverse the full Department list staring from the root,
               to check whether any node already contains the name or not, if yes then
               the function returns the address of the node. If the name is not found
               on any node then the function returns NULL.

Return type : Return type is pointer to Department Node.

*/
department_t * Department_ID_Exists(department_t * root, int ID)
{
    department_t * temp = root;
    while(temp)
    {
        if(temp->ID == ID)
        {
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}

/*
Parameter : 1. Address of the root node
            2. Name of the department

What the function does: The function creates a new Department
                        using dynamic memory allocation, if memory
                        allocation failed then it prints the error
                        message. We are using a static ID for auto
                        incrementing the ID. If node is already exist
                        in the list then we do not create any new node

Return Type: The function return an address of the Department node.
             If the node creation is successful then the address of
             the node is returned otherwise return value is NULL

*/

int Is_Department_Name_Exist(department_t * root, char *name)
{
    department_t * current = root;
    while(current)
    {
        if(!strcmp(current->name,name))
        {
            return 1;
        }
        current=current->next;
    }
    return 0;
}



department_t * Create_New_Department(department_t *root, char *name)
{
    department_t * new_node =(department_t *)malloc(sizeof(department_t));
    new_node->name=(char *)malloc(strlen(name)+1);
    if(Error_Message(new_node,new_dept_mem_error) || Error_Message(new_node->name,name_mem_error))
    {
        return NULL;
    }
    static department_id = 1;
    new_node->ID=department_id++;
    strcpy(new_node->name,name);
    new_node->next=NULL;
    return new_node;
}

/*
Parameter of the function : 1.Address of the root pointer of the linked list
                            2.Pointer to a character array/string

What it does: This function insert a new department in the existing department list.
              We are inserting the new department node in a sorted manner.

Return type: The return type of this function is void. Basically we just add the newly created
             department to the existing department list. Not returning any value.
*/
void Add_New_Department(department_t **rootp, char *name)
{
    if(Is_Department_Name_Exist(*rootp,name))
    {
        Error_Message(NULL,"Department Name Already Exist\n");
        return;
    }
    department_t * current;
    department_t * new_department = Create_New_Department(*rootp,name);
    if(!new_department)
    {
        return;
    }
    while((current = *rootp)!=NULL)
    {
        rootp=&current->next;
    }
    new_department->next=current;
    *rootp=new_department;
}

/*
Parameter :1. Address of the root pointer of the Department list
           2. ID of the department

What It Does : This function takes the ID of the department and deletes the corresponding node
               from the linked list if it exists.

Return type : This function returns nothing. Return type is void.
*/
void Delete_Department(department_t ** root, int16_t ID)
{
    if(!Department_ID_Exists(*root,ID))
    {
        Error_Message(NULL,"Department Not Found, Deletion Cannot Be Performed\n");
        return;
    }
    department_t *dummy=(department_t*)malloc(sizeof(department_t));
    department_t *current;
    dummy->next=*root;
    current=dummy;

    while(current->next)
    {
        if(current->next->ID==ID)
        {
            department_t * temp= current->next;
            current->next = current->next->next;
            free(temp->name);
            break;

        }
        current=current->next;
    }

    *root=dummy->next;
    free(dummy);
    return;

}

/*
Parameter :1. Root node of the department list
           2. ID of the department
           3. New Name of the department

What It Does : This function takes the ID of the department whose name will be updated
               Then change the department name to new name.

Return type : This function returns nothing. Return type is void.

*/

void Update_Department(department_t * root, int16_t ID, char * new_name)
{
    if(!(Department_ID_Exists(root,ID)))
    {
        Error_Message(NULL,"Department Do Not Exist, Update Is Not Possible");
        return;
    }
    department_t * current=root;
    while(current)
    {
        if(current->ID == ID)
        {
            strcpy(current->name,new_name);
            break;
        }
        current=current->next;
    }
    return;
}


/*
Parameters:root: Pointer to the root node of the student linked list.
           ID: Department ID for which male student count is to be determined.

What the function does:
       This function counts the number of male students in a specified department identified by the department ID.
       It iterates through the linked list of students starting from the root, checking each student's department ID
       and gender. If a student belongs to the specified department and is male ("Male" string comparison), the male_count
       is incremented.

Return Type: int
- Returns the count of male students in the specified department.

*/
int Department_Male_Student(student_t * root,int16_t ID)
{
    int male_count=0;
    student_t * current=root;
    while(current)
    {
        if(current->department_id==ID && !strcmp(current->gender,"Male"))
        {
            ++male_count;
        }
        current=current->next;
    }
    return male_count;
}


/*
Parameters:
- root: Pointer to the root node of the student linked list.
- ID: Department ID for which female student count is to be determined.

What the function does:
Counts the number of female students in a specified department identified by the department ID.
Iterates through the linked list of students starting from the root, checking each student's department ID
and gender. If a student belongs to the specified department and is female ("Female" string comparison),
increments the female_count.

Return Type: int
- Returns the count of female students in the specified department.
*/

int Department_Female_Student(student_t * root, int16_t ID)
{
    int female_count=0;
    student_t * current=root;
    while(current)
    {
        if(current->department_id==ID && !strcmp(current->gender,"Female"))
        {
            ++female_count;
        }
        current=current->next;
    }
    return female_count;
}

/*
Parameters:
- roots: Pointer to the root node of the student linked list.
- root: Pointer to the root node of the department linked list.

What the function does:
Displays all department information including department ID, department name,
number of male students, and number of female students. It iterates through the
linked list of departments starting from the root, printing details for each department.
For each department, it calculates the number of male and female students using
the functions Department_Male_Student and Department_Female_Student.

Return Type: void
*/


void Display_All_Department(student_t *roots, department_t *root)
{
    printf("  -----------------------------------------------------------------------------------\n");
    printf("  |                               All Department Information                        |\n");
    printf("  -----------------------------------------------------------------------------------\n");
    //printf("\n");

    printf("  -----------------------------------------------------------------------------------\n");
    printf("  | %-10s | %-20s | %-20s | %-20s |\n", "Dept ID", "Dept Name", "Male (Number)", "Female (Number)");
    printf("  -----------------------------------------------------------------------------------\n");

    department_t *node = root;
    while (node)
    {
        printf("  | %-10d | %-20s | %-20d | %-20d |\n", node->ID, node->name, Department_Male_Student(roots, node->ID), Department_Female_Student(roots, node->ID));
        printf("  -----------------------------------------------------------------------------------\n");
        node = node->next;
    }
    //printf("  ---------------------------------------------------------------------------------------------------\n");
}

