#include<stdio.h>
#include "Error.h"


/*
Parameters:
- ptr: Pointer to check for error condition (typically a memory allocation result).
- message: Error message to display if ptr is NULL.

What the function does:
Checks if ptr is NULL. If ptr is NULL, prints the error message provided in 'message'
to the standard output and returns true (1). If ptr is not NULL, returns false (0)
indicating no error.

Return Type: bool
- Returns true (1) if ptr is NULL (indicating an error condition), otherwise returns false (0).
*/

bool Error_Message(void * ptr, char * message)
{
    if(!ptr)
    {
        printf("%s\n",message);
        return 1;
    }
    return 0;
}
