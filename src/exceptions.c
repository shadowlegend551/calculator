#include <stdlib.h>
#include <stdio.h>

#include "../include/exceptions.h"

void throw(exception instance)
{
    char* message = instance.message;

    switch(instance.criticality)
    {
        case WARNING:
            printf("\nWarning: %s. Program execution continued.\n", message);            
            break;

        case ASK_CONFIRMATION:
            printf("\nWarning: %s. Continuing execution might be fatal.\nDo you still want to continue? (y=yes): ", message);
            
            if(getchar() == 'y')
            {
                printf("Execution continued.\n");
            }
            else
            {
                printf("Program terminated with exit code 1.\n");
                exit(1);
            }
            break;

        case FATAL_ERROR:
            printf("\nFatal error: %s.\nProgram terminated with exit code 1.\n", message);
            exit(1);
            break;
    }
}

