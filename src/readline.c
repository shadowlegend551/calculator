#include "../include/readline.h"
#include <stdio.h>
#include <stdlib.h>

char* readline(void)
{
    int buffer_size = 128;
    char* buffer = malloc(buffer_size);
    if(!buffer) { return NULL; }

    int write_offset = 0;
    char character;
    char* realloc_holder;

    while((character = getchar()) && character != '\n')
    {
        if(write_offset == buffer_size)
        {
            buffer_size *= 2;
            realloc_holder = realloc(buffer, buffer_size);
            if(!realloc_holder)
            {
                free(buffer);
                return NULL;
            }
            buffer = realloc_holder;
        }

        buffer[write_offset] = character;
        write_offset++;
    }

    realloc_holder = realloc(buffer, write_offset+1);
    if(!realloc_holder)
    {
        free(buffer);
        return NULL;
    }

    buffer = realloc_holder;
    buffer[write_offset] = '\0';

    return buffer;
}
