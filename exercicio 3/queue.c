#include <stdlib.h>
#include "queue.h"

void initialize(queue *q)
{
    q->first = NULL;
    q->last = NULL;
}

void destroy(queue *q)
{
    while (!empty(q))
        pop(q);
}

void *front(queue *q)
{
    if (!empty(q))
        return q->first->data;
    return 0;
}

void push(queue *q, void *data)
{
    qnode *novo = (qnode *)malloc(sizeof(qnode));

    if (empty(q))
        q->first = novo;
    else
        q->last->next = novo;
    novo->next = NULL;
    novo->next = NULL;
    q->last = novo;
    novo->data = data;
}

void pop(queue *q)
{
    qnode *descarte;
    descarte = q->first;
    q->first = descarte->next;
    free(descarte);
}

int empty(queue *q)
{
    return q->first == 0;
}