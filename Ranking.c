#include "Ranking.h"
#include <stdlib.h>
#include <string.h>
#include<stdio.h>
#define Not_Found "N/A"
#define Absent "Abs"

/*
Parameter:
    - char *student_name: A pointer to a character array representing the name of the student.
    - char *student_id: A pointer to a character array representing the ID of the student.
    - char *department_name: A pointer to a character array representing the name of the department.
    - int department_id: An integer representing the ID of the department.
    - int English: An integer representing the student's score in English.
    - int History: An integer representing the student's score in History.
    - int Math: An integer representing the student's score in Math.

What the function does:
    This function creates a new `rank_student_t` structure and initializes its members with the provided values. The function performs the following steps:
    1. Allocates memory for a new `rank_student_t` structure.
    2. Allocates memory for the `student_name`, `student_id`, and `department_name` strings within the structure.
    3. Copies the provided string values into the newly allocated memory.
    4. Assigns the provided integer values to the respective fields within the structure.
    5. Calculates the `total_marks` as the sum of the `English`, `History`, and `Math` scores.
    6. Sets the `next` pointer to `NULL`.
    7. Returns a pointer to the newly created `rank_student_t` structure.

Return Type:
    - The return type of the function is `rank_student_t *`.
    - It returns a pointer to the newly created `rank_student_t` structure.
*/
rank_student_t * Create_New_Rankstudent(char * student_name, char * student_id, char * department_name, int department_id, int English,
                                        int History, int Math)
{
    rank_student_t * new_rank = (rank_student_t *)malloc(sizeof(rank_student_t));

    // Allocate memory for strings
    new_rank->student_name = (char *)malloc(strlen(student_name) + 1);
    new_rank->student_id = (char *)malloc(strlen(student_id) + 1);
    new_rank->department_name = (char *)malloc(strlen(department_name) + 1);
    if(!new_rank || !(new_rank->student_name) || !(new_rank->department_name)|| !(new_rank->student_id)){
        Error_Message(NULL, "Memory Allocation Failed\n");
        free(new_rank);
        free(new_rank->student_name);
        free(student_id);
        free(new_rank->department_name);
        return NULL;
    }

    // Copy strings
    strcpy(new_rank->student_name, student_name);
    strcpy(new_rank->student_id, student_id);
    strcpy(new_rank->department_name, department_name);

    // Assign other values
    new_rank->department_id=department_id;
    new_rank->English = English;
    new_rank->History = History;
    new_rank->Math = Math;
    new_rank->total_marks = English + History + Math;  // total_marks is calculated from the subjects
    new_rank->next=NULL;
    return new_rank;
}

/*
Parameter:
    - department_t *root: A pointer to the root of a linked list of `department_t` structures.
    - int department_id: An integer representing the ID of the department whose name is to be retrieved.

What the function does:
    This function retrieves the name of a department given its ID from a linked list of departments. The function performs the following steps:
    1. Checks if the `department_id` is 0. If so, it returns "N/A".
    2. Iterates through the linked list starting from the `root` pointer.
    3. Compares the `ID` of each `department_t` node with the provided `department_id`.
    4. If a matching `ID` is found, the function returns the corresponding `name` of the department.
    5. If the iteration completes without finding a match, the function returns "N/A".

Return Type:
    - The return type of the function is `char *`.
    - It returns the name of the department if a matching `department_id` is found.
    - It returns "N/A" if the `department_id` is 0 or if no matching department is found in the list.
*/
char * get_department_name(department_t * root, int department_id)
{
    if(department_id==0)
    {
        return "N/A";
    }
    department_t * temp=root;
    while(temp)
    {
        if(temp->ID == department_id)
        {
            return temp->name;
        }
        temp=temp->next;
    }

    return "N/A";
}

/*
Parameter:
    - rank_student_t **root: A double pointer to the root of a linked list of `rank_student_t` structures. This allows the function to modify the head of the list if necessary.
    - char *student_name: A pointer to a character array representing the name of the student.
    - char *student_id: A pointer to a character array representing the ID of the student.
    - char *department_name: A pointer to a character array representing the name of the department.
    - int department_id: An integer representing the ID of the department.
    - int English: An integer representing the student's score in English.
    - int History: An integer representing the student's score in History.
    - int Math: An integer representing the student's score in Math.

What the function does:
    This function adds a new `rank_student_t` structure to the end of a linked list. The function performs the following steps:
    1. Creates a new `rank_student_t` structure with the provided student details by calling the `Create_New_Rankstudent` function.
    2. Checks if the list is empty (`*root` is `NULL`). If it is, sets the new structure as the root of the list.
    3. If the list is not empty, iterates through the list to find the last node.
    4. Adds the new structure to the end of the list by setting the `next` pointer of the last node to point to the new structure.

Return Type:
    - The function has a `void` return type, meaning it does not return any value.
*/

void Add_New_Rank_Student(rank_student_t ** root,char * student_name, char * student_id, char * department_name, int department_id, int English,
                          int History, int Math)
{
    rank_student_t * new_rank_student = Create_New_Rankstudent(student_name,student_id,department_name,department_id,English,History,Math);
    if(*root==NULL)
    {
        *root=new_rank_student;
        return;
    }
    rank_student_t * temp = *root;
    while(temp->next)
    {
        temp=temp->next;

    }
    temp->next=new_rank_student;
    return;

}

/*
 * Parameter:
   - s1: Pointer to the first student record (`rank_student_t`).
   - s2: Pointer to the second student record (`rank_student_t`).
   - check: Integer flag influencing comparison order (specific behavior depends on implementation).

 * What the function does:
   1. Compares student records based on various criteria, potentially influenced by the `check` flag.
     - If `check` is set, it compares department names first (using `strcmp`).
   2. If departments are the same (or `check` is not set):
     - Compares total marks of the students.
     - If total marks differ, returns `s2->total_marks - s1->total_marks`.
     - If total marks are the same, compares student names (using `strcmp`).
     - If names differ, returns the result of `strcmp`.
   3. If total marks and names are the same, compares individual subject marks (English, History, Math) in that order.
     - For each subject, if marks differ, returns `s2->subject_mark - s1->subject_mark`.

 * Return Type:
   - int: An integer value indicating the comparison result:
     - Positive value: `s2` is ranked higher than `s1`.
     - Zero: `s1` and `s2` have the same ranking.
     - Negative value: `s1` is ranked higher than `s2`.
 */


int comapare_students(rank_student_t * s1, rank_student_t * s2, int check)
{
    if(check)
    {
        int deptName=strcmp(s1->department_name,s2->department_name);
        if(deptName)
        {
            return deptName;
        }
    }
    if(s1->total_marks!=s2->total_marks)
    {
        return s2->total_marks - s1->total_marks;
    }
    int nameCompare = strcmp(s1->student_name,s2->student_name);
    if(nameCompare)
    {
        return nameCompare;
    }
    if(s1->English!=s2->English)
    {
        return s2->English - s1->English;
    }
    if(s1->History != s2->History)
    {
        return s2->History - s1->History;
    }
    return s2->Math - s1->Math;
}

/*
 * Merge_List: Merges two sorted linked lists of students

 * Parameter:
   - left: Pointer to the head of the first sorted linked list (`rank_student_t`).
   - right: Pointer to the head of the second sorted linked list (`rank_student_t`).
   - check: Integer flag influencing the comparison order during merging (specific behavior depends on implementation).

 * What the function does:
   1. Merges two pre-sorted linked lists of `rank_student_t` structures into a new sorted list based on the `compare_students` function.
   2. Uses a dummy node (`dummy`) to simplify list manipulation.
   3. Iterates through both lists (`left` and `right`) simultaneously:
     - Compares the head nodes of each list using `compare_students` with the `check` flag.
     - Based on the comparison result:
       - If the element in `left` comes before the element in `right` (negative return value from `compare_students`), it's added to the new list.
       - Otherwise, the element in `right` is added.
   4. After iterating through both lists, any remaining elements in either `left` or `right` are appended to the new list.
   5. Returns the head of the newly created merged list (excluding the dummy node).

 * Return Type:
   - `rank_student_t *`: Pointer to the head of the merged sorted linked list. (Skips the dummy node)
 */

rank_student_t * Merge_List(rank_student_t * left, rank_student_t * right, int check)
{
    rank_student_t dummy;
    rank_student_t * tail = &dummy;
    while(left && right)
    {
        if(comapare_students(left,right,check)<0)
        {
            tail->next=left;
            left=left->next;
        }
        else
        {
            tail->next=right;
            right=right->next;
        }
        tail=tail->next;
    }

    if(left)
    {
        tail->next=left;
    }
    if(right)
    {
        tail->next=right;
    }
    return dummy.next;
}

/*
 * Middle_Node: Finds the middle node of a linked list

 * Parameter:
   - root: Pointer to the head of the linked list (`rank_student_t`).

 * What the function does:
   1. Checks if the list is empty (`root` is NULL). If so, returns NULL.
   2. Uses two pointers, `slow` and `fast`:
     - `slow` moves one node at a time.
     - `fast` moves two nodes at a time (if possible).
   3. Iterates while `fast` and `fast->next` are not NULL:
     - This loop ensures `fast` reaches the end of the list or the second-to-last node.
   4. When the loop terminates, `slow` will be pointing to the middle node of the list (or the only node if there's just one).
   5. Returns the `slow` pointer, which points to the middle node.

 * Return Type:
   - `rank_student_t *`: Pointer to the middle node of the linked list, or NULL if the list is empty.
 */


rank_student_t * Middle_Node(rank_student_t * root)
{
    if(!root)
    {
        return root;
    }
    rank_student_t * slow=root;
    rank_student_t * fast = root->next;

    while(fast && fast->next)
    {
        slow=slow->next;
        fast=fast->next->next;
    }
    return slow;
}


/*
 * Parameter:
   - root: Pointer to the head of the linked list (`rank_student_t`) to be sorted.
   - check: Integer flag influencing the comparison order during sorting (specific behavior depends on implementation).

 * What the function does:
   1. Implements a recursive merge sort algorithm to sort a linked list of `rank_student_t` structures.
   2. Base Case: If the list is empty (`root` is NULL) or has only one element (`root->next` is NULL), it's already sorted and the function returns `root`.
   3. Recursive Case:
     - Finds the middle node of the list using `Middle_Node`.
     - Splits the list into two halves: left sublist (from `root` to the middle node) and right sublist (from the node after the middle node to the end).
     - Recursively sorts the left and right sublists using `Merge_sort` with the same `check` flag.
     - Merges the two sorted sublists back together using `Merge_List` with the `check` flag to maintain the sorting order.
   4. Returns the head of the newly sorted linked list.

 * Return Type:
   - `rank_student_t *`: Pointer to the head of the sorted linked list.
 */

rank_student_t * Merge_sort(rank_student_t * root, int check)
{
    if(root==NULL || root->next==NULL)
    {
        return root;
    }
    rank_student_t * left, *right;
    rank_student_t * middle = Middle_Node(root);
    right=middle->next;
    middle->next=NULL;
    left=Merge_sort(root,check);
    right=Merge_sort(right,check);

    return Merge_List(left,right,check);
}

/*
Parameter:
    - rank_student_t **rootr: A double pointer to the root of a linked list of `rank_student_t` structures. This allows the function to modify the head of the list if necessary.
    - student_t *roots: A pointer to the root of a linked list of `student_t` structures, representing a list of students.
    - grade_t *rootg: A pointer to the root of a linked list of `grade_t` structures, representing grades or marks of students.
    - department_t *rootd: A pointer to the root of a linked list of `department_t` structures, representing departments.

What the function does:
    This function traverses through a linked list of students (`roots`) and performs the following actions for each student:
    1. Retrieves the student's `name`, `ID`, and `department_id` from the `student_t` structure.
    2. Retrieves the department's name corresponding to the `department_id` using the `get_department_name` function.
    3. Retrieves the student's marks from the `grade_t` structure using the `getMarks` function.
    4. If the student has no recorded marks (`marks[0] == -1`), adds a new `rank_student_t` structure to the `rootr` list with default marks (0 for English, History, and Math).
    5. If the student has recorded marks, adds a new `rank_student_t` structure to the `rootr` list with the retrieved marks.
    6. Moves to the next student in the `roots` list and repeats the process until all students have been processed.

Return Type:
    - The function has a `void` return type, meaning it does not return any value.
*/

int * get_marks(grade_t * root, char * id)
{
    grade_t * temp=root;
    int * marks = (int *)malloc(3*sizeof(int));
    while(temp){
        if(!strcmp(temp->Student_Id,id)){
            marks[0]=temp->English;
            marks[1]=temp->History;
            marks[2]=temp->Math;
            return marks;
        }
        temp=temp->next;
    }

    marks[0]=marks[1]=marks[2]=-1;
    return marks;
}
void Student_Traverse(rank_student_t ** rootr, student_t * roots, grade_t *rootg,department_t* rootd)
{
    student_t * temp=roots;
    int English=60, History=65, Math=70;
    while(temp){
        char * department_name=get_department_name(rootd,temp->department_id);
        int * marks=get_marks(rootg,temp->ID);

        Add_New_Rank_Student(rootr,temp->name,temp->ID,department_name,temp->department_id,marks[0],marks[1],marks[2]);
        temp=temp->next;
    }
}
/*

 * Parameter:
   - root: Pointer to the head of the linked list (`rank_student_t`) containing student records.

 * What the function does:
   1. Sorts the provided linked list of students using `Merge_sort` (assuming `check` flag is set to 0 for default ranking).
   2. Prints a formatted table header with student information fields (ID, Name, Department, Scores, Rank).
   3. Iterates through the sorted linked list (`temp` pointer):
     - If the student's total marks are less than 0 (indicating missing data), prints special placeholders ("Not_Found" and "Absent") for missing information.
     - Otherwise, prints the student's details (ID, Name, Department, Scores) and assigns a rank (starting from 1 and incrementing for each student).
   4. Prints a formatted table footer after iterating through all students.

 * Return Type:
   - void (Function does not return a value)
 */
void Display_Rank_Student(rank_student_t * root)
{
    // Sort the list
    root=Merge_sort(root,0);

    // Display the sorted list
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("|                                               All Student Ranking                                            |\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("| %-15s| %-15s| %-15s| %-15s| %-10s| %-10s| %-10s| %-5s|\n","Student ID","Student Name","Department Name","Total Score",
           "English","History","Math","Rank");
    printf("----------------------------------------------------------------------------------------------------------------\n");

    rank_student_t * temp = root;
    int i=1;
    while (temp != NULL)
    {
        if(temp->total_marks<0)
        {
            printf("| %-15s| %-15s| %-15s| %-15s| %-10s| %-10s| %-10s| %-5s|\n",temp->student_id,temp->student_name,temp->department_name,
                   Not_Found,Not_Found,Not_Found,Not_Found,Absent);
        }
        else
        {
            printf("| %-15s| %-15s| %-15s| %-15d| %-10d| %-10d| %-10d| %-5d|\n",temp->student_id,temp->student_name,temp->department_name,
                   temp->total_marks,temp->English,temp->History,temp->Math,i++);
        }

        printf("----------------------------------------------------------------------------------------------------------------\n");
        temp = temp->next;
    }
}

/*
 * Parameter:
   - root: Pointer to the head of the linked list (`rank_student_t`) containing student records.

 * What the function does:
   1. Sorts the provided linked list using `Merge_sort` with the `check` flag set to 1 (assuming this triggers department-based ranking).
   2. Prints a formatted table header with student information fields and a "Rank" column.
   3. Iterates through the sorted linked list (`temp` pointer):
     - Tracks the current department ID (`id`).
     - If the student belongs to a new department (department ID differs from `id`):
       - Resets the rank counter (`i`) to 1 for the new department.
       - Updates `id` to the current department ID.
     - If the student's total marks are less than 0 (indicating missing data), prints special placeholders for missing information.
     - Otherwise, prints the student's details (Department Name, ID, Name, Scores) and assigns a rank within their department (starting from 1 and incrementing for each student within the same department).
   4. Prints a formatted table footer after iterating through all students.

 * Return Type:
   - void (Function does not return a value)
 */

void Display_Department_Rank(rank_student_t * root)
{
    // Sort the list
    root=Merge_sort(root,1);

    // Display the sorted list
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("|                                               All Department Ranking                                         |\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("| %-15s| %-15s| %-15s| %-15s| %-10s| %-10s| %-10s| %-5s|\n","Department Name","Student ID","Student Name","Total Score",
           "English","History","Math","Rank");
    printf("----------------------------------------------------------------------------------------------------------------\n");

    rank_student_t * temp = root;
    int i=1;
    int id=-1;

    while (temp != NULL)
    {
        if(id!=temp->department_id)
        {
            i=1;
            id=temp->department_id;
            printf("----------------------------------------------------------------------------------------------------------------\n");
            //printf("----------------------------------------------------------------------------------------------------------------\n");
        }
        if(temp->total_marks<0)
        {
            printf("| %-15s| %-15s| %-15s| %-15s| %-10s| %-10s| %-10s| %-5s|\n",temp->department_name,temp->student_id,temp->student_name,
                   Not_Found,Not_Found,Not_Found,Not_Found,Absent);
        }
        else
        {
            printf("| %-15s| %-15s| %-15s| %-15d| %-10d| %-10d| %-10d| %-5d|\n",temp->department_name,temp->student_id,temp->student_name,
                   temp->total_marks,temp->English,temp->History,temp->Math,i++);
        }

        printf("----------------------------------------------------------------------------------------------------------------\n");
        temp = temp->next;
    }
}


