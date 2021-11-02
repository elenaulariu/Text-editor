#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

typedef char T;

typedef struct ListNode
{
    struct ListNode *next; // pointer catre nodul urmator
    struct ListNode *prev; // pointer catre nodul precedent
    T value;
} ListNode;

typedef struct List
{
    ListNode *head; // pointer catre primul nod din lista
    ListNode *tail; // pointer catre ultimul nod din lista
} List;

// Initializeaza o lista dublu inlantuita.
List *init_list();

// Insereaza un nou element la finalul listei.
void insert(List *list, T value);

// Insereaza un nou element dupa pozitia cursorului.
void insertaftercursor(List *list, T value, ListNode *cursor);

// Sterge si dezaloca din memorie elementul din lista aflat inaintea cursorului.
char delete (List *list, ListNode *cursor);

// Sterge si dezaloca din memorie elementul din lista aflat dupa cursor.
char deleteafter(List *list, ListNode *cursor);

// Sterge si dezaloca din memorie ultimul element al listei.
void deletelastnode(List *list);

// Sterge si dezaloca din memorie toate elementele din lista.
void destroy_list(List *list);

// Duplica lista.
void copy_list(List *list, List *copy);

// Afiseaza elementele din lista in fisierul "editor.out".
void print_list(List *list);

#endif