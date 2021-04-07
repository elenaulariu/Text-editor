#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

typedef char T;

typedef struct ListNode {
    struct ListNode *next; // pointer catre nodul urmator
    struct ListNode *prev; // pointer catre nodul precedent
    T value;
} ListNode;

typedef struct List {
    ListNode *head; // pointer catre primul nod din lista
    ListNode *tail; // pointer catre ultimul nod din lista
} List;

// Initializeaza o lista dublu inlantuita.
List *init_list();

// Returneaza 1 daca lista este goala, 0 in caz contrar. 
int is_empty(List *list);

// Returneaza 1 daca elementul se afla in lista, sau 0 in caz contrar.
int contains(List *list, T value);

// Returneaza lungimea listei
int get_length(List *list);

// Insereaza un nou element la finalul listei.
void insert(List *list, T value);

// Insereaza un nou element astfel incat lista sa ramana in continuare sortata.
void insert_in_order(List *list, T value);

// Sterge si dezaloca din memorie elementul din lista aflat inaintea cursorului.
void delete(List *list, ListNode *cursor);

//Sterge si dezaloca din lista elementul aflat dupa cursor
void deleteafter(List *list, ListNode *cursor);

// Sterge si dezaloca din memorie toate elementele din lista.
void destroy_list(List *list);

// Duplica lista.
void copy_list(List *list, List *copy);

// Afiseaza elementele din lista.
void print_list(List *list);

// Afiseaza elementele din lista in ordine inversa. 
void print_list_reversed(List *list);

#endif