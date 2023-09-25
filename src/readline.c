#include "../include/readline.h"

#include <stdio.h>
#include <stdlib.h>

char* readline(void)
{
    char* line = malloc(1);
    if(!line) { return NULL; }
    int increment = 0;
    char character;
    
    while((character = getchar()) && character != '\n')
    {
        line[increment] = character;
        increment++;
        
        line = realloc(line, increment+1);
        if(!line) { return NULL; }
    }
    
    line[increment] = '\0';
    return line;
}
