#include "conversions.h"
#include "evaluator.h"
#include "exceptions/exceptionslib.h"
#include "functions.h"
#include "parser.h"
#include "readline.h"
#include "token.h"
#include "tokenizer.h"
#include "tokenqueue.h"
#include "tokenstack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    Token* token;
    char* input_string;
    
    while(1)
    {
        printf("> ");
        input_string = readline();
        if(!(*input_string)) { continue; }
        
        if(!strcmp(input_string, "exit"))
        {
            printf("Exiting...\n");
            return 0;
        }
        
        Queue* tokenized = tokenize(input_string);
        free(input_string); input_string = NULL;
        
        if(!tokenized)
        {
            printf("Invalid token in expression.\n");
            continue;
        }
        
        Queue* rpn = generate_rpn(tokenized);
        if(!rpn)
        {
            printf("Invalid expression.\n");
            continue;
        }
        
        // Deletes exess + if first element in rpn is a negative number.
        if(rpn->length > 1 && rpn->queue[1]->type == OPERATOR)
        {
            for(int i = 1; i < rpn->length-1; i++)
            {
                rpn->queue[i] = rpn->queue[i+1];
            }
            rpn = realloc(rpn, sizeof(Token)*rpn->length-1);
            rpn->length--;
        }
        token = evaluate_rpn(rpn);

        printf("%f\n", token->value.number);
        
        qdelete(&tokenized);
        qdelete(&rpn);
    }
}
