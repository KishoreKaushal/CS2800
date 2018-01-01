#include<stdio.h>
#include<stdlib.h>

#ifndef STACK_H
#define STACK_H

#define FAILED 0
#define SUCCESS 1

typedef void (*DISPLAY)(void*);         /* DISPLAY: type cast a function to void(*)(void*) */
typedef int (*COMPARE)(void* , void*);  /* COMPARE: type cast a function to int(*)(void*, void*) */

#ifndef NODE_H
#define NODE_H

typedef struct node{
    void *data;
    struct node *next;
} node;

#endif  // NODE_H

typedef struct stack{
    node *top;
    node *bottom;
    int size;
} stack;

void initializeStack(stack *) ;               /* Initializes Stack */
void *pop(stack *);                           /* Pops an element out of the stk from the top */
int push(stack *, void *);                    /* Pushes an element on the top of the stk */
void clearStack(stack *);                   /* Silently destroy the whole stk */
int stkEmpty(const stack *);                /* returns 1 if stk is stkEmpty */

#endif // STACK_H