#include "double_linked_list.h"
#include "stack.h"
#include "queue.h"
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
    //fgets(s, 100, fin);
    while(fgets(s, 100, fin)){
        if(strncmp(s, "::i", 3)==0) {
            push(undo, s);
            c=fgetc(fin);
            while(c!=':') {
                insert(text, c);
                c=fgetc(fin);
            }
            fgetc(fin);
            fgetc(fin);
            fgetc(fin);
        }
        if (strcmp(s, "s\n")==0){
            destroy_list(savedtext);
            save(text, savedtext);
            delete_stack(undo);
            delete_stack(redo);
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
            push(undo, s);
            if(s[2]==' ') {
                l=s[3]-'0';
                gotoline(text, cursor, l);
            }
            deleteline(text, cursor);
        }
        if (strncmp(s, "gc", 2)==0) {
            push(undo, s);
            p=s[3]-'0';
            if(s[4]==' ') {
                l=s[5]-'0';
                gotoline(text, cursor, l);
            }
            gotocharacter(text, cursor, p);
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
        print_stack(undo);
        if(strcmp(s, "u\n")==0) {
            char *command=top(undo);
            //printf("%s", command);
            if(strcmp(command, "::i\n")==0) {
                printf("da");
                push(redo, top(undo));
                pop(undo);
                
                deleteline(text, cursor);
            }
        }
        
        /*if(c=='g') {
            c=fgetc(fin);
            if(c=='l'){
                c=fgetc(fin);
                c=fgetc(fin);
                l=c-'0';
                gotoline(text,cursor,l);
            }
            else if(c=='c') {
                fgetc(fin);
                c=fgetc(fin);
                p=c-'0';
                c=fgetc(fin); 
                if(c==' '){
                    c=fgetc(fin);
                    l=c-'0';
                    gotoline(text, cursor, l);
                }
                gotocharacter(text, cursor, p);
            }
        }
        if(c=='d') {
            c=fgetc(fin);
            if(c=='l')
                {if(fgetc(fin)==' '){
                    c=fgetc(fin);
                    l=c-'0';
                    gotoline(text, cursor, l);
                }
                deleteline(text, cursor);
            }
            else if(c==' ') {
                c=fgetc(fin);
                nc=c-'0';
                for(i=0; i<nc; i++)
                    deleteafter(text, cursor);
            }
            else deletechar(text, cursor);
        }
        if(c=='b') backspace(text, cursor);
        if(c=='s') {save(text, savedtext);
            //print_list_reversed(text);
            //print_list_reversed(savedtext);
        }
        if(c=='q') {quit(savedtext);
                    break;}*/
    }
    destroy_list(text);
    destroy_list(savedtext);
    delete_stack(undo);
    delete_stack(redo);
    free(cursor);
    free(text);
    free(savedtext);
    free(undo);
    free(redo);
    free(s);
    fclose(fin);
}