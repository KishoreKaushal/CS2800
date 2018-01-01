#include<stdio.h>
#include<stdlib.h>

#ifndef LIST_H
#define LIST_H

#define FAILED 0
#define SUCCESS 1


typedef void (*DISPLAY)(void*);         /* DISPLAY: type cast a function to void(*)(void*) */
typedef int (*COMPARE)(void* , void*);  /* COMPARE: type cast a function to int(*)(void*, void*) */

/* ---------- SINGLY LINKED LIST -------------------*/

#ifndef NODE_H
#define NODE_H

typedef struct node{
    void *data;
    struct node *next;
} node;

#endif // NODE_H

typedef struct list{
    node *front;
    node *back;
    int size;
} list;

void initializeList(list*);                /* Initializes the linked lst */
int push_front(list*, void*);                 /* Adds data to the linked lists's front */
int push_back(list*, void*);                 /* Adds data to the linked lst's back */
void pop_front(list*);                      /* removes an element from the front of the list */
void pop_back(list *);                      /* removes an element from the back of the list */

void removeNode(list*, node*);               /* Removes a list from the linked lst */
node *getNode(const list*, COMPARE , void*);   /* Returns a pointer to the list containing a specific data item */
void displayLinkedList(const list*, DISPLAY);    /* Displays the linked lst */
int listEmpty(const list*); /*Returns 1 if lst is empty */
void clearList(list*); /* Free the allocated linked lst from the memory.*/

#endif // LIST_H