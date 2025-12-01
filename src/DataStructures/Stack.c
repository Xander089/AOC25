#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

void as_init(ArrayStack *S, int capacity) {
    S->data = (int*) malloc(sizeof(int) * capacity);
    if (!S->data) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    S->capacity = capacity;
    S->top = -1;
}

void as_free(ArrayStack *S) {
    free(S->data);
    S->data = NULL;
    S->capacity = 0;
    S->top = -1;
}

int as_is_empty(ArrayStack *S) {
    return S->top == -1;
}

int as_is_full(ArrayStack *S) {
    return S->top == S->capacity - 1;
}

void as_push(ArrayStack *S, int value) {
    if (as_is_full(S)) {
        fprintf(stderr, "Stack overflow\n");
        exit(1);
    }
    S->data[++S->top] = value;
}

int as_pop(ArrayStack *S) {
    if (as_is_empty(S)) {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    return S->data[S->top--];
}

int as_peek(ArrayStack *S) {
    if (as_is_empty(S)) {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }
    return S->data[S->top];
}
