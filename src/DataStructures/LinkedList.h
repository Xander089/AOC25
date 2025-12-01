#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

#include "Common.h"

typedef struct {
    Node *head;
} SinglyList;

void list_init(SinglyList *L);
void list_free(SinglyList *L);

void list_insert_front(SinglyList *L, int value);
void list_insert_back(SinglyList *L, int value);

Node* list_search(SinglyList *L, int value);
int   list_delete(SinglyList *L, int value); /* returns 1 if deleted */

#endif
