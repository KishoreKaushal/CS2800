#include<stdio.h>
#include<stdlib.h>

#define FAILED 0
#define SUCCESS 1

#ifndef QUEUE_H
#define QUEUE_H

typedef void (*DISPLAY)(void*);         /* DISPLAY: type cast a function to void(*)(void*) */
typedef int (*COMPARE)(void* , void*);  /* COMPARE: type cast a function to int(*)(void*, void*) */

#ifndef NODE_H
#define NODE_H

typedef struct node{
    void *data;
    struct node *next;
} node;

#endif  // node

typedef struct queue {
    node *front;
    node *back;
    int size;
} queue;

void initializeQueue(queue *);                /* Initializes Queue*/
int enqueue(queue *, void *);                 /* Adds an element in the q(FIFO) */
void *dequeue(queue *);                       /* Removes an element from the q at back position*/
void clearQueue(queue *);                   /* Destroy the whole q */
int queueEmpty(const queue *);                /* returns 1 if the q is empty. */


#endif // QUEUE_H