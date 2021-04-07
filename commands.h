#include "queue.h"
#include "stack.h"
#include "double_linked_list.h"
#ifndef COMMANDS_H
#define COMMANDS_H

void save(List *text, List *saved_text);
void quit(List *saved_text);
void backspace(List *text, ListNode *cursor);
void gotoline(List *text, ListNode *cursor ,int line);
void deleteline(List *text, ListNode *cursor);
void gotocharacter(List *text, ListNode *cursor, int car);
void deletechar(List *text, ListNode *cursors);
void undo_comm(List *text, Stack *undo, Stack *redo, ListNode *cursor);

#endif