#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

// Initializeaza o coada. 
Queue* init_queue()
{
    Queue* q=malloc(sizeof(Queue));
    q->front=NULL;
    q->back=NULL;
    q->size=0;
    return q;
}

// Returneaza 1 daca coada este goala si 0 in caz contrar. 
int is_empty_queue(Queue *q)
{
    if(q->size==0) 
        return 1;
    return 0;
}

// Returneaza numarul de elemente din coada.
int queue_size(Queue *q)
{
    return q->size;
}

// Adauga un element in coada.
void enqueue(Queue *q, double x) 
{
    Node *newNode = malloc (sizeof(Node));
    newNode->value=x;
    newNode->next=NULL;
    if(q->front==NULL && q->back==NULL) {
        q->front=newNode;
        q->back=newNode;
    }
    else {
        q->back->next=newNode;
        q->back=newNode;
    }
    q->size++;
}

// Sterge si dezaloca elementul de la finalul cozii. (Intoarce 1 daca operatia a reusit si 0 in caz contrar) 
int dequeue(Queue *q)
{
    if(q->front==NULL) return 0;
    if(q->front==q->back) {
        free(q->front);
        q->front=NULL;
        q->back=NULL;
        q->size==0;
    }
    else {
        Node *temp=q->front;
        q->front=q->front->next;
        free(temp);
        q->size--;
    }
    return 1;
}

// Returneaza elementul din varful cozii. 
double front(Queue *q) 
{
    if(q->front==NULL) return 0;
    return q->front->value;
}

// Afiseaza elementele din coada.
void print_queue(Queue *q)
{
    if (!q)
        return;
        
    printf("[");
    for (Node *it = q->front; it != NULL; it = it->next) {
        printf("%lf ", it->value);
    }
    printf("]");
}