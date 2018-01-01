#include<stdio.h>
#include<stdlib.h>
#include "stack.h"

/* returns 1 if the stk s StkEmpty */
int stkEmpty(const stack *stk) {
    return (stk->top == NULL);
}

/* Initializes the stk */
void initializeStack(stack *stk){
    stk->top = NULL;
    stk->bottom = NULL;
    stk->size = 0;
}

/* push data onto the stk */
int push(stack *stk, void *data){
    node *newNode = (node *)malloc(sizeof(node));
    if(newNode == NULL ) return FAILED;
    newNode->data = data;
    if(stk->top == NULL ) {
        newNode->next = NULL;
        stk->bottom = newNode;
    } else {
        newNode->next = stk->top;
    }
    stk->top = newNode;
    stk->size += 1;
    return SUCCESS;
}


void *pop(stack *stk) {
    node *nd = stk->top ;
    if(nd == NULL) {
        printf("Stack StkEmpty\n");
        return NULL;
    } else if (nd == stk->bottom) {
        stk->top = stk->bottom = NULL;
        void *data = nd->data;
        free(nd);
        stk->size-=1;
        return data;
    } else {
        stk->top = stk->top->next;
        void *data = nd->data;
        free(nd);
        stk->size-=1;
        return data;
    }
}

void clearStack(stack *stk){
    node *nd;
    nd  = stk->top;
    while(1){
        if(nd == NULL ) {
            break;
        }
        stk->top = stk->top->next;
        void *data= nd->data;
        free(data);
        free(nd);
        nd = stk->top;
    }
    initializeStack(stk);
}
