#ifndef TOKENQUEUE_H
#define TOKENQUEUE_H

#include "token.h"

typedef struct Queue
{
    Token** queue;
    int length;
} Queue;

Queue* init_queue(void);

void qpush(Token* value, Queue* queue);

Token* qpop(Queue* queue);

void qdelete(Queue** queue);

#endif
