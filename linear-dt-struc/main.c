#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "list.h"
#include "queue.h"

void displayInt(int *ptr) {
    printf("%d " , *ptr);
}

int main() {
    printf("Testing Linked List\n");
    // testing the linked function
    list lst;
    int *ptr1; int* ptr2;
    initializeList(&lst);
    int n;
    while(scanf(" %d" , &n) , n!=-1){
        ptr1 = (int*)malloc(sizeof(int));
        ptr2 = (int*)malloc(sizeof(int));
        *ptr1 = n;
        push_back(&lst , ptr1);
        *ptr2 = n + 10;
        push_front(&lst , ptr2);
    }
    // displaying the linked list
    displayList(&lst , (DISPLAY) displayInt);
    printf("\n");
       //pop_front(&lst);
    pop_back(&lst);
    
    displayList(&lst , (DISPLAY) displayInt);
    printf("\n");
    pop_front(&lst);
    
    displayList(&lst , (DISPLAY) displayInt);
    printf("\n");
    
    clearList(&lst);
    displayList(&lst , (DISPLAY) displayInt);
    printf("\n");
    
    return 0;
}