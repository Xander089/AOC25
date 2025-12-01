#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

void list_init(SinglyList *L) {
    L->head = NULL;
}

void list_free(SinglyList *L) {
    Node *cur = L->head;
    Node *next;

    while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
    }

    L->head = NULL;
}

void list_insert_front(SinglyList *L, int value) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    new_node->value = value;
    new_node->next  = L->head;
    L->head = new_node;
}

void list_insert_back(SinglyList *L, int value) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    Node *cur;

    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    new_node->value = value;
    new_node->next  = NULL;

    if (L->head == NULL) {
        L->head = new_node;
        return;
    }

    cur = L->head;
    while (cur->next != NULL) {
        cur = cur->next;
    }

    cur->next = new_node;
}

Node* list_search(SinglyList *L, int value) {
    Node *cur = L->head;

    while (cur != NULL) {
        if (cur->value == value)
            return cur;
        cur = cur->next;
    }

    return NULL;
}

int list_delete(SinglyList *L, int value) {
    Node *cur = L->head;
    Node *prev = NULL;

    while (cur != NULL) {
        if (cur->value == value) {
            if (prev == NULL) {
                L->head = cur->next;
            } else {
                prev->next = cur->next;
            }
            free(cur);
            return 1; /* deleted */
        }
        prev = cur;
        cur = cur->next;
    }

    return 0; /* not found */
}
