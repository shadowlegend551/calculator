#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/functions.h"
#include "../include/functionscore.h"
#include "../include/constants.h"
#include "../include/conversions.h"
#include "../include/exceptionslib.h"
#include "../include/isin.h"

/*
* When a function is encountered in tokenizer,
* get_function_pointer is called. It returns
* a pointer to the function, which corresponds
* to the input string.
* Then the arguments are parsed in parse_args
* and are then put into a FunctionContainer
* defined in token.h
*/


MathFunctionPointer get_function_pointer(char* function_name)
{
    if(!strcmp(function_name, "abs"))
        return &absolute_value;

    else if(!strcmp(function_name, "avg"))
        return &average;

    else if(!strcmp(function_name, "deg"))
        return &rad_to_deg;

    else if(!strcmp(function_name, "fac"))
        return &factorial;

    else if(!strcmp(function_name, "mod"))
        return &modulo;

    else if(!strcmp(function_name, "rad"))
        return &deg_to_rad;

    else if(!strcmp(function_name, "sqrt"))
        return &square_root;

    else if(!strcmp(function_name, "sum"))
        return &sum;

    return NULL;
}


// number_array[0] is the number of arguments.
double* parse_args(char* arguments_string)
{
    char NULL_TERMINATOR_HOLDER = '\0';
    char* current_arg;
    int args_array_length = 3;
    int i = 1;
    double* args_array = malloc(sizeof(double) * args_array_length);
    double arg_value;
    int argument_length;

    while(*arguments_string)
    {
        if(*arguments_string == ' ')
        {
            arguments_string++;
            continue;
        }

        if(is_in(*arguments_string, numbers) || *arguments_string == '-')
        {
            argument_length = 0;

            if(*arguments_string == '-') { argument_length++; }

            while(is_in(arguments_string[argument_length], numbers))
            {
                argument_length++;
            }

            current_arg = malloc(argument_length+NULL_TERMINATOR_HOLDER);
            if(!current_arg) { throw(memory_allocation_error); }

            strncpy(current_arg, arguments_string, argument_length);
            current_arg[argument_length] = '\0';

            arg_value = stod(current_arg);
        }

        else if(is_in(*arguments_string, upper_case_alphabet))
        {
            argument_length = 0;

            while(is_in(arguments_string[argument_length], upper_case_alphabet))
            {
                argument_length++;
            }

            current_arg = malloc(argument_length+NULL_TERMINATOR_HOLDER);
            if(!current_arg) { throw(memory_allocation_error); }

            strncpy(current_arg, arguments_string, argument_length);
            current_arg[argument_length] = '\0';


            arg_value = get_constant_value(current_arg);
        }

        args_array[i] = arg_value;
        i++;

        if(i == args_array_length)
        {
            args_array_length *= 2;
            args_array = realloc(args_array, args_array_length*sizeof(double));
        }

        arguments_string += argument_length;
        arguments_string++;
    }

    args_array[0] = i-1;
    return args_array;
}

