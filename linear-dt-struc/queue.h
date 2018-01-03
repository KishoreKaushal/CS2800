#include<stdio.h>
#include<stdlib.h>
#include "list.h"

typedef struct list queue;			/* Implementing the queue by using the linked list */

void initialize_queue(queue *q);	/* Initialize the queue */
int enqueue(queue *q, void *data);	/* Enqueue a data in the queue */
int dequeue(queue *q);				/* Dequeue a data from the queue */
node* get_front(queue *q);			/* Get front node of the queue */
node* get_back(queue *q);			/* Get the back node of the queue */
int queue_empty(queue *q);			/* Returns 1 if the queue is empty */
void clear_queue(queue *q);			/* Free the memory allocated to the queue */
