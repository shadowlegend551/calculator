#include "../include/functions.h"
#include "../include/constants.h"
#include "../include/conversions.h"
#include "../include/exceptionslib.h"
#include "../include/isin.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* When a function is encountered in tokenizer,
* get_function_pointer is called. It returns
* a pointer to the function, which corresponds
* to the input string.
* Then the arguments are parsed in parse_args
* and are then put into a FunctionContainer
* defined in token.h
*/


double absolute_value(double* number_array)
{
    double number = number_array[1];
    double result = number < 0 ? number * -1 : number;

    return result;
}


double average(double* number_array)
{
    double result = sum(number_array);

    // number_array[0] is the number of arguments.
    return result / number_array[0];
}


double deg_to_rad(double* number_array)
{
    double degrees = number_array[1];
    return degrees * (PI / 180);
}


double modulo(double* number_array)
{
    double result = number_array[1];
    double subtractable = number_array[2];

    while(result - subtractable >= 0) { result -= subtractable; }

    return result;
}


double rad_to_deg(double* number_array)
{
    double radians = number_array[1];
    return radians * (180 / PI);
}


double square_root(double* number_array)
{
    int RESOLUTION = 20; 
    double original_number = number_array[1];

    // Often used roots.
    if(original_number == 0.5) { return 0.707106781186547; }
    if(original_number == 2.0) { return 1.414213562373095; }
    if(original_number == 3.0) { return 1.732050807568877; }
    if(original_number == 4.0) { return 2.0; }
    if(original_number == 5.0) { return 2.236067977499789; }
    
    double iterable = original_number;

    for(int i = 0; i < RESOLUTION; i++)
    {
        iterable = (iterable + original_number/iterable) / 2;
    }

    return iterable;
}


double sum(double* number_array)
{
    double argument_amount = number_array[0];
    double result = 0;

    for(int i = 1; i <= argument_amount; i++)
    {
        result += number_array[i];
    }
    
    return result;
}


MathFunctionPointer get_function_pointer(char* function_name)
{
    if(!strcmp(function_name, "abs")) { return &absolute_value; }
    else if(!strcmp(function_name, "avg")) { return &average; }
    else if(!strcmp(function_name, "deg")) { return &rad_to_deg; }
    else if(!strcmp(function_name, "mod")) { return &modulo; }
    else if(!strcmp(function_name, "rad")) { return &deg_to_rad; }
    else if(!strcmp(function_name, "sqrt")) { return &square_root; }
    else if(!strcmp(function_name, "sum")) { return &sum; }
    
    return NULL;
}


double* parse_args(char* arguments_string)
{
    char NULL_TERMINATOR_HOLDER = '\0';
    char* current_arg;
    double* args_array = malloc(sizeof(double));
    double arg_value;
    int args_array_length = 1;
    int argument_length;

    while(*arguments_string)
    {
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

            args_array_length++;
            args_array = realloc(args_array, args_array_length);
            args_array[args_array_length-1] = arg_value;

            arguments_string += argument_length;
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

            args_array_length++;
            args_array = realloc(args_array, args_array_length);
            args_array[args_array_length-1] = arg_value;

            arguments_string += argument_length;
        }

        arguments_string++;
    }

    args_array[0] = args_array_length-1;
    return args_array;
}
