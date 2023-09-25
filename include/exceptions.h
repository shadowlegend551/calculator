#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H


// Exception types:
//     WARNING: only prints a warning that something is wrong.
//     ASK_CONFIRMATION: asks if the user wants to continue,
//     if not, terminate the program with exit code 1
//     FATAL_ERROR: Prints an error message and terminates the
//     Program with exit code 1.
typedef enum exception_type
{
    WARNING,
    ASK_CONFIRMATION,
    FATAL_ERROR
} exception_type;

// Can be thrown. Criticality defines the action to be taken
// and message what to output in case of exception.
typedef struct exception
{
    exception_type criticality;
    char* message;
    
} exception;

// Takes in a variable of type exception and prints some
// info about the exception. Might terminate the program
// depending on the value of instance's critiality member.
void throw(exception instance);

#endif
