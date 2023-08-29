#include "tokenqueue.h"
#include "exceptions/exceptionslib.h"
#include "token.h"

#include <stdlib.h>
#include <string.h>

Queue* init_queue(void)
{
    Queue* new_queue = malloc(sizeof(Queue));
    if(!new_queue) { throw(memory_allocation_error); }
    
    new_queue->queue = malloc(sizeof(Token**));
    if(!new_queue->queue) { throw(memory_allocation_error); }

    new_queue->length = 0;
    
    return new_queue;
}

// Pushes a value onto the queue.
void qpush(Token* token, Queue* queue)
{
    queue->queue[queue->length] = token;
    queue->length++;
    
    queue->queue = realloc(queue->queue, sizeof(Token**)*queue->length+1);
    if(!queue->queue) { throw(memory_reallocation_error); }
}

// Pops the bottommost value off the queue.
Token* qpop(Queue* queue)
{
    if(!queue->length) { return NULL; } 
    queue->length--;
    
    Token* return_token = queue->queue[0];

    for(int i = 0; i < queue->length; i++)
    {
        queue->queue[i] = queue->queue[i+1];
    }
    
    queue->queue = realloc(queue->queue, sizeof(Token**)*queue->length+1);
    if(!queue->queue) { throw(memory_reallocation_error); }
    return return_token;
}

// Deletes a queue instance safely.
void qdelete(Queue** queue)
{
    for(int i = 0; i < (*queue)->length; i++)
    {
        if((*queue)->queue[i])
        {
            free((*queue)->queue[i]);
            (*queue)->queue[i] = NULL;
        }
    }

    if((*queue)->queue)
    {
        free((*queue)->queue);
        (*queue)->queue = NULL;
    }

    if(*queue)
    {
        free(*queue);
        *queue = NULL;
    }
}
