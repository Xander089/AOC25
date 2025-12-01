#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

// Array-based LIFO Stack implementation

typedef struct {
    int *data;
    int top;
    int capacity;
} ArrayStack;

void as_init(ArrayStack *S, int capacity);
void as_free(ArrayStack *S);

int  as_is_empty(ArrayStack *S);
int  as_is_full(ArrayStack *S);

void as_push(ArrayStack *S, int value);
int  as_pop(ArrayStack *S);
int  as_peek(ArrayStack *S);

#endif
