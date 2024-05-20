#include <stdlib.h>
#include <string.h>

include "../include/tokenstack.h"
#include "../include/exceptionslib.h"

// Initializes an empty stack.
Stack* init_stack(void)
{
    Stack* new_stack = malloc(sizeof(Stack));
    if(!new_stack) { throw(memory_allocation_error); }

    new_stack->stack = malloc(sizeof(Token**));
    if(!new_stack->stack) { throw(memory_allocation_error); }

    new_stack->length = 0;
    
    return new_stack;
}


// Pushes a value onto the stack.
void spush(Token* value, Stack* stack)
{
    stack->stack[stack->length] = value;
    stack->length++;

    stack->stack = realloc(stack->stack, sizeof(Token**)*stack->length+1);
    if(!stack->stack) { throw(memory_reallocation_error); }
}


// Pops the topmost value off the stack.
Token* spop(Stack* stack)
{
    if(!stack->length) { return NULL; }

    stack->length--;
    Token* return_token = stack->stack[stack->length];

    stack->stack = realloc(stack->stack, sizeof(Token**)*stack->length+1);
    if(!stack->stack) { throw(memory_reallocation_error); }

    return return_token;
}


// Deletes a stack instance safely.
void sdelete(Stack** stack)
{
    for(int i = 0; i < (*stack)->length; i++)
    {
        free((*stack)->stack[i]); (*stack)->stack[i] = NULL;
    }
    free((*stack)->stack); (*stack)->stack = NULL;
    free(*stack); *stack = NULL;
}

