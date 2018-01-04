#include<stdio.h>
#include<stdlib.h>
#include "list.h"
#include "stack.h"

/* Initializes the stack */
void initialize_stack(stack *stk) {
	initialize_list(stk);
}

/* Pushes the data in the top of the stack */
void push(stack *stk , void *data){
	push_front(stk , data);
}

/* Pushes an integer data into the stack */
void push_int(stack *stk , int data) {
	int *ptr = (int*)malloc(sizeof(int));
	*ptr = data;
	push(stk , ptr);
}

/* Pop the top data out of the stack */
void pop(stack *stk){
	pop_front(stk);
}

/* Return and Pop the integer data on the front of the stack */
int pop_int(stack *stk){
	int data = *(int*)(stk->front->data);
	pop(stk);
	return data;
}

/* Returns 1 if the stack is empty */
int stack_empty(stack *stk) {
	return (stk->front == NULL);
}

/* Clear the memory allocated to the stack */
void clear_stack(stack *stk) {
	clear_list(stk);
}

/* Returns the pointer to the top node */
node *get_top_node(stack *stk){
	if(!stack_empty(stk)){
		return stk->front;
	}
	return NULL;
}
