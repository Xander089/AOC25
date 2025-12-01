#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

typedef struct {
    int *data;
    int size;
    int capacity;
} DynamicArray;

void da_init(DynamicArray *A);
void da_free(DynamicArray *A);

int da_get(DynamicArray *A, int index);
void da_set(DynamicArray *A, int index, int value);

void da_append(DynamicArray *A, int value);
void da_insert(DynamicArray *A, int index, int value);
int  da_remove(DynamicArray *A, int index);

#endif
