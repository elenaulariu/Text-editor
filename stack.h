#ifndef STACK_H_
#define STACK_H_

#ifndef NODE
#define NODE

typedef struct Node {
    char* value;
    struct Node *next;
} Node;

#endif

typedef struct {
    int size;
    Node *top;
} Stack;

// Initializeaza o stiva. 
Stack* init_stack();

// Returneaza 1 daca stiva este goala si 0 in caz contrar.
int is_empty_stack(Stack *s);

// Returneaza numarul de elemente din stiva.
int stack_size(Stack *s);

// Returneaza elementul din varful stivei. 
char* top(Stack *s);

// Adauga un element in stiva. 
void push(Stack *s, char* x);

// Sterge (si dezaloca) elementul din varful stivei. (Intoarce 1 daca operatia a reusit si 0 in caz contrar)
int pop(Stack *s);

//Sterge (si dezaloca) toate elementele din stiva
void delete_stack(Stack *s);

// Afiseaza elementele din stiva.
void print_stack(Stack *s);

#endif