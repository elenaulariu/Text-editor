#include "stack.h"
#include "double_linked_list.h"

#ifndef COMMANDS_H
#define COMMANDS_H

// Executa comanda save, salvand o copie a textului, copie ce va fi afisata in fisierul "editor.out".
void save(List *text, List *saved_text);

// Executa comanda quit, afisand textul salvat.
void quit(List *saved_text);

// Executa comanda backspace (echivalenta cu comanda de stergere a elementului din lista plasat inaintea cursorului).
char backspace(List *text, ListNode *cursor);

// Plaseaza cursorul inaintea primului element de pe linia indicata.
void gotoline(List *text, ListNode *cursor, int line);

// Sterge toate elementele plasate pe aceeasi linie cu cursorul (pana la intalnirea caracterului "\n").
void deleteline(List *text, ListNode *cursor);

// Plaseaza cursorul dupa al "car"-lea caracter de pe linia respectiva.
void gotocharacter(List *text, ListNode *cursor, int car);

// Echivalentul comenzii delete (fara argument), sterge caracterul aflat imediat dupa cursor.
char deletechar(List *text, ListNode *cursor);

// Inlocuieste prima aparitie de dupa cursor a cuvantului vechi cu cel nou.
int replace(List *text, ListNode *cursor, char *oldword, char *newword);

// Sterge prima aparitie de dupa cusor a cuvantului.
int deleteword(List *text, ListNode *cursor, char *word);

// Sterge un rand, daca acesta este gol.
void deleteblankline(List *text);

// Gaseste pozitia cursorului in text si o adauga intr-o lista.
void findcursorpos(List *text, ListNode *cursor, List *position);

#endif