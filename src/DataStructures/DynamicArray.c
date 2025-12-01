#include <stdio.h>
#include <stdlib.h>
#include "DynamicArray.h"

static void da_resize(DynamicArray *A, int new_capacity) {
    printf("Resizing from %d to %d\n", A->capacity, new_capacity);
    int *new_data;
    int i;

    new_data = (int*) malloc(sizeof(int) * new_capacity);
    if (!new_data) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (i = 0; i < A->size; i++) {
        new_data[i] = A->data[i];
    }

    free(A->data);
    A->data = new_data;
    A->capacity = new_capacity;
}

void da_init(DynamicArray *A) {
    A->capacity = 1;
    A->size = 0;
    A->data = (int*) malloc(sizeof(int) * A->capacity);

    if (!A->data) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
}

void da_free(DynamicArray *A) {
    free(A->data);
    A->data = NULL;
    A->size = 0;
    A->capacity = 0;
}

int da_get(DynamicArray *A, int index) {
    if (index < 0 || index >= A->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(1);
    }
    return A->data[index];
}

void da_set(DynamicArray *A, int index, int value) {
    if (index < 0 || index >= A->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(1);
    }
    A->data[index] = value;
}

void da_append(DynamicArray *A, int value) {
    if (A->size == A->capacity) {
        da_resize(A, A->capacity * 2);
    }
    A->data[A->size++] = value;
}



void da_insert(DynamicArray *A, int index, int value) {
    int i;

    if (index < 0 || index > A->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(1);
    }

    if (A->size == A->capacity) {
        da_resize(A, A->capacity * 2);
    }

    for (i = A->size - 1; i >= index; i--) {
        printf("Shifting index %d to index %d\n", i, i + 1);
        A->data[i + 1] = A->data[i];
    }

    A->data[index] = value;
    A->size++;
}

int da_remove(DynamicArray *A, int index) {
    int i, value;

    if (index < 0 || index >= A->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(1);
    }

    value = A->data[index];

    for (i = index; i < A->size - 1; i++) {
        A->data[i] = A->data[i + 1];
    }

    A->size--;

    if (A->size > 0 && A->size <= A->capacity / 4) {
        da_resize(A, A->capacity / 2);
    }

    return value;
}
