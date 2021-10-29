#ifndef TECHNOPARK_ARRAY_H
#define TECHNOPARK_ARRAY_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Array {
    int* array;
    size_t size;
    size_t factual_size;
} Array;

void alloc_int_array(Array* arr, const size_t size) {
    arr->size = size;
    arr->factual_size = 0;
    arr->array = (int*)calloc(arr->size, sizeof(int));
}

void free_int_array(const Array* arr) {
    free(arr->array);
}

void print_array(const Array* arr) {
    for (size_t i = 0; i < arr->factual_size; i++)
        printf("Array[%zu] = %d\n", i, arr->array[i]);
}

void resize(Array* arr, const size_t new_size) { //
    Array tmp;
    alloc_int_array(&tmp, arr->size);
    tmp.factual_size = arr->factual_size;
    for (size_t i = 0; i < tmp.factual_size; i++) {
        tmp.array[i] = arr->array[i];
    }

    free_int_array(arr);
    alloc_int_array(arr, new_size);
    if (new_size >= tmp.size) {
        for (int i = 0; i < tmp.factual_size; i++)
            arr->array[i] = tmp.array[i];
        arr->factual_size = tmp.factual_size;
    }
    else {
        for (int i = 0; i < arr->size; i++)
            arr->array[i] = tmp.array[i];
        arr->factual_size = arr->size;
    }

    free_int_array(&tmp);
}

void add(Array* arr, int el) {
    if (arr->factual_size == arr->size)
        resize(arr, arr->size / 2 + 1);
    arr->array[arr->factual_size++] = el;
}

#endif //TECHNOPARK_ARRAY_H