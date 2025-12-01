#include "Structures.h"
#include <stdio.h>

void testStructures() {
    // Test DynamicArray
    DynamicArray arr;
    da_init(&arr);

    for (int i = 0; i < 10; i++) {
        da_append(&arr, 1+ i);
    }
    
    da_insert(&arr, 2, 9);

    for (int i = 0; i < arr.size; i++) {
        printf("%d ", da_get(&arr, i));
    }
    printf("\n");

    da_free(&arr);

    // Test SinglyList
    
    SinglyList list;
    
    list_init(&list);
    
    for (int i = 0; i < 5; i++) {
        list_insert_back(&list, i * 10);
    }

    Node *cur = list.head;
    while (cur != NULL) {
        printf("%d ", cur->value);
        cur = cur->next;
    }
    printf("\n");

    list_free(&list);

    // Test ArrayStack
    ArrayStack stack;
    as_init(&stack, 10);
    for (int i = 0; i < 5; i++) {
        as_push(&stack, i + 100);
    }

    while (!as_is_empty(&stack)) {
        printf("%d ", as_pop(&stack));
    }
    printf("\n");

    as_free(&stack);
}