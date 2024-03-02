#include "../include/parser.h"
#include "../include/token.h"
#include "../include/tokenqueue.h"
#include "../include/tokenstack.h"
#include "../include/tokenqueue.h"

#include <stdlib.h>
#include <string.h>

Queue* generate_rpn(Queue* input_queue)
{
    Queue* output_queue = init_queue();
    Stack* operator_stack = init_stack();
    Token* current_token;
    Token* stack_holder;

    while(current_token = qpop(input_queue))
    {
        if(current_token->type == NUMBER || current_token->type == FUNCTION)
        {
            qpush(current_token, output_queue);
        }

        else if(!strcmp(current_token->value.string, "^") || current_token->type == LEFT_PAREN)
        {
            spush(current_token, operator_stack);
        }

        else if(!strcmp(current_token->value.string, "*") || !strcmp(current_token->value.string, "/"))
        {
            while((stack_holder = spop(operator_stack)) && 
                 stack_holder->type != LEFT_PAREN &&
                 !strcmp(current_token->value.string, "+") &&
                 !strcmp(current_token->value.string, "-"))
            {
                qpush(stack_holder, output_queue);
            }

            if(stack_holder) { spush(stack_holder, operator_stack); }
            spush(current_token, operator_stack);
        }

        else if(!strcmp(current_token->value.string, "+") || !strcmp(current_token->value.string, "-"))
        {
            while((stack_holder = spop(operator_stack)) && stack_holder->type != LEFT_PAREN)
            {
                qpush(stack_holder, output_queue);
            }

            if(stack_holder) { spush(stack_holder, operator_stack); }
            spush(current_token, operator_stack);
        }

        else if(current_token->type == RIGHT_PAREN)
        {
            while((stack_holder = spop(operator_stack)) && stack_holder->type != LEFT_PAREN)
            {
                qpush(stack_holder, output_queue);
            }

            if(!stack_holder) { return NULL; }
        }
    }
    
    while((current_token = spop(operator_stack))) { qpush(current_token, output_queue); }
    
    return output_queue;
}
