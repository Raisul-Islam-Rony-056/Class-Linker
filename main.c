#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include<stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include<string.h>
#include "Department_Table.h"
#include "Student_Table.h"
#include "Grade_Table.h"
#include "Error.h"
#include "Ranking.h"
#include "Display.h"

department_t * department_root = NULL;
student_t * student_root = NULL;
grade_t * grade_root = NULL;
rank_student_t * rank_root = NULL;



/*
Parameter:
    - const char *str: A pointer to a character array (string) that represents the number to be validated.

What the function does:
    This function checks if a given string is a valid number. The function performs the following operations:
    1. It iterates through each character of the string.
    2. If any character in the string is not a digit (0-9), the function returns -1, indicating that the string is not a valid number.
    3. If all characters in the string are digits, the function converts the string to an integer using the atoi() function and returns this integer value.

Return Type:
    - The return type of the function is int.
    - It returns the integer value of the string if it consists of only digits.
    - It returns -1 if the string contains any non-digit characters.
*/
int is_valid_number(const char *str)
{
    // Check if the string is not empty and consists of only digits
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return -1;
        }
    }
    return atoi(str);
}


/*
Parameter: None.

What the function does:
    This function clears the input buffer to remove any extraneous characters left in the buffer. This is often used after reading input to ensure that any remaining characters, such as newline characters, do not interfere with subsequent input operations.
    The function works by reading characters from the input buffer one at a time until it encounters either a newline character ('\n') or the end-of-file indicator (EOF). It discards these characters to clear the buffer.

Return Type: The function has a void return type, meaning it does not return any value.
*/

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
/*
Parameter : 1. Pointer to the character array representing the student ID.

What the function does: This function checks if a given student ID is valid according to specified criteria:
                        1. The ID must be exactly 8 characters long.
                        2. The first 5 characters must match the string "BDCOM".
                        3. The last 3 characters must be digits (0-9).

                        If any of these conditions are not met, the function prints an error message indicating
                        that the student ID is invalid and returns false. If all conditions are satisfied,
                        the function returns true indicating that the student ID is valid.

Return Type: The return type of the function is a boolean (true or false). It returns true if the student ID
             meets all the validity criteria, otherwise it returns false.
*/

bool Is_Student_ID_Valid(char * ID)
{
    if(strlen(ID)!=8 || strncmp(ID,"BDCOM",5)!=0)
    {
        printf("Invalid Student ID\n");
        return false;
    }
    int i=5;
    for(; i<8; ++i)
    {
        if(!isdigit(ID[i]))
        {
            printf("Invalid Student ID\n");
            return false;
        }
    }
    return true;
}

/*
Parameter : 1. Address of the root node of the Department Linked List
            2. 16-bit integer representing the department ID to be validated.

What the function does: This function checks if a given department ID is valid by searching through a linked list
                        of departments.
                        It traverses the linked list and compares each department's ID with the provided ID.
                        If a department with the same ID is found, the function returns true indicating that the
                        department ID is valid.
                        If no department with the provided ID is found in the linked list, the function returns false.

Return Type: The return type of the function is a boolean (true or false). It returns true if the department ID
             exists in the linked list of departments, otherwise it returns false.
*/

bool Is_Department_ID_Valid(department_t * root_d, int16_t ID)
{
    department_t * current=root_d;
    while(current)
    {
        if(current->ID==ID)
        {
            return true;
        }
        current=current->next;
    }
    return false;
}

/*
Parameter : 1. Pointer to a character array (string) that may contain trailing spaces.

What the function does: This function removes trailing spaces from the end of a given string.
                        It starts from the end of the string and moves backwards, checking each character.
                        If the character is a space (' '), it continues moving backwards until a non-space character
                        or the beginning of the string is encountered. Once trailing spaces are removed,
                        it adds a null terminator ('\0') at the new end of the string to ensure it remains valid.

Return Type: The function does not return a value. It modifies the input string in place by removing trailing spaces.
*/

void Remove_Trailing_Spaces(char * ara)
{
    int length=strlen(ara);
    int i=length-1;
    while(ara[i]==' ')
    {
        i--;
    }
    ara[i+1]='\0';
    return;
}
/*
Parameter : 1. Pointer to a character array containing the name of the file to be read.

What the function does: This function reads student information from a text file specified by `file_name`.
                        It attempts to open the file for reading. If the file cannot be opened, it displays
                        an error message using Error_Message function and returns without further action.
                        The function reads data from the file line by line using fgets and parses the data using
                        sscanf to extract student ID, name, gender, and department ID from each line.
                        For each student's information read successfully, it calls the Add_New_Student function
                        to add the student to a linked list (student_root in this case).

Return Type: The function does not return a value. It reads data from the file and adds students to the linked list
             as specified, handling errors if the file cannot be opened.
*/


void readStudent_Info(char *file_name)
{
    FILE *file = fopen(file_name, "r");
    if (!file)
    {
        Error_Message(NULL,"Grade File Cannot be Opened\n");
        return; // Exit if the file cannot be opened
    }

    char ID[21];
    char name[21];
    char gender[7];

    int dept_id;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file))
    {
        if (sscanf(buffer, "%20s", ID) != 1)
            break;

        if (!fgets(buffer, sizeof(buffer), file))
            break;
        sscanf(buffer, "%100[^\n]", name);

        if (!fgets(buffer, sizeof(buffer), file))
            break;
        sscanf(buffer, "%7s", gender);


        if (!fgets(buffer, sizeof(buffer), file))
            break;
        if (sscanf(buffer, "%d", &dept_id) != 1)
            break;

        //printf("%s %s %s %d\n", ID, name, gender, dept_id);
        Add_New_Student(&student_root, ID, name, gender, dept_id);
    }
    printf("Student Loaded Successfully\n");
    sleep(1);
    fclose(file);
}

/*
Parameter : 1. Pointer to a character array containing the name of the file to be read.

What the function does: This function reads department information from a text file specified by `file_name`.
                        It attempts to open the file for reading. If the file cannot be opened, it displays
                        an error message using Error_Message function, closes the file, and returns without further action.

                        The function reads each line from the file using fscanf with %[^\n]\n format specifier to capture
                        the department name. It then removes any trailing spaces from the department name using
                        Remove_Trailing_Spaces function.

                        If the trimmed department name has a length less than 20 characters, it calls the
                        Add_New_Department function to add the department to a linked list (department_root in this case).

Return Type: The function does not return a value. It reads data from the file and adds departments to the linked list
             as specified, handling errors if the file cannot be opened.
*/

void readDepartment_Info(char * file_name)
{
    FILE * file = fopen(file_name,"r");
    if(!file)
    {
        Error_Message(file, "Department File Cannot be Opened\n");
        fclose(file);
        return;
    }
    char deparment_name[21];
    while(fscanf(file,"%[^\n]\n",deparment_name)!=EOF)
    {
        Remove_Trailing_Spaces(deparment_name);
        if(strlen(deparment_name)<20)
        {
            Add_New_Department(&department_root,deparment_name);
        }

    }
    printf("Department Loaded Successfully\n");
    sleep(1);

    fclose(file);
    return;
}
/*
Parameter : 1. Pointer to a character array containing the name of the file to be read.

What the function does: This function reads grade information from a text file specified by `file_name`.
                        It attempts to open the file for reading. If the file cannot be opened, it displays
                        an error message using Error_Message function, closes the file, and returns without further action.
                        The function reads each set of data from the file using fscanf with %s\n%d\n%d\n%d\n format specifiers
                        to capture the Student_Id, English grade, History grade, and Math grade respectively. It expects
                        each set of data to be successfully read (return value 4 from fscanf) to continue processing.
                        It removes any trailing spaces from the Student_Id using Remove_Trailing_Spaces function.
                        If the trimmed Student_Id has a length less than 20 characters, it calls the Add_New_Grade function
                        to add the grade information to a linked list (grade_root in this case).

Return Type: The function does not return a value. It reads data from the file and adds grades to the linked list
             as specified, handling errors if the file cannot be opened.
*/

void readGrade_Info(char * file_name)
{
    FILE * file = fopen(file_name,"r");
    if(!file)
    {
        Error_Message(file, "Grade File Cannot be Opened\n");
        fclose(file);
        return;
    }
    char Student_Id[21];
    int English,History,Math;
    while(fscanf(file,"%s\n%d\n%d\n%d\n",Student_Id,&English,&History,&Math)==4)
    {
        Remove_Trailing_Spaces(Student_Id);
        if(strlen(Student_Id)<20)
        {
            Add_New_Grade(student_root,&grade_root,Student_Id,English,History,Math);
        }
    }
    printf("Grade Loaded Successfully\n");
    sleep(1);
    return;
}
/*
Parameter : 1. Pointer to a character array containing the name of the file to be written.

What the function does: This function saves grade information from the linked list `grade_root` to a text file specified by `file_name`.
                        It attempts to open the file for writing. If the file cannot be opened, it displays an error message using
                        Error_Message function, closes the file, and returns without further action.

                        The function iterates through the linked list `grade_root` using a while loop, and for each node (grade),
                        it writes the Student_Id, English grade, History grade, and Math grade to the file using fprintf.

Return Type: The function does not return a value. It writes grade information from the linked list to the specified file,
             handling errors if the file cannot be opened for writing.
*/
void saveGrade_Info(char * file_name)
{
    FILE * file = fopen(file_name,"w");
    if(!file)
    {
        Error_Message(file, "Grade File Cannot be Opened\n");
        fclose(file);
        return;
    }
    grade_t * temp=grade_root;
    while(temp)
    {
        fprintf(file,"%s\n%d\n%d\n%d\n",temp->Student_Id,temp->English,temp->History,temp->Math);
        temp=temp->next;
    }
    fclose(file);
    return;
}

/*
Parameter : 1. Pointer to a character array containing the name of the file to be written.

What the function does: This function saves department information from the linked list `department_root` to a text file specified by `file_name`.
                        It attempts to open the file for writing. If the file cannot be opened, it displays an error message using
                        Error_Message function, closes the file, and returns without further action.

                        The function iterates through the linked list `department_root` using a while loop, and for each node (department),
                        it writes the department name to the file using fprintf.

Return Type: The function does not return a value. It writes department information from the linked list to the specified file,
             handling errors if the file cannot be opened for writing.
*/

void saveDepartment_Info(char * file_name)
{
    FILE * file = fopen(file_name,"w");
    if(!file)
    {
        Error_Message(file, "Department File Cannot be Opened\n");
        fclose(file);
        return;
    }
    department_t * temp = department_root;
    while(temp)
    {
        fprintf(file,"%s\n",temp->name);
        temp=temp->next;
    }
    fclose(file);
    return;
}

/*
Parameter : 1. Pointer to a character array containing the name of the file to be written.

What the function does: This function saves student information from the linked list `student_root` to a text file specified by `file_name`.
                        It attempts to open the file for writing. If the file cannot be opened, it displays an error message using
                        Error_Message function, closes the file, and returns without further action.

                        The function iterates through the linked list `student_root` using a while loop, and for each node (student),
                        it writes the student ID, name, gender, and department ID to the file using fprintf.

Return Type: The function does not return a value. It writes student information from the linked list to the specified file,
             handling errors if the file cannot be opened for writing.
*/

void saveStudent_Info(char *file_name)
{
    FILE * file = fopen(file_name,"w");
    if(!file)
    {
        Error_Message(file, "Student File Cannot be Opened\n");
        fclose(file);
        return;
    }
    student_t* temp = student_root;
    while (temp != NULL)
    {
        fprintf(file, "%s\n%s\n%s\n%d\n", temp->ID, temp->name, temp->gender, temp->department_id);
        temp = temp->next;
    }

    fclose(file);
    return;
}

/*
What the function does: This function implements a menu-driven interface for managing departments.
                        It displays a menu with options to add, delete, update, and display departments,
                        as well as an option to exit the menu.

                        - Option 1: Allows the user to add a new department by entering the department name.
                        - Option 2: Allows the user to delete a department by entering the department ID.
                        - Option 3: Allows the user to update a department's name by entering the department ID
                          and providing a new name.
                        - Option 4: Displays all departments currently stored in the system.
                        - Option 5: Exits the menu and returns to the caller function.

                        The function uses scanf for input handling and ensures that department names entered are
                        less than 20 characters long. It interacts with functions like Add_New_Department,
                        Delete_Department, Update_Department, and Display_All_Department to perform respective actions
                        on the department linked list (department_root).

Return Type: The function does not return a value. It continuously loops until the user chooses to exit (option 5).
*/

void Department_Menu()
{
    char department_name[20];
    int dept_id;
    int option;
    char input[3];
    do
    {
        printf("\n");
        printf("  **************************************************\n");
        printf("  *                                                *\n");
        printf("  *               Department Management            *\n");
        printf("  *                                                *\n");
        printf("  **************************************************\n");
        printf("  *                                                *\n");
        printf("  *   1. Add Department                            *\n");
        printf("  *                                                *\n");
        printf("  *   2. Delete Department                         *\n");
        printf("  *                                                *\n");
        printf("  *   3. Update Department                         *\n");
        printf("  *                                                *\n");
        printf("  *   4. Display All Departments                   *\n");
        printf("  *                                                *\n");
        printf("  *   5. Exit                                      *\n");
        printf("  *                                                *\n");
        printf("  **************************************************\n");


        printf("Please Enter Your Choice : ");
        clear_input_buffer();
        scanf("%[^\n]s",input);
        if((option = is_valid_number(input))==-1)
        {
            printf("Please Enter Choice Between 1 to 5\n");
            continue;
        }
        switch(option)
        {

        case 1:
            while(true)
            {
                getchar();
                printf("Please Enter the department name(Must Be Less Than 20 Character) : ");
                scanf("%[^\n]s", department_name);
                if(strlen(department_name)<20)
                {
                    break;
                }
            }

            Add_New_Department(&department_root, department_name);
            break;

        case 2:
            printf("Please Enter The ID of the department: ");
            scanf("%d",&dept_id);
            Delete_Department(&department_root,dept_id);
            break;

        case 3:
            printf("Please Enter The ID of the department: ");
            scanf("%d",&dept_id);
            while(true)
            {
                printf("Please Enter the new department name(Must Be Less Than 20 Character): ");
                getchar();
                scanf("%[^\n]s", department_name);
                if(strlen(department_name)<20)
                {
                    break;
                }
            }

            Update_Department(department_root,dept_id,department_name);
            break;

        case 4:
            Display_All_Department(student_root,department_root);
            break;
        case 5:
            return;
        default:
            printf("Please Enter Choice Between 1 to 5\n");
            break;
        }
    }
    while(true);   // Exit when option is 5
}



/*
What the function does: This function implements a menu-driven interface for managing students.
                        It displays a menu with options to add, delete, update, and display students,
                        as well as an option to exit the menu.

                        - Option 1: Allows the user to add a new student by entering the student ID (in the format BDCOM followed by three digits),
                          name, gender, and department ID. Validates the uniqueness of the student ID, the validity of the format,
                          the length of the name (less than 20 characters), the gender (Male or Female), and the validity of the department ID.
                        - Option 2: Allows the user to delete a student by entering the student ID.
                        - Option 3: Allows the user to update a student's department ID and name by entering the student ID and providing
                          new values. Validates the validity of the new department ID (or 0 for no department) and the length of the new name.
                        - Option 4: Displays all students currently stored in the system along with their department and grade information.
                        - Option 5: Exits the menu and returns to the caller function.

                        The function uses scanf for input handling and interacts with functions like Add_New_Student,
                        Delete_Student, Update_Student, and Display_All_Student to perform respective actions on the student linked list (student_root),
                        department linked list (department_root), and grade linked list (grade_root).

Return Type: The function does not return a value. It continuously loops until the user chooses to exit (option 5).
*/

void Student_Menu()
{

    char student_id[20];
    int department_id;
    char name[20], gender[20];
    int option;
    char input[3];
    // Make sure this is properly initialized or passed as an argument

    do
    {
        clear_input_buffer();
        printf("\n");
        printf("  **************************************************\n");
        printf("  *                                                *\n");
        printf("  *                 Student Management             *\n");
        printf("  *                                                *\n");
        printf("  **************************************************\n");
        printf("  *                                                *\n");
        printf("  *  1. Add Student                                *\n");
        printf("  *                                                *\n");
        printf("  *  2. Delete Student                             *\n");
        printf("  *                                                *\n");
        printf("  *  3. Update Student                             *\n");
        printf("  *                                                *\n");
        printf("  *  4. Display All Students                       *\n");
        printf("  *                                                *\n");
        printf("  *  5. Exit                                       *\n");
        printf("  *                                                *\n");
        printf("  **************************************************\n");

        printf("Please Enter Your Choice : ");
        scanf("%[^\n]s", input);
        if((option=is_valid_number(input))==-1)
        {
            printf("Please Enter Number Between 1 to 5\n");
            continue;
        }

        switch(option)
        {
        case 1:
            if(department_root==NULL)
            {
                printf("Please Add Department Before Adding Student\n");
                return;
            }

            while(1)
            {
                clear_input_buffer();
                printf("Please Enter Student ID(BDCOM followed by three digits): ");
                scanf("%[^\n]s", student_id);
                if(Student_ID_Exists(student_root,student_id))
                {
                    printf("Please Enter Another ID, This ID already in use\n");
                    continue;
                }
                if(Is_Student_ID_Valid(student_id))
                {
                    break;
                }
            }


            //getchar();

            while(true)
            {
                clear_input_buffer();

                printf("Please Enter A Valid Name (Must be Less Than 20 Characters): ");
                scanf("%[^\n]s", name);
                if(strlen(name)<20)
                {
                    break;
                }
                getchar();

            }

            while(true)
            {
                clear_input_buffer();
                printf("Please Enter Gender (Male or Female): ");
                scanf("%s", gender);
                if(!strcmp(gender,"Male") || !strcmp(gender,"Female"))
                {
                    break;
                }

            }
            while(true)
            {
                printf("Please Enter Department ID (0 For No Department): ");
                scanf("%d", &department_id);
                if(Is_Department_ID_Valid(department_root,department_id) || department_id==0)
                {
                    break;
                }
                printf("Department ID invalid\n");
            }


            Add_New_Student(&student_root, student_id, name, gender, department_id);
            break;

        case 2:
            printf("Please Enter Student ID:(BDCOM followed by 3 digits): ");
            scanf("%s", student_id);
            Delete_Student(&grade_root,&student_root,student_id);
            break;

        case 3:

            printf("Please Enter Student ID: ");
            scanf("%s", student_id);

            while(true)
            {
                clear_input_buffer();
                printf("Please Enter New Department ID (0 For No Department): ");
                scanf("%d", &department_id);
                if(Is_Department_ID_Valid(department_root,department_id) || department_id==0)
                {
                    break;
                }
                printf("Department ID invalid\n");
            }


            while(true)
            {
                clear_input_buffer();
                //getchar();
                printf("Please Enter A New Student Name (Must be Less Than 20 Characters): ");
                scanf("%[^\n]s", name);
                if(strlen(name)<20)
                {
                    break;
                }

            }
            Update_Student(student_root,student_id,name,department_id);
            break;

        case 4:
            Display_All_Student(student_root,department_root,grade_root);
            break;

        case 5:
            return;

        default:
            printf("Please Enter Number Between 1 to 5\n");
            break;

        }


    }
    while(true);   // Exit when option is 5
}

/*
What the function does: This function implements a menu-driven interface for managing grades.
                        It displays a menu with options to add, delete, update, and display grades,
                        as well as an option to exit the menu.

                        - Option 1: Allows the user to add a new grade by entering the student ID (in the format BDCOM followed by 3 digits),
                          English, History, and Math marks. Validates that marks are within the range 0-100.
                        - Option 2: Allows the user to delete a grade by entering the student ID.
                        - Option 3: Allows the user to update a grade by entering the student ID and providing new English, History,
                          and Math marks. Validates that marks are within the range 0-100.
                        - Option 4: Displays all grades currently stored in the system.
                        - Option 5: Exits the menu and returns to the caller function.

                        The function uses scanf for input handling and interacts with functions like Add_New_Grade,
                        Delete_Grade, Update_Grade, and Display_All_Grade to perform respective actions on the grade linked list (grade_root).

Return Type: The function does not return a value. It continuously loops until the user chooses to exit (option 5).
*/

void Grade_Menu()
{
    int option;
    char student_id[20];
    int English,History,Math;
    char input[4];
    do
    {
        printf("\n");
        printf("  **************************************************\n");
        printf("  *                                                *\n");
        printf("  *                Grade Management                *\n");
        printf("  *                                                *\n");
        printf("  **************************************************\n");
        printf("  *                                                *\n");
        printf("  *   1. Add Grade                                 *\n");
        printf("  *                                                *\n");
        printf("  *   2. Delete Grade                              *\n");
        printf("  *                                                *\n");
        printf("  *   3. Update Grade                              *\n");
        printf("  *                                                *\n");
        printf("  *   4. Display All Grades                        *\n");
        printf("  *                                                *\n");
        printf("  *   5. Exit                                      *\n");
        printf("  *                                                *\n");
        printf("  **************************************************\n");


        printf("Please Enter Your Choice: ");
        clear_input_buffer();
        scanf("%[^\n]s",input);
        if((option = is_valid_number(input))==-1)
        {
            printf("Please Enter Choice Between 1 to 5\n");
            continue;
        }

        switch(option)
        {
        case 1:

            printf("Please Enter Student ID(BDCOM followed by 3 digits): ");
            scanf("%s", student_id);


            while(true)
            {
                clear_input_buffer();
                printf("Please Enter English Marks(0-100): ");
                scanf("%[^\n]s", input);
                English=is_valid_number(input);
                if(English>=0 && English<=100)
                {
                    break;
                }
                printf("Invalid Marks For English\n");

            }
            while(true)
            {
                clear_input_buffer();
                printf("Please Enter History Marks(0-100): ");
                scanf("%[^\n]s", input);
                History=is_valid_number(input);
                if(History>=0 && History<=100)
                {
                    break;
                }
                printf("Invalid Marks For History\n");
            }
            while(true)
            {
                clear_input_buffer();
                printf("Please Enter Math Marks(0-100): ");
                scanf("%[^\n]s", input);
                Math=is_valid_number(input);
                if(Math>=0 && Math<=100)
                {
                    break;
                }

                printf("Invalid Marks For Math\n");

            }

            Add_New_Grade(student_root,&grade_root,student_id,English,History,Math);
            break;

        case 2:
            printf("Please Enter Student ID(BDCOM followed by 3 digits): ");
            scanf("%s", student_id);
            Delete_Grade(&grade_root, student_id);
            break;

        case 3:
            printf("Please Enter Student ID(BDCOM followed by 3 digits): ");
            scanf("%s", student_id);

            while(true)
            {
                clear_input_buffer();
                printf("Please Enter English Marks(0-100): ");
                scanf("%[^\n]s", input);
                English=is_valid_number(input);
                if(English>=0 && English<=100)
                {
                    break;
                }
                printf("Invalid Marks For English\n");

            }
            while(true)
            {
                clear_input_buffer();
                printf("Please Enter History Marks(0-100): ");
                scanf("%[^\n]s", input);
                History=is_valid_number(input);
                if(History>=0 && History<=100)
                {
                    break;
                }
                printf("Invalid Marks For History\n");
            }
            while(true)
            {
                clear_input_buffer();
                printf("Please Enter Math Marks(0-100): ");
                scanf("%[^\n]s", input);
                Math=is_valid_number(input);
                if(Math>=0 && Math<=100)
                {
                    break;
                }

                printf("Invalid Marks For Math\n");

            }

            Update_Grade(student_root,grade_root,student_id,English,History,Math);
            break;

        case 4:
            Display_All_Grade(student_root,grade_root);
            break;
        case 5:
            return;
        default:
            printf("Please Enter Option Between 1 to 5\n");
            break;
        }
    }
    while(true);   // Exit when option is 5
}



/*
What the function does: This function implements the main menu of a management system for departments, students, and grades.
                        It displays a menu with options to manage departments, students, and grades, save data to files,
                        and exit the program.

                        - Option 1: Calls the Department_Menu function to manage departments.
                        - Option 2: Calls the Student_Menu function to manage students.
                        - Option 3: Calls the Grade_Menu function to manage grades.
                        - Option 4: Saves all data (students, departments, grades) to respective text files ("Database/student.txt",
                          "Database/department.txt", "Database/grade.txt") using functions like saveStudent_Info,
                          saveDepartment_Info, and saveGrade_Info.
                        - Option 5: Exits the program.
                        The function uses scanf for input handling and continuously loops until the user chooses to exit (option 5).

Return Type: The function does not return a value. It serves as the main control loop for the program, coordinating interactions
             between the user and various management functionalities.
*/


void Ranking_Menu()
{
    int option;
    // Buffer to store user input
    char input[3];
    do
    {
        printf("\n");
        printf("  **************************************************\n");
        printf("  *                                                *\n");
        printf("  *                  Ranking MENU                  *\n");
        printf("  *                                                *\n");
        printf("  **************************************************\n");
        printf("  *                                                *\n");
        printf("  *   1. Ranking In School                         *\n");
        printf("  *                                                *\n");
        printf("  *   2. Ranking In Department                     *\n");
        printf("  *                                                *\n");
        printf("  *   3. Exit                                      *\n");
        printf("  *                                                *\n");
        printf("  **************************************************\n");

        printf("\n");


        clear_input_buffer();
        printf("Please Enter Your Choice : ");
        scanf("%[^\n]s",input);

        if((option=is_valid_number(input))==-1)
        {
            printf("Please Enter Option Between 1 to 3\n");
            continue;
        }

        switch(option)
        {
        case 1:
            rank_root=NULL;

            Student_Traverse(&rank_root,student_root,grade_root,department_root);
            Display_Rank_Student(rank_root);

            break;
        case 2:
            rank_root=NULL;
            Student_Traverse(&rank_root,student_root,grade_root,department_root);
            Display_Department_Rank(rank_root);
            break;
        case 3:
            return;
        default:
            printf("Please Enter Option Between 1 to 3\n");

        }

    }
    while(true);
}

int check=0;
void Main_Menu()
{
    int option;
    // Buffer to store user input
    char input[3];

    do
    {
        printf("\n");
        printf("  **************************************************\n");
        printf("  *                                                *\n");
        printf("  *                  MAIN MENU                     *\n");
        printf("  *                                                *\n");
        printf("  **************************************************\n");
        printf("  *                                                *\n");
        printf("  *   1. Department Management                     *\n");
        printf("  *                                                *\n");
        printf("  *   2. Student Management                        *\n");
        printf("  *                                                *\n");
        printf("  *   3. Grade Management                          *\n");
        printf("  *                                                *\n");
        printf("  *   4. Save                                      *\n");
        printf("  *                                                *\n");
        printf("  *   5. Ranking                                   *\n");
        printf("  *                                                *\n");
        printf("  *   6. Exit                                      *\n");
        printf("  *                                                *\n");
        printf("  **************************************************\n");

        printf("\n");
        if(!check)
        {
            printf("Please Press Enter Enter To Get Started\n");
            check++;
        }

        clear_input_buffer();
        printf("Please Enter Your Choice : ");
        scanf("%[^\n]s",input);

        if((option=is_valid_number(input))==-1)
        {
            printf("Please Enter Option Between 1 to 6\n");
            continue;
        }

        switch(option)
        {
        case 1:
            Department_Menu();
            break;
        case 2:
            Student_Menu();
            break;
        case 3:
            Grade_Menu();
            break;
        case 4:
            saveStudent_Info("Database/student.txt");
            saveDepartment_Info("Database/department.txt");
            saveGrade_Info("Database/grade.txt");
            break;

        case 5:
            Ranking_Menu();
            break;

        case 6:
            return;
        default:
            printf("Please Enter Option Between 1 to 6\n");
            break;
        }
    }
    while(true);

}
int main()
{

    readDepartment_Info("Database/department.txt");
    readStudent_Info("Database/student.txt");
    readGrade_Info("Database/grade.txt");
    sleep(1);
    Main_Menu();
    return 0;
}
