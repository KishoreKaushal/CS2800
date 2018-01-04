/********************************************************/
/*	Name 		:	Kaushal Kishore						*/
/*	RollNo		:	111601008							*/
/*	FileName	:	stack.h								*/
/********************************************************/

/* Use Makefile to compile the program. */

#include<stdio.h>
#include<stdlib.h>
#include "list.h"

typedef struct list stack;          /* Stack implementation using linked list */

void initialize_stack(stack *stk);  /* Initializes the stack */
void push(stack *stk , void *data);  /* Pushes the data in the top of the stack */
void pop(stack *stk);                /* Pop the top data out of the stack */
node *get_top_node(stack *stk);     /* Returns the pointer to the top node */
int stack_empty(stack *stk);        /* Returns 1 if the stack is empty */
void clear_stack(stack *stk);       /* Clear the memory allocated to the stack */
void push_int(stack *stk , int data);   /* Pushes an integer data into the stack */
int pop_int(stack *stk);                /* Return and Pop the integer data on the top of the stack */