#include<stdio.h>
#include<stdlib.h>
#include "list.h"
#include "queue.h"

/* Initialize the queue */
void initialize_queue(queue *q) {
    initialize_list(q);
}

/* Enqueue a data in the queue */
void enqueue(queue *q, void *data) {
    push_back(q , data);
}

/* enqueue an integer data into the stack */
void enqueue_int(queue *q , int data) {
	int *ptr = (int*)malloc(sizeof(int));
	*ptr = data;
	enqueue(q , ptr);
}

/* Dequeue a data from the queue */
void dequeue(queue *q) {
    pop_front(q);
}

/* Returns and Dequeue an integer */
int dequeue_int(queue *q) {
    int data = *(int*)(q->front->data);
    dequeue(q);
    return data;
}

/* Get front node of the queue */
node* get_front(queue *q) {
    return q->front;
}

/* Get the back node of the queue */
node* get_back(queue *q) {
    return q->back;
}

/* Returns 1 if the queue is empty */
int queue_empty(queue *q){
    return (q->front == NULL);
}

/* Free the memory allocated to the queue */
void clear_queue(queue *q) {
    clear_list(q);
}
