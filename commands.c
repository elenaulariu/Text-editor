#include "stack.h"
#include "double_linked_list.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void save(List *text, List *saved_text) {
    destroy_list(saved_text);
    copy_list(text, saved_text);
}

void quit(List *saved_text) {
    print_list(saved_text);
}

void backspace(List *text, ListNode *cursor) {
    delete(text, cursor);
}

void gotoline(List *text, ListNode *cursor, int line) {
    cursor->next=text->head;
    cursor->prev=NULL;
    int currentline=1;
    if(line==1)  {
        return;
    }    
    else {
        ListNode *current=text->head;
        while(current!=NULL){
            if(current->value=='\n'){
                currentline++;
                if(currentline==line) {
                    cursor->next=current->next;
                    cursor->prev=current;
                    return;
                }
            }
            current=current->next;
        }
    }
}

void deleteline(List *text, ListNode *cursor) {
    while(cursor->next->value!='\n') {
        deleteafter(text, cursor);
    }
    deleteafter(text, cursor);
}

void gotocharacter(List *text, ListNode *cursor, int car) {
    int i;
    for(i=0; i<car; i++) {
        cursor->prev=cursor->prev->next;
        cursor->next=cursor->next->next;
    }
}

void deletechar(List *text, ListNode *cursor) {
    deleteafter(text, cursor); 
}

int replace(List *text, ListNode *cursor, char *oldword, char *newword) {
    ListNode* current=cursor->next;
    int length=strlen(oldword), i, ok=0;
    while(current!=NULL){
        if(current->value!=oldword[0]){
            current=current->next;
        }    
        else {
            ok=1;
            ListNode *temp=current;
            for(i=0; i<length; i++) {
                if(temp->value==oldword[i]) {
                    temp=temp->next;
                }
                else ok=0;
            }
            if(ok==1) {
                cursor->next=current;
                cursor->prev=current->prev;
                for(i=0; i<length; i++){
                    deleteafter(text, cursor);
                }
                length=strlen(newword);
                for(i=0; i<length; i++){
                    insertaftercursor(text, newword[i], cursor);
                }
            break;
            }
            current=current->next;
        }
    }
    return ok;
}

int deleteword(List *text, ListNode *cursor, char *word) {
    ListNode* current=cursor->next;
    int length=strlen(word), i, ok=0;
    while(current!=NULL){
        if(current->value!=word[0]){
            current=current->next;
        }    
        else {
            ok=1;
            ListNode *temp=current;
            for(i=0; i<length; i++) {
                if(temp->value==word[i]) {
                    temp=temp->next;
                }
                else ok=0;
            }
            if(ok==1) {
                cursor->next=current;
                cursor->prev=current->prev;
                for(i=0; i<length; i++){
                    deleteafter(text, cursor);
                }
            break;
            }
            current=current->next;
        }
    }
    return ok;
}

void deleteblankline(List *text) {
    ListNode *current=text->head, *temp=malloc(sizeof(ListNode));
    while(current!=NULL) {
        if(current->value=='\n' && current->next->value=='\n'){
            temp->prev=current;
            temp->next=current->next;
            current=current->next;
            deleteafter(text, temp);
            break;
        }
        current=current->next;
    }
    free(temp);
}