#ifndef TOKENSTACK_H
#define TOKENSTACK_H

#include "token.h"

typedef struct Stack
{
    Token** stack;
    int length;
} Stack;

Stack* init_stack(void);

void spush(Token* value, Stack* stack_ptr);

Token* spop(Stack* stack_ptr);

void sdelete(Stack** stack);

#endif
