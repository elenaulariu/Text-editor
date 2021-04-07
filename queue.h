#ifndef QUEUE_H_
#define QUEUE_H_

#ifndef NODE
#define NODE

typedef struct Node {
    double value;
    struct Node *next;
} Node;

#endif

typedef struct {
    int size;
    Node *front, *back;
} Queue;

// Initializeaza o coada.
Queue* init_queue();

// Returneaza 1 daca coada este goala si 0 in caz contrar. 
int is_empty_queue(Queue *q);

// Returneaza numarul de elemente din coada. 
int queue_size(Queue *q);

// Adauga un element in coada. (0.5 puncte)
void enqueue(Queue *q, double x);

// Sterge si dezaloca ultimul element din coada. (Intoarce 1 daca operatia a reusit si 0 in caz contrar) 
int dequeue(Queue *q);

// Returneaza elementul din varful cozii. 
double front(Queue *q);

// Afiseaza elementele din coada.
void print_queue(Queue *q);

#endif