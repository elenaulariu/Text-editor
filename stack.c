#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

// Initializeaza o stiva. 
Stack* init_stack()
{
    Stack* s=malloc(sizeof(Stack));
    s->size=0;
    s->top=NULL;
    return s;
}

// Returneaza 1 daca stiva este goala si 0 in caz contrar.
int is_empty_stack(Stack *s)
{
    if(s->size==0)
        return 1;
    return 0;
}

// Returneaza numarul de elemente din stiva.
int stack_size(Stack *s)
{
    return s->size;
}

// Adauga un element in stiva. 
void push(Stack *s, char* x)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->value=x;
    newNode->next=s->top;
    s->top=newNode;
    s->size++;
}

// Sterge (si dezaloca) elementul din varful stivei. (Intoarce 1 daca operatia a reusit si 0 in caz contrar) 
int pop(Stack *s)
{
    Node *temp;
    if(s->top==NULL) return 0;
    temp=s->top;
    s->top=s->top->next;
    free(temp);
    s->size--;
    return 1;
}

//Sterge (si dezaloca) toate elementele din stiva
void delete_stack(Stack *s){
    while(s->size!=0) 
        pop(s);
}

// Returneaza elementul din varful stivei. 
char* top(Stack *s)
{
    if(s->top==NULL) return 0;
    return s->top->value;
}

void print_stack(Stack *s)
{
    if (!s)
        return;

    printf("[");
    for (Node *it = s->top; it != NULL; it = it->next) {
        printf("%s ", it->value);
    }
    printf("]");
}