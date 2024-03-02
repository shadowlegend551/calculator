#ifndef FUNCTIONSCORE_H
#define FUNCTIONSCORE_H

// Core functionality for functions.

typedef double (*MathFunctionPointer)(double*);

typedef struct FunctionContainer
{
    MathFunctionPointer function;
    double* args;

} FunctionContainer;

MathFunctionPointer get_function_pointer(char* function_name);

double* parse_args(char* arguments_string);

#endif
