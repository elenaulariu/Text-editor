#include "stack.h"
#include "double_linked_list.h"
#include "commands.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Executa comanda save, salvand o copie a textului, copie ce va fi afisata in fisierul "editor.out".
void save(List *text, List *saved_text)
{
    destroy_list(saved_text);
    copy_list(text, saved_text);
}

// Executa comanda quit, afisand textul salvat.
void quit(List *saved_text)
{
    print_list(saved_text);
}

// Executa comanda backspace (echivalenta cu comanda de stergere a elementului din lista plasat inaintea cursorului).
char backspace(List *text, ListNode *cursor)
{
    delete (text, cursor);
}

// Plaseaza cursorul inaintea primului element de pe linia indicata.
void gotoline(List *text, ListNode *cursor, int line)
{
    cursor->next = text->head;
    cursor->prev = NULL;
    int currentline = 1;
    if (line == 1)
    {
        return;
    }
    else
    {
        ListNode *current = text->head;
        while (current != NULL)
        {
            if (current->value == '\n')
            {
                currentline++;
                if (currentline == line)
                {
                    cursor->next = current->next;
                    cursor->prev = current;
                    return;
                }
            }
            current = current->next;
        }
    }
}

// Sterge toate elementele plasate pe aceeasi linie cu cursorul (pana la intalnirea caracterului "\n").
void deleteline(List *text, ListNode *cursor)
{
    while (cursor->next->value != '\n')
    {
        deleteafter(text, cursor);
    }
    deleteafter(text, cursor);
}

// Plaseaza cursorul dupa al "car"-lea caracter de pe linia respectiva.
void gotocharacter(List *text, ListNode *cursor, int car)
{
    int i;
    for (i = 0; i < car; i++)
    {
        cursor->prev = cursor->prev->next;
        cursor->next = cursor->next->next;
    }
}

// Echivalentul comenzii delete (fara argument), sterge caracterul aflat imediat dupa cursor.
char deletechar(List *text, ListNode *cursor)
{
    return deleteafter(text, cursor);
}

// Inlocuieste prima aparitie de dupa cursor a cuvantului vechi cu cel nou.
int replace(List *text, ListNode *cursor, char *oldword, char *newword)
{
    ListNode *current = cursor->next;
    int length = strlen(oldword), i, ok = 0;
    while (current != NULL)
    {
        // Cauta prima aparitie a cuvantului.
        if (current->value != oldword[0])
        {
            current = current->next;
        }
        else
        {
            ok = 1;
            ListNode *temp = current;
            for (i = 0; i < length; i++)
            {
                if (temp->value == oldword[i])
                {
                    temp = temp->next;
                }
                else
                    ok = 0;
            }
            // Daca cuvantul a fost gasit se sterge din text.
            if (ok == 1)
            {
                cursor->next = current;
                cursor->prev = current->prev;
                for (i = 0; i < length; i++)
                {
                    deleteafter(text, cursor);
                }
                // Se insereaza in locul vechiului cuvant, cuvantul nou.
                length = strlen(newword);
                for (i = 0; i < length; i++)
                {
                    insertaftercursor(text, newword[i], cursor);
                }
                break;
            }
            current = current->next;
        }
    }
    return ok;
}

// Sterge prima aparitie de dupa cusor a cuvantului.
int deleteword(List *text, ListNode *cursor, char *word)
{
    ListNode *current = cursor->next;
    int length = strlen(word), i, ok = 0;
    while (current != NULL)
    {
        // Cauta prima aparitie a cuvantului.
        if (current->value != word[0])
        {
            current = current->next;
        }
        else
        {
            ok = 1;
            ListNode *temp = current;
            for (i = 0; i < length; i++)
            {
                if (temp->value == word[i])
                {
                    temp = temp->next;
                }
                else
                    ok = 0;
            }
            // Daca cuvantul a fost gasit, acesta este sters.
            if (ok == 1)
            {
                cursor->next = current;
                cursor->prev = current->prev;
                for (i = 0; i < length; i++)
                {
                    deleteafter(text, cursor);
                }
                break;
            }
            current = current->next;
        }
    }
    return ok;
}

// Sterge un rand, daca acesta este gol.
void deleteblankline(List *text)
{
    ListNode *current = text->head, *temp = malloc(sizeof(ListNode));
    while (current != NULL)
    {
        if (current->value == '\n' && current->next->value == '\n')
        {
            temp->prev = current;
            temp->next = current->next;
            current = current->next;
            deleteafter(text, temp);
            break;
        }
        current = current->next;
    }
    free(temp);
}

// Gaseste pozitia cursorului in text si o adauga intr-o lista.
void findcursorpos(List *text, ListNode *cursor, List *position)
{
    ListNode *temp = text->head;
    int pos = 0, line = 1;
    if (text->head == cursor->next)
    {
        insert(position, '0');
        insert(position, ' ');
        insert(position, '1');
        insert(position, '\n');
    }
    else
    {
        while (temp != NULL)
        {
            if (temp->next == cursor->next)
            {
                insert(position, '0' + pos);
                insert(position, ' ');
                insert(position, '0' + line);
                insert(position, '\n');
                return;
            }
            temp = temp->next;
            pos++;
            if (temp->value == '\n')
            {
                pos = 0;
                line++;
            }
        }
    }
}