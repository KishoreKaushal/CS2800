#include<stdio.h>
#include<stdlib.h>
#include "list.h"
#include "stack.h"
#include "queue.h"

void display_int(int *a) { printf("%d " , *a) ; }

int main() {
    /* Testing List */
    int *ptr1 , *ptr2 ;
    puts("Testing the List:-\n");
    list lst;
    initialize_list(&lst);
    for(int i=1; i<5; i++ ){
        ptr1 = (int*)malloc(sizeof(int));
        ptr2 = (int*)malloc(sizeof(int));
        *ptr1 = i;
        *ptr2 = -i;
        push_front(&lst , ptr1);
        push_back(&lst , ptr2);
    }
    
    printf("Is list Empty: %d\nList size: %d\n", list_empty(&lst), lst.size);
    
    display_list(&lst , (DISPLAY)display_int );
    pop_back(&lst);
    display_list(&lst , (DISPLAY)display_int );
    pop_back(&lst);
    display_list(&lst , (DISPLAY)display_int );
    pop_front(&lst);
    display_list(&lst , (DISPLAY)display_int );
    pop_front(&lst);
    display_list(&lst , (DISPLAY)display_int );
    
    printf("List size: %d\n" , lst.size);
    
    clear_list(&lst);
    printf("Is list Empty: %d\nList Size: %d\n", list_empty(&lst) , lst.size);
    
    /* Testing stack */
    stack stk;
    initialize_stack(&stk);
    for(int i=1; i<5; i++ ){
        ptr1 = (int*)malloc(sizeof(int));
        ptr2 = (int*)malloc(sizeof(int));
        *ptr1 = i;
        *ptr2 = -i;
        push(&stk , ptr1);
        push(&stk , ptr2);
    }
    
    printf("Is stack Empty: %d\nstack size: %d\n", stack_empty(&stk), stk.size);
    
    display_list(&stk , (DISPLAY)display_int );
    pop(&stk); pop(&stk); pop(&stk);
    display_list(&stk , (DISPLAY)display_int );
    
    printf("stack size: %d\n" , stk.size);
    
    clear_stack(&stk);
    printf("Is stack Empty: %d\nstack Size: %d\n", stack_empty(&stk) , stk.size);
    
    /* Testing queue */
    queue q;
    initialize_queue(&q);
    for(int i=1; i<5; i++ ){
        ptr1 = (int*)malloc(sizeof(int));
        ptr2 = (int*)malloc(sizeof(int));
        *ptr1 = i;
        *ptr2 = -i;
        enqueue(&q , ptr1);
        enqueue(&q , ptr2);
    }
    
    printf("Is queue Empty: %d\nqueue size: %d\n", queue_empty(&q), q.size);
    
    display_list(&q , (DISPLAY)display_int );
    dequeue(&q); dequeue(&q); dequeue(&q);
    display_list(&q , (DISPLAY)display_int );
    
    printf("queue size: %d\n" , q.size);
    
    clear_queue(&q);
    printf("Is queue Empty: %d\nqueue Size: %d\n", queue_empty(&q) , q.size);
    return 0;
}