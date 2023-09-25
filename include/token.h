#ifndef TOKEN_H
#define TOKEN_H

typedef enum TokenType
{
    NUMBER,
    OPERATOR,
    LEFT_PAREN,
    RIGHT_PAREN,
    FUNCTION,
} TokenType;

// Function is a pointer to a function. args gets passed to function.
// The length of args must be determined in function.
// In variable argument functions the amount of args is the
// first value in args. (i.e. sum function)
typedef struct FunctionContainer
{
    double (*function)(double*);
    double* args;
} FunctionContainer;

typedef union TokenValue
{
    double number;
    char* string;
    FunctionContainer function;
    
} TokenValue;

typedef struct Token
{
    TokenType type;
    TokenValue value;
} Token;

Token* init_token(TokenType type, ...);

#endif