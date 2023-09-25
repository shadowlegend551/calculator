#include "../include/token.h"
#include "../include/exceptionslib.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Token* init_token(TokenType type, ...)
{
    va_list token_value;
    va_start(token_value, type);
    
    Token* token = malloc(sizeof(Token));
    if(!token) { throw(memory_allocation_error); }

    switch(type)
    {
        case NUMBER:
            token->value.number = va_arg(token_value, double);
            break;

        case OPERATOR:
        case LEFT_PAREN:
        case RIGHT_PAREN:
            char* original_string = va_arg(token_value, char*);
            char* value_ptr = malloc(strlen(original_string)+1);
            if(!value_ptr) { throw(memory_allocation_error); }
            
            strcpy(value_ptr, original_string);
            token->value.string = value_ptr;
            
            break;
        
        case FUNCTION:
            token->value.function.function = va_arg(token_value, double (*)(double*));
            token->value.function.args = va_arg(token_value, double*);

            break;
    }

    token->type = type;
    va_end(token_value);
    
    return token;
}