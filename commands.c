#include "queue.h"
#include "stack.h"
#include "double_linked_list.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void save(List *text, List *saved_text) {
    copy_list(text, saved_text);
}

void quit(List *saved_text) {
    print_list(saved_text);
}

void backspace(List *text, ListNode *cursor) {
    delete(text, cursor);
}

void gotoline(List *text, ListNode *cursor, int line) {
    int currentline=1;
    if(line==1)  cursor->next=text->head;
    else {
        ListNode *current=text->head;
        while(current!=NULL){
            if(current->value=='\n'){
                currentline++;
                if(currentline==line) {
                    cursor->next=current->next;
                    cursor->prev=current;
                    break;
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

void undo_comm(List *text, Stack *undo, Stack *redo, ListNode *cursor) {
    char *command=malloc(100*sizeof(char));
    strcpy(command,top(undo));
    pop(undo);
    push(redo, command);
    if (strcmp(command, "::i\n")==0) {
        deleteline(text, cursor);
    }
    free(command);
}