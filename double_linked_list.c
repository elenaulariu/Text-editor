#include "double_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

// Initializeaza o lista dublu inlantuita.
List *init_list()
{
    List *list = malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    return list;
    return NULL;
}

// Insereaza un nou element la finalul listei.
void insert(List *list, T value)
{
    ListNode *newNode = malloc(sizeof(ListNode));
    newNode->value = value;
    newNode->next = NULL;
    if (list->head == NULL && list->tail == NULL)
    {
        newNode->prev = NULL;
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

// Insereaza un nou element dupa pozitia cursorului.
void insertaftercursor(List *list, T value, ListNode *cursor)
{
    ListNode *newNode = malloc(sizeof(ListNode));
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    if (cursor->next == NULL)
    {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
        cursor->next = NULL;
        cursor->prev = list->tail;
    }
    else if (cursor->prev == NULL)
    {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
        cursor->prev = list->head;
        cursor->next = list->head->next;
    }
    else
    {
        ListNode *temp = list->head;
        while (temp != cursor->prev)
            temp = temp->next;
        newNode->next = temp->next;
        newNode->next->prev = newNode;
        temp->next = newNode;
        newNode->prev = temp;
        cursor->prev = newNode;
        cursor->next = newNode->next;
    }
}

// Sterge si dezaloca din memorie elementul din lista aflat inaintea cursorului.
char delete (List *list, ListNode *cursor)
{
    ListNode *temp;
    char value;
    if (list->head == cursor->prev)
    {
        temp = list->head;
        value = temp->value;
        list->head = list->head->next;
        list->head->prev = NULL;
        cursor->prev = NULL;
        free(temp);
    }
    else
    {
        ListNode *curent = list->head;
        while (curent->next != NULL)
        {
            if (curent->next == cursor->prev)
            {
                cursor->prev = cursor->prev->prev;
                if (curent->next == list->tail)
                {
                    temp = list->tail;
                    value = temp->value;
                    list->tail->next = NULL;
                    curent->next = NULL;
                    list->tail = list->tail->prev;
                    free(temp);
                    break;
                }
                else
                {
                    temp = curent->next;
                    value = temp->value;
                    curent->next = curent->next->next;
                    curent->next->prev = curent;
                    free(temp);
                    break;
                }
            }
            else
                curent = curent->next;
        }
    }
    return value;
}

// Sterge si dezaloca din memerie elementul din lista aflat dupa cursor.
char deleteafter(List *list, ListNode *cursor)
{
    char value;
    ListNode *temp;
    if (list->head == cursor->next)
    {
        temp = list->head;
        value = temp->value;
        list->head = list->head->next;
        list->head->prev = NULL;
        cursor->next = list->head;
        free(temp);
    }
    else
    {
        ListNode *curent = list->head;
        while (curent->next != NULL)
        {
            if (curent->next == cursor->next)
            {
                if (curent->next == list->tail)
                {
                    temp = list->tail;
                    value = temp->value;
                    list->tail->next = NULL;
                    list->tail = list->tail->prev;
                    curent->next = NULL;
                    cursor->next = NULL;
                    free(temp);
                    break;
                }
                else
                {
                    temp = curent->next;
                    value = temp->value;
                    curent->next = curent->next->next;
                    curent->next->prev = curent;
                    cursor->next = curent->next;
                    free(temp);
                    break;
                }
            }
            else
                curent = curent->next;
        }
    }
    return value;
}

// Sterge si dezaloca din memorie ultimul element al listei.
void deletelastnode(List *list)
{
    ListNode *temp;
    if (list->head == NULL)
    {
        return;
    }
    if (list->head == list->tail)
    {
        temp = (list->head);
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        temp = list->tail;
        list->tail->next = NULL;
        list->tail = list->tail->prev;
    }
    free(temp);
}

// Sterge si dezaloca din memorie toate elementele din lista.
void destroy_list(List *list)
{
    ListNode *temp;
    while (list->head != NULL)
    {
        if (list->head == list->tail)
        {
            temp = list->tail;
            list->tail = NULL;
            list->head = NULL;
            free(temp);
        }
        else
        {
            temp = list->head;
            list->head = list->head->next;
            free(temp);
        }
    }
}

// Duplica lista.
void copy_list(List *list, List *copy)
{
    ListNode *it = list->head;
    for (; it != NULL; it = it->next)
    {
        insert(copy, it->value);
    }
}

// Afiseaza elementele din lista in fisierul "editor.out".
void print_list(List *list)
{
    FILE *f;
    f = fopen("editor.out", "wt");
    ListNode *it = list->head;
    for (; it != NULL; it = it->next)
    {
        fputc(it->value, f);
    }
    fclose(f);
}