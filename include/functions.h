#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef double (*MathFunctionPointer)(double*);

double sum(double* number_array);

MathFunctionPointer get_function_pointer(char* function_name);

double* parse_args(char* arguments_string);

#endif
