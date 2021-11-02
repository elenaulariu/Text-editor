#include "double_linked_list.h"
#include "stack.h"
#include "commands.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    FILE *fin;
    fin = fopen("editor.in", "rt");
    char c, *s = malloc(100 * sizeof(char)), d;
    int l, p, nc, i;
    List *text = init_list();
    List *savedtext = init_list();
    List *newtext = init_list();
    List *deleted = init_list();
    List *deletedword = init_list();
    List *position = init_list();
    ListNode *cursor = malloc(sizeof(ListNode)), *find = malloc(sizeof(ListNode));
    Stack *undo = init_stack();
    Stack *redo = init_stack();
    // Plasam cursorul la sfarsitul textului.
    cursor->next = NULL;
    cursor->prev = text->tail;
    c = fgetc(fin);
    // Citim si introducem in lista textul initial.
    while (c != ':')
    {
        insert(text, c);
        c = fgetc(fin);
    }
    cursor->prev = text->tail->prev;
    ListNode *lastinsert = text->head;
    // Citim si implementam comenzile de editare ale textului.
    fgets(s, 100, fin);
    while (fgets(s, 100, fin))
    {
        // Introducem caractere in  lista dupa pozitia cursorului.
        if (strncmp(s, "::i", 3) == 0)
        {
            {
                while (lastinsert != text->tail)
                    lastinsert = lastinsert->next;
            }
            push(undo, s);
            c = fgetc(fin);
            while (c != ':')
            {
                if (cursor->next != NULL && c == '\n')
                {
                    d = fgetc(fin);
                    if (d != ':')
                    {
                        insertaftercursor(text, c, cursor);
                        insertaftercursor(text, d, cursor);
                    }
                }
                else
                {
                    insertaftercursor(text, c, cursor);
                    insert(newtext, c);
                }
                c = fgetc(fin);
            }
            fgets(s, 100, fin);
        }
        // Salveaza forma actuala a textului, intr-o lista ce va fi afisata la final.
        if (strcmp(s, "s\n") == 0)
        {
            save(text, savedtext);
            destroy_list(newtext);
            destroy_list(position);
            delete_stack(undo);
            delete_stack(redo);
            cursor->prev = text->tail;
            cursor->next = NULL;
        }
        // Afiseaza textul salvat si iese din forma de editare.
        if (strcmp(s, "q\n") == 0)
        {
            quit(savedtext);
            break;
        }
        // Muta cursorul la inceputul liniei specificate.
        if (strncmp(s, "gl ", 3) == 0)
        {
            l = s[3] - '0';
            findcursorpos(text, cursor, position);
            gotoline(text, cursor, l);
            push(undo, s);
        }
        // Sterge linia specificata, sau in cazul in care numarul liniei lipseste, sterge linia curenta.
        if (strncmp(s, "dl", 2) == 0)
        {
            if (s[2] == ' ')
            {
                l = s[3] - '0';
                gotoline(text, cursor, l);
            }
            deleteline(text, cursor);
            push(undo, s);
        }
        // Muta cursorul dupa caracterul specificat.
        if (strncmp(s, "gc", 2) == 0)
        {
            findcursorpos(text, cursor, position);
            p = s[3] - '0';
            if (s[4] == ' ')
            {
                l = s[5] - '0';
                gotoline(text, cursor, l);
            }
            gotocharacter(text, cursor, p);
            push(undo, s);
        }
        // Sterge caracterul plasat inaintea cursorului.
        if (strcmp(s, "b\n") == 0)
        {
            backspace(text, cursor);
            push(undo, s);
        }
        // Sterge un numar "nc" de caractere de dupa cursor, sau doar unul in cazul in care valoarea lui "nc" lipseste (si salveaza intr-o lista pozitia).
        if (s[0] == 'd')
        {
            findcursorpos(text, cursor, position);
            if (s[1] == ' ')
            {
                nc = s[2] - '0';
                for (i = 0; i < nc; i++)
                {
                    c = deletechar(text, cursor);
                    insert(deleted, c);
                }
                push(undo, s);
            }
            else if (s[1] == '\n')
            {
                c = deletechar(text, cursor);
                insert(deleted, c);
                push(undo, s);
            }
        }
        // Inlocuieste prima aparitie a unui cuvant dat cu altul (si salveaza pozitia la care a fost inlocuit).
        if (strncmp(s, "re ", 3) == 0)
        {
            int k = 0;
            i = 3;
            find->prev = cursor->prev;
            find->next = cursor->next;
            char *oldword = malloc(100 * sizeof(char)), *newword = malloc(100 * sizeof(char));
            while (s[i] != ' ')
            {
                oldword[k] = s[i];
                i++;
                k++;
            }
            oldword[k] = '\0';
            i++;
            k = 0;
            while (s[i] != '\n')
            {
                newword[k] = s[i];
                i++;
                k++;
            }
            newword[k] = '\0';
            replace(text, find, oldword, newword);
            findcursorpos(text, find, position);
            push(undo, s);
            free(oldword);
            free(newword);
        }
        // Inlocuieste toate aparitiile cuvantului.
        if (strncmp(s, "ra ", 3) == 0)
        {
            int k = 0;
            i = 3;
            findcursorpos(text, cursor, position);
            cursor->next = text->head;
            cursor->prev = NULL;
            char *oldword = malloc(100 * sizeof(char)), *newword = malloc(100 * sizeof(char));
            while (s[i] != ' ')
            {
                oldword[k] = s[i];
                i++;
                k++;
            }
            oldword[k] = '\0';
            i++;
            k = 0;
            while (s[i] != '\n')
            {
                newword[k] = s[i];
                i++;
                k++;
            }
            newword[k] = '\0';
            while (replace(text, cursor, oldword, newword) == 1)
                ;
            push(undo, s);
            deletelastnode(position);
            l = position->tail->value - '0';
            deletelastnode(position);
            deletelastnode(position);
            p = position->tail->value - '0';
            deletelastnode(position);
            gotoline(text, cursor, l);
            gotocharacter(text, cursor, p);
            free(oldword);
            free(newword);
        }
        // Sterge prima aparitie a cuvantului.
        if (strncmp(s, "dw ", 3) == 0)
        {
            find->prev = cursor->prev;
            find->next = cursor->next;
            int k = 0;
            i = 3;
            char *word = malloc(100 * sizeof(char));
            insert(deletedword, '\n');
            while (s[i] != '\n')
            {
                word[k] = s[i];
                insert(deletedword, s[i]);
                i++;
                k++;
            }
            word[k] = '\0';
            if (deleteword(text, find, word) == 0)
            {
                find->next = text->head;
                find->prev = NULL;
                deleteword(text, find, word);
            }
            push(undo, s);
            free(word);
        }
        // Sterge toate aparitiile cuvantului.
        if (strncmp(s, "da ", 3) == 0)
        {
            int k = 0;
            i = 3;
            findcursorpos(text, cursor, position);
            cursor->next = text->head;
            cursor->prev = NULL;
            char *word = malloc(100 * sizeof(char));
            while (s[i] != '\n')
            {
                word[k] = s[i];
                i++;
                k++;
            }
            word[k] = '\0';
            while (deleteword(text, cursor, word) == 1)
                ;
            push(undo, s);
            free(word);
            deletelastnode(position);
            l = position->tail->value - '0';
            deletelastnode(position);
            deletelastnode(position);
            p = position->tail->value - '0';
            deletelastnode(position);
            gotoline(text, cursor, l);
            gotocharacter(text, cursor, p);
            ListNode *it = text->head;
            for (; it->next != NULL; it = it->next)
            {
                if (it->value == '\n' && it->next->value == '\n')
                    deleteblankline(text);
            }
        }
        // Anuleaza ultima comanda efectuata.
        if (strcmp(s, "u\n") == 0)
        {
            char *command = malloc(100 * sizeof(char));
            strcpy(command, top(undo));
            push(redo, command);
            pop(undo);
            // Sterge textul inserat.
            if (strncmp(command, "::i", 3) == 0)
            {
                while (cursor->prev != lastinsert)
                {
                    backspace(text, cursor);
                }
            }
            // Insereaza toate caracterele sterse.
            if (strncmp(command, "d", 1) == 0)
            {
                deletelastnode(position);
                l = position->tail->value - '0';
                deletelastnode(position);
                deletelastnode(position);
                p = position->tail->value - '0';
                deletelastnode(position);
                gotoline(text, cursor, l);
                gotocharacter(text, cursor, p);
                if (command[1] == '\n')
                {
                    insertaftercursor(text, deleted->tail->value, cursor);
                    deletelastnode(deleted);
                }
                else if (command[1] == ' ')
                {
                    nc = command[2] - '0';
                    for (i = 0; i < nc; i++)
                    {
                        insertaftercursor(text, deleted->tail->value, cursor);
                        cursor->next = cursor->prev;
                        cursor->prev = cursor->prev->prev;
                        deletelastnode(deleted);
                    }
                }
            }
            // Muta cursorul la pozitia anterioara mutarii.
            if (strncmp(command, "gl ", 3) == 0)
            {
                deletelastnode(position);
                l = position->tail->value - '0';
                deletelastnode(position);
                deletelastnode(position);
                p = position->tail->value - '0';
                deletelastnode(position);
                gotoline(text, cursor, l);
                gotocharacter(text, cursor, p);
            }
            // Muta cursorul la pozitia anterioara mutarii.
            if (strncmp(command, "gc ", 3) == 0)
            {
                deletelastnode(position);
                l = position->tail->value - '0';
                deletelastnode(position);
                deletelastnode(position);
                p = position->tail->value - '0';
                deletelastnode(position);
                gotoline(text, cursor, l);
                gotocharacter(text, cursor, p);
            }
            // Reintroduce cuvantul sters.
            if (strncmp(command, "dw ", 3) == 0)
            {
                while (deletedword->tail->value != '\n')
                {
                    insertaftercursor(text, deletedword->tail->value, find);
                    find->next = find->prev;
                    find->prev = find->prev->prev;
                    deletelastnode(deletedword);
                }
                deletelastnode(deletedword);
            }
            // Inlocuieste cuvantul inlocuit cu cuvantul precedent inlocuirii.
            if (strncmp(command, "re ", 3) == 0)
            {
                deletelastnode(position);
                l = position->tail->value - '0';
                deletelastnode(position);
                deletelastnode(position);
                p = position->tail->value - '0';
                deletelastnode(position);
                gotoline(text, find, l);
                gotocharacter(text, find, p);
                int k = 0;
                i = 3;
                char *oldword = malloc(100 * sizeof(char)), *newword = malloc(100 * sizeof(char));
                while (command[i] != ' ')
                {
                    newword[k] = command[i];
                    i++;
                    k++;
                }
                newword[k] = '\0';
                i++;
                k = 0;
                while (command[i] != '\n')
                {
                    oldword[k] = command[i];
                    i++;
                    k++;
                }
                oldword[k] = '\0';
                replace(text, find, oldword, newword);
                free(oldword);
                free(newword);
            }
            free(command);
        }
        // Reaplica comanda anulata.
        if (strcmp(s, "r\n") == 0)
        {
            char *command = malloc(100 * sizeof(char));
            strcpy(command, top(redo));
            pop(redo);
            // Reintroduce textul sters prin comanda undo.
            if (strncmp(command, "::i", 3) == 0)
            {
                ListNode *it = newtext->head;
                for (; it != NULL; it = it->next)
                    insert(text, it->value);
            }
            // Sterge caracterele reintroduse prin comanda undo.
            if (command[0] == 'd')
            {
                if (command[1] == '\n')
                {
                    deletechar(text, cursor);
                }
                else if (command[1] == ' ')
                {
                    nc = command[2] - '0';
                    for (i = 0; i < nc; i++)
                        deletechar(text, cursor);
                }
            }
            // Replaseaza cursorul la inceput liniei cerute.
            if (strncmp(command, "gl ", 3) == 0)
            {
                l = command[3] - '0';
                gotoline(text, cursor, l);
            }
            // Replaseaza cursorul dupa caracterul p de pe linia l (sau de pe linia curenta in absenta lui l).
            if (strncmp(command, "gc ", 3) == 0)
            {
                p = command[3] - '0';
                if (command[4] == ' ')
                {
                    l = command[5] - '0';
                    gotoline(text, cursor, l);
                }
                gotocharacter(text, cursor, p);
            }
            // Sterge din nou prima aparitie de dupa cursor a cuvantului.
            if (strncmp(command, "dw ", 3) == 0)
            {
                int k = 0;
                i = 3;
                char *word = malloc(100 * sizeof(char));
                while (command[i] != '\n')
                {
                    word[k] = command[i];
                    i++;
                    k++;
                }
                word[k] = '\0';
                deleteword(text, find, word);
                free(word);
            }
            // Reaplica comanda replace.
            if (strncmp(command, "re ", 3) == 0)
            {
                find->next = cursor->next;
                find->prev = cursor->prev;
                int k = 0;
                i = 3;
                char *oldword = malloc(100 * sizeof(char)), *newword = malloc(100 * sizeof(char));
                while (s[i] != ' ')
                {
                    oldword[k] = s[i];
                    i++;
                    k++;
                }
                oldword[k] = '\0';
                i++;
                k = 0;
                while (s[i] != '\n')
                {
                    newword[k] = s[i];
                    i++;
                    k++;
                }
                newword[k] = '\0';
                replace(text, find, oldword, newword);
                free(oldword);
                free(newword);
            }
            free(command);
        }
    }
    free(find);
    free(cursor);
    destroy_list(text);
    destroy_list(savedtext);
    destroy_list(deletedword);
    destroy_list(newtext);
    destroy_list(deleted);
    destroy_list(position);
    delete_stack(undo);
    delete_stack(redo);
    free(text);
    free(deleted);
    free(savedtext);
    free(deletedword);
    free(position);
    free(newtext);
    free(undo);
    free(redo);
    free(s);
    fclose(fin);
}