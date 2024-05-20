#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/tokenizer.h"
#include "../include/constants.h"
#include "../include/conversions.h"
#include "../include/exceptionslib.h"
#include "../include/functionscore.h"
#include "../include/isin.h"

int NULL_TERMINATOR_HOLDER = 1;

Token* tokenize_number(char** input_string)
{
    int token_length = 0;

    if((*input_string)[0] == '-')
        token_length++;

    while(is_in((*input_string)[token_length], numbers))
        token_length++;

    char* token_value = malloc(token_length+NULL_TERMINATOR_HOLDER);
    if(!token_value)
        throw(memory_allocation_error);

    strncpy(token_value, *input_string, token_length);
    token_value[token_length] = '\0';

    Token* return_token = init_token(NUMBER, stod(token_value));
    free(token_value);

    *input_string += token_length;
    return return_token;
}


Token* tokenize_constant(char** input_string)
{
    int constant_length = 0;

    while(is_in((*input_string)[constant_length], upper_case_alphabet))
        constant_length++;

    char* token_value = malloc(constant_length+NULL_TERMINATOR_HOLDER);
    if(!token_value)
        throw(memory_allocation_error);

    strncpy(token_value, *input_string, constant_length);
    token_value[constant_length] = '\0';

    double constant_value = get_constant_value(token_value);

    free(token_value); token_value = NULL;

    *input_string += constant_length;
    return init_token(NUMBER, constant_value);
}


Token* tokenize_operator(char* input_string, char** offset)
{
    int token_length = 0;

    while(is_in(input_string[token_length], operators))
        token_length++;
    *offset += token_length;

    char* token_value = malloc(token_length+NULL_TERMINATOR_HOLDER);
    if(!token_value)
        throw(memory_allocation_error);

    strncpy(token_value, input_string, token_length);
    token_value[token_length] = '\0';

    Token* return_token = init_token(OPERATOR, token_value);
    return return_token;
}


Token* tokenize_parenthesis(char parenthesis, char** offset)
{
    char* token_value = malloc(2);
    if(!token_value)
        throw(memory_allocation_error);

    (*offset)++;

    if(parenthesis == '(')
    {
        token_value = "(\0";
        return init_token(LEFT_PAREN, token_value);
    }

    // If parenthesis is not left parenthesis, it must be right.
    token_value = ")\0";
    return init_token(RIGHT_PAREN, token_value);
}


Token* tokenize_function(char* input_string, char** offset)
{
    int function_name_length = 0;

    while(input_string[function_name_length] != '(')
        function_name_length++;

    char* function_name = malloc(function_name_length+NULL_TERMINATOR_HOLDER);
    if(!function_name)
        throw(memory_allocation_error);

    strncpy(function_name, input_string, function_name_length);
    function_name[function_name_length] = '\0';

    MathFunctionPointer function_pointer = get_function_pointer(function_name);
    if(function_pointer == NULL)
        return NULL;
    free(function_name); function_name = NULL;

    // Skip the first parenthesis.
    int function_args_base = function_name_length + 1;
    int args_length = 0;


    // Get the arguments.
    while(input_string[function_args_base+args_length] != ')')
        args_length++;

    char* function_args = malloc(args_length+NULL_TERMINATOR_HOLDER);
    if(!function_args)
        throw(memory_allocation_error);

    strncpy(function_args, input_string+function_args_base, args_length);
    function_args[args_length] = '\0';

    // Skip right parenthesis.
    function_args_base += 1;

    double* args_pointer = parse_args(function_args);

    free(function_args); function_args = NULL;
    *offset += function_args_base + args_length;

    return init_token(FUNCTION, function_pointer, args_pointer);
}


Queue* tokenize(char* input_string)
{
    int string_length = strlen(input_string);
    Queue* output_queue = init_queue();
    Token* current_token;
    int whitespace_amount;
    int offset = 0;

    while(*input_string)
    {
        // Skip whitespaces.
        if(*input_string == ' ')
        {
            input_string += 1;
            continue;
        }

        // If token is a numeric literal.
        else if(is_in(*input_string, numbers) || *input_string == '-')
        {
            current_token = tokenize_number(&input_string);

            if(current_token->value.number < 0)
                qpush(init_token(OPERATOR, "+"), output_queue);
        }

        // If token is an operator.
        else if(is_in(*input_string, upper_case_alphabet))
            current_token = tokenize_constant(&input_string);

        // If token is an operator.
        else if(is_in(*input_string, operators))
            current_token = tokenize_operator(input_string, &input_string);

        // If token is a parenthesis.
        else if(is_in(*input_string, parentheses))
            current_token = tokenize_parenthesis(*input_string, &input_string);

        // Tokenize a function.
        else if(is_in(*input_string, lower_case_alphabet))
        {
            current_token = tokenize_function(input_string, &input_string);
            if(!current_token->value.function.function)
                return NULL;
        }

        else
            return NULL;

        qpush(current_token, output_queue);
    }

    return output_queue;
}

