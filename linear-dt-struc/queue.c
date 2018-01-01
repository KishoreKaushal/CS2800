#include<stdio.h>
#include<stdlib.h>
#include "queue.h"

/* Initializes Queue */
void initializeQueue(queue * q) {
    q->front = NULL ;
    q->back = NULL ;
    q->size = 0;
}

/* Adds an element to the Queue(FIFO)  */
int enqueue(queue *q, void *data ) {
    node *newNode = (node*) malloc(sizeof(node));
    if (newNode == NULL ) return FAILED;
    newNode->data = data ;
    newNode->next = NULL;
    if(q->front == NULL) {
        q->front = q->back = newNode;
    } else {
        newNode->next = q->front;
        q->front = newNode;
    }
    q->size++;
    return SUCCESS;
}

/* Removes an element from the q at front position*/
void *dequeue(queue * q){
    if( queueEmpty(q) ) {
        return NULL;
    }
    node *tmp = q->front;
    void *data = q->front->data;
    if(q->front == q->back ){
        q->front = q->back = NULL;
    } else {
        q->front = q->front->next;
    }
    free(tmp);
    q->size--;
    return data;
}


/* Destroy the whole Queue */
void clearQueue(queue *q) {
    node *tmp = q->front;
    while (q->front != NULL ){
        q->front = q->front->next;
        free(tmp);
        tmp = q->front;
    }
    q->front = q->back = NULL;
    initializeQueue(q);
}

/* returns 1 if the q is empty */
int queueEmpty(const queue * q ){
    return (q->front == NULL);
}
