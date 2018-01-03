#include<stdio.h>
#include<stdlib.h>
#include "list.h"

typedef struct list stack;          /* Stack implementation using linked list */

void initialize_stack(stack *stk);  /* Initializes the stack */
int push(stack *stk , void *data);  /* Pushes the data in the top of the stack */
int pop(stack *stk);                /* Pop the top data out of the stack */
node *get_top_node(stack *stk);     /* Returns the pointer to the top node */
int stack_empty(stack *stk);        /* Returns 1 if the stack is empty */
void clear_stack(stack *stk);       /* Clear the memory allocated to the stack */
