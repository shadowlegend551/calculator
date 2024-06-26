#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/evaluator.h"
#include "../include/exceptionslib.h"
#include "../include/functions.h"
#include "../include/isin.h"
#include "../include/tokenstack.h"
#include "../include/tokenqueue.h"

Token* evaluate_rpn(Queue* rpn)
{
    Stack* temp_stack = init_stack();
    double result;
    Token* current_token;
    Token* first_operand;
    Token* second_operand;
    MathFunctionPointer function;
    double* function_arguments;
    double function_result;


    while((current_token = qpop(rpn)))
    {

        switch(current_token->type)
        {
        case NUMBER:
            spush(current_token, temp_stack);
            break;


        case FUNCTION:
            function = current_token->value.function.function;
            function_arguments = current_token->value.function.args;
            result = function(function_arguments);

            spush(init_token(NUMBER, result), temp_stack);
            break;

            
        case OPERATOR:
            second_operand = spop(temp_stack);
            first_operand = spop(temp_stack);

            if(!strcmp(current_token->value.string, "+"))
            {
                result =
                first_operand->value.number
                + second_operand->value.number;
            }

            else if(!strcmp(current_token->value.string, "-"))
            {
                result =
                first_operand->value.number
                - second_operand->value.number;
            }

            else if(!strcmp(current_token->value.string, "*"))
            {
                result =
                first_operand->value.number
                * second_operand->value.number;
            }

            else if(!strcmp(current_token->value.string, "/"))
            {
                result =
                first_operand->value.number
                / second_operand->value.number;
            }

            else if(!strcmp(current_token->value.string, "^"))
            {
                result =
                pow(first_operand->value.number,
                second_operand->value.number);
            }

            free(current_token); current_token = NULL;
            free(second_operand); second_operand = NULL;
            spush(init_token(NUMBER, result), temp_stack);
            break;
        }
    }

    // Remaining token is the result.
    return spop(temp_stack);
}

