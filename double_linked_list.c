#include "double_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

// Initializeaza o lista dublu inlantuita.
List *init_list() {
    List *list=malloc(sizeof(List));
    list->head=NULL;
    list->tail=NULL;
    return list;
    return NULL;
}

// Returneaza 1 daca lista este goala, 0 in caz contrar.
int is_empty(List *list) {
    if(list->head==NULL && list->tail==NULL)
        return 1;
    return 0;
}

// Returneaza 1 daca elementul se afla in lista, sau 0 in caz contrar.
int contains(List *list, T value) {
    ListNode *temp=list->head;
    while(temp!=NULL) {
        if(temp->value==value)
            return 1;
        temp=temp->next;
    }
    return 0;
}

// Returneaza lungimea listei
int get_length(List *list) {
    int length=0;
    ListNode *current=list->head;
    while (current!=NULL) {
        length++;
        current=current->next;
    }
    if (length)
        return length;
    return 0;
}

// Insereaza un nou element la finalul listei.
void insert(List *list, T value) {
    ListNode *newNode = malloc (sizeof(ListNode));
    newNode->value=value;
    newNode->next=NULL;
    newNode->prev=NULL;
    if(list->head==NULL && list->tail==NULL) {
        list->head=newNode;
        list->tail=newNode;
    }
    else {
        newNode->prev=list->tail;
        list->tail->next=newNode;
        list->tail=newNode;
    }
}

// Insereaza un nou element astfel incat lista sa ramana in continuare sortata.
void insert_in_order(List *list, T value) {
    ListNode *newNode = malloc (sizeof(ListNode));
    newNode->value=value;
    newNode->next=NULL;
    newNode->prev=NULL;
    if(list->head==NULL && list->tail==NULL) {
        list->head=newNode;
        list->tail=newNode;
    }
    else {
        if(list->head->value>newNode->value) {
            newNode->next=list->head;
            newNode->next->prev=newNode;
            list->head=newNode;
        }
        else if(list->tail->value<newNode->value) {
            newNode->prev=list->tail;
            newNode->prev->next=newNode;
            list->tail=newNode;
        }
            else {
                ListNode *current=list->head;
                while(current->next!=NULL && current->next->value<newNode->value)
                    current=current->next;
                newNode->next=current->next;
                newNode->next->prev=newNode;
                current->next=newNode;
                newNode->prev=current;
            }
    }
}

// Sterge si dezaloca din memorie elementul din lista aflat inaintea cursorului. 
void delete(List *list, ListNode *cursor) {
    ListNode *temp;
    if(list->head==cursor->prev) {
        temp=list->head;
        list->head=list->head->next;
        list->head->prev=NULL;
        cursor->prev=NULL;
        free(temp);
    }
    else {
        ListNode *curent = list->head;
        while(curent->next!=NULL) {
            if(curent->next==cursor->prev) {
                cursor->prev=cursor->prev->prev;
                if(curent->next==list->tail) {
                    temp=list->tail;
                    list->tail->next=NULL;
                    curent->next=NULL;
                    list->tail=list->tail->prev;
                    free(temp);
                    break;
                }
                else {
                temp=curent->next;
                curent->next=curent->next->next;
                curent->next->prev=curent;
                free(temp);
                break; }
            }
            else curent=curent->next;
        }
    }
}

//Sterge si dezaloca din lista elementul aflat dupa cursor
void deleteafter(List *list, ListNode *cursor) {
    ListNode *temp;
    if(list->head==cursor->next) {
        temp=list->head;
        list->head=list->head->next;
        list->head->prev=NULL;
        free(temp);
    }
    else {
        ListNode *curent = list->head;
        while(curent->next!=NULL) {
            if(curent->next==cursor->next) {
                if(curent->next==list->tail) {
                    temp=list->tail;
                    list->tail->next=NULL;
                    curent->next=NULL;
                    cursor->next=curent->next;
                    list->tail=list->tail->prev;
                    free(temp);
                    break;
            }
            else {
                temp=curent->next;
                curent->next=curent->next->next;
                curent->next->prev=curent;
                cursor->next=curent->next;
                free(temp);
                break; }
            }
            else curent=curent->next;
        }
    }
}

// Sterge si dezaloca din memorie toate elementele din lista.
void destroy_list(List *list) {
    ListNode *temp;
    while(list->head!=NULL) {
        if(list->head==list->tail) {
            temp=list->tail;
            list->tail=NULL;
            list->head=NULL;
            free(temp);
        }
        else{
            temp=list->head;
            list->head=list->head->next;
            free(temp); }
    }
}

void copy_list(List *list, List *copy) {
    for (ListNode *it = list->head; it != NULL; it = it->next) {
        insert(copy, it->value);
    }
}

void print_list(List *list) {
    FILE *f;
    f=fopen("editor.out", "wt");
    for (ListNode *it = list->head; it != NULL; it = it->next) {
        fputc(it->value, f);
    }
    fclose(f);
}

void print_list_reversed(List *list) {
    for (ListNode *it = list->tail; it != NULL; it = it->prev) {
        printf("%c->", it->value);
    }
    printf("NULL\n");
}