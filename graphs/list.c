#include<stdio.h>
#include<stdlib.h>
#include "list.h"

void pop_front(list* lst) {
    removeNode(lst, lst->front);
}

void pop_back(list* lst) {
    removeNode(lst , lst->back);
}

void initializeList(list *lst){
    lst->front = NULL;
    lst->back = NULL;
    lst->size = 0;
}

int push_front(list* lst, void* data){
    node *nd = (node*)malloc(sizeof(node));
    if(nd == NULL) return 0;
    nd->data = data;
    if(lst->front == NULL){
        lst->back = nd;
        nd->next = NULL;
    } else {
        nd->next = lst->front;
    }
    lst->front = nd;
    lst->size++;
    return 1;
}

int push_back(list* lst, void* data){
    node *nd = (node*)malloc(sizeof(node));
    if(nd == NULL) return 0;
    nd->data = data;
    nd->next = NULL;
    if(lst->front == NULL ){
        lst->front = nd;
    } else {
        lst->back->next = nd;
    }
    lst->back = nd;
    lst->size++;
    return 1;
}

void removeNode(list *lst, node *nd) {
    void *data = nd->data;
    if (nd == lst->front) {
        if (lst->front->next == NULL) {
            lst->front = lst->back = NULL;
        } else {
            lst->front = lst->front->next;
        }
    } else {
        node *tmp = lst->front;
        while (tmp != NULL && tmp->next != nd) {
            tmp = tmp->next;
        }
        if (tmp != NULL) {
            tmp->next = nd->next;
        }
    }
    lst->size--;
    free(data);
    free(nd);
}

int listEmpty(const list *lst) {
    return (lst->front == NULL);
}

void clearList(list *lst) {
    while(!listEmpty(lst)){
        removeNode(lst, lst->front);
    }
}

node *getNode(const list *lst, COMPARE compare, void *data){
    node *nd = lst->front;
    while(nd != NULL ){
        if(compare(nd->data, data) == 0){
            return nd;
        }
        nd = nd->next;
    }
    return NULL;
}

void displayList(const list *lst , DISPLAY display){
    //printf("Linked List\n");
    node *current = lst->front;
    while(current != NULL){
        display(current->data);
        current = current->next;
    }
}
