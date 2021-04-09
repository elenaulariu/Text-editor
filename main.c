#include "double_linked_list.h"
#include "stack.h"
#include "commands.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *fin;
    fin=fopen("editor.in","rt");
    char c, *s=malloc(100*sizeof(char));
    int l, p, nc,i;
    List *text=init_list();
    List *savedtext=init_list();
    List *newtext=init_list();
    ListNode *cursor=malloc(sizeof(ListNode));
    Stack *undo=init_stack();
    Stack *redo=init_stack();
    cursor->next=NULL;
    cursor->prev=text->tail;
    cursor->value=0;
    c=fgetc(fin);
    while(c!=':') {
        insert(text, c);
        c=fgetc(fin);
    }
    ListNode* lastinsert=text->head;
    fgets(s, 100, fin);
    while(fgets(s, 100, fin)){
        printf("%s", s);
        if(strncmp(s, "::i", 3)==0) {
            {   
                while(lastinsert!=text->tail)
                    lastinsert=lastinsert->next;
            }
            push(undo, s);
            c=fgetc(fin);
            while(c!=':') {
                if(cursor->next!=NULL && c=='\n') {
                    c=fgetc(fin);
                }
                else {
                    insertaftercursor(text, c, cursor);
                    insert(newtext, c); }
                c=fgetc(fin);
            }
            fgets(s, 100, fin);
        }
        if (strcmp(s, "s\n")==0){
            save(text, savedtext);
            destroy_list(newtext);
            delete_stack(undo);
            delete_stack(redo);
            cursor->prev=text->tail;
            cursor->next=NULL;
        }
        if (strcmp(s, "q\n")==0){
            quit(savedtext);
            break;
        }
        if (strncmp(s, "gl ", 3)==0) {
            l=s[3]-'0';
            gotoline(text, cursor, l);
            push(undo, s);
        }
        if (strncmp(s, "dl", 2)==0) {
            if(s[2]==' ') {
                l=s[3]-'0';
                gotoline(text, cursor, l);
            }
            deleteline(text, cursor);
            push(undo, s);
        }
        if (strncmp(s, "gc", 2)==0) {
            p=s[3]-'0';
            if(s[4]==' ') {
                l=s[5]-'0';
                gotoline(text, cursor, l);
            }
            gotocharacter(text, cursor, p);
            printf("%c", cursor->next->value);
            printf("%c", cursor->prev->value);
            push(undo, s);
        }
        if(strcmp(s, "b\n")==0){
            backspace(text, cursor);
            push(undo, s);
        }
        if(strncmp(s, "d", 1)==0) {
            if(s[1]==' ') {
                nc=s[2]-'0';
                for(i=0; i<nc; i++)
                    deletechar(text, cursor);
                push(undo, s);
            }
            if(s[1]=='\n') {
                deletechar(text, cursor);
                push(undo, s);
            }
        }
        if(strncmp(s, "re ", 3)==0) {
            int k=0;
            i=3;
            char *oldword=malloc(100*sizeof(char)), *newword=malloc(100*sizeof(char));
            while(s[i]!=' ') {
                oldword[k]=s[i];
                i++;
                k++;
            }
            oldword[k]='\0';
            i++;
            k=0;
            while(s[i]!='\n') {
                newword[k]=s[i];
                i++;
                k++;
            }
            newword[k]='\0';
            replace(text, cursor, oldword, newword);
            free(oldword);
            free(newword);
        }
         if(strncmp(s, "ra ", 3)==0) {
            int k=0;
            i=3;
            cursor->next=text->head;
            cursor->prev=NULL;
            char *oldword=malloc(100*sizeof(char)), *newword=malloc(100*sizeof(char));
            while(s[i]!=' ') {
                oldword[k]=s[i];
                i++;
                k++;
            }
            oldword[k]='\0';
            i++;
            k=0;
            while(s[i]!='\n') {
                newword[k]=s[i];
                i++;
                k++;
            }
            newword[k]='\0';
            while(replace(text, cursor, oldword, newword)==1);
            free(oldword);
            free(newword);
        }
        if(strncmp(s, "dw ", 3)==0) {
            int k=0;
            i=3;
            char *word=malloc(100*sizeof(char));
            while(s[i]!='\n') {
                word[k]=s[i];
                i++;
                k++;
            }
            word[k]='\0';
            deleteword(text, cursor, word);
            free(word);
        }
        if(strncmp(s, "da ", 3)==0) {
            int k=0;
            i=3;
            cursor->next=text->head;
            cursor->prev=NULL;
            char *word=malloc(100*sizeof(char));
            while(s[i]!='\n') {
                word[k]=s[i];
                i++;
                k++;
            }
            word[k]='\0';
            while(deleteword(text, cursor, word)==1);
            free(word);
            deleteblankline(text);
        }
        if(strcmp(s, "u\n")==0) {
            char *command=malloc(100*sizeof(char));
            strcpy(command, top(undo));
            push(redo, command);
            pop(undo);
            if(strncmp(command, "::i", 3)==0) {
                while(cursor->prev!=lastinsert) {
                    backspace(text, cursor);
                }
            }
            free(command);
        }
        if(strcmp(s, "r\n")==0) {
            char *command=malloc(100*sizeof(char));
            strcpy(command, top(redo));
            pop(redo);
            if(strncmp(command, "::i", 3)==0) {
                ListNode *it = newtext->head;
                for (; it != NULL; it = it->next)
                    insert(text, it->value);
            }
            free(command);
        }
    }
    free(cursor);
    destroy_list(text);
    destroy_list(savedtext);
    destroy_list(newtext);
    delete_stack(undo);
    delete_stack(redo);
    free(text);
    free(savedtext);
    free(newtext);
    free(undo);
    free(redo);
    free(s);
    fclose(fin);
}