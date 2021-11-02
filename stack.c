#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initializeaza o stiva.
Stack *init_stack()
{
    Stack *s = malloc(sizeof(Stack));
    s->size = 0;
    s->top = NULL;
    return s;
}

// Adauga un element in stiva.
void push(Stack *s, char *x)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->value = malloc(100 * sizeof(char));
    strcpy(newNode->value, x);
    newNode->next = s->top;
    s->top = newNode;
    s->size++;
}

// Sterge (si dezaloca) elementul din varful stivei. (Intoarce 1 daca operatia a reusit si 0 in caz contrar)
int pop(Stack *s)
{
    Node *temp;
    if (s->top == NULL)
        return 0;
    temp = s->top;
    s->top = s->top->next;
    free(temp->value);
    free(temp);
    s->size--;
    return 1;
}

//Sterge (si dezaloca) toate elementele din stiva
void delete_stack(Stack *s)
{
    while (s->size != 0)
        pop(s);
}

// Returneaza elementul din varful stivei.
char *top(Stack *s)
{
    if (s->top == NULL)
        return 0;
    return s->top->value;
}