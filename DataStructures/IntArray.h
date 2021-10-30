#ifndef TECHNOPARK_INTARRAY_H
#define TECHNOPARK_INTARRAY_H
#include <stdio.h>
#include <stdlib.h>

typedef struct IntArray {
    int* array;
    size_t size;
    size_t factual_size;
} IntArray;

void alloc_int_array(IntArray* arr, const size_t size) {
    arr->size = size;
    arr->factual_size = 0;
    arr->array = (int*)calloc(arr->size, sizeof(int));
}

void free_int_array(const IntArray* arr) {
    free(arr->array);
}

void print_int_array(const IntArray* arr) {
    for (size_t i = 0; i < arr->factual_size; i++)
        printf("IntArray[%zu] = %d\n", i, arr->array[i]);
}

void resize_int_array(IntArray* arr, const size_t new_size) { //
    IntArray tmp;
    alloc_int_array(&tmp, arr->size);
    tmp.factual_size = arr->factual_size;
    for (size_t i = 0; i < tmp.size; i++) {
        tmp.array[i] = arr->array[i];
    }

    free_int_array(arr);
    alloc_int_array(arr, new_size);

    if (tmp.factual_size != 0) {
        if (new_size >= tmp.size)
            for (int i = 0; i < tmp.size; i++)
                arr->array[i] = tmp.array[i];
        else
            for (int i = 0; i < arr->size; i++)
                arr->array[i] = tmp.array[i];
    }
    arr->factual_size = tmp.factual_size;

    free_int_array(&tmp);
}

void add_to_int_array(IntArray* arr, int el) {
    if (arr->factual_size == arr->size)
        resize_int_array(arr, arr->size + arr->size / 2 + 1);
    arr->array[arr->factual_size++] = el;
}

void test_int_array() {
    IntArray arr;
    alloc_int_array(&arr, 10);
    print_int_array(&arr);
    printf("IntArray size = [%zu]\tIntArray factual size = [%zu]\n\n", arr.size, arr.factual_size);

    resize_int_array(&arr, 0);
    printf("IntArray size = [%zu]\tIntArray factual size = [%zu]\n\n", arr.size, arr.factual_size);

    resize_int_array(&arr, 5);
    print_int_array(&arr);
    printf("IntArray size = [%zu]\tIntArray factual size = [%zu]\n\n", arr.size, arr.factual_size);

    add_to_int_array(&arr, 4);
    add_to_int_array(&arr, 3);
    add_to_int_array(&arr, 1000);
    add_to_int_array(&arr, -1235);
    print_int_array(&arr);
    printf("IntArray size = [%zu]\tIntArray factual size = [%zu]\n\n", arr.size, arr.factual_size);

    resize_int_array(&arr, arr.size - 2);
    print_int_array(&arr);
    printf("IntArray size = [%zu]\tIntArray factual size = [%zu]\n\n", arr.size, arr.factual_size);

    resize_int_array(&arr, arr.factual_size + 2);
    print_int_array(&arr);
    printf("IntArray size = [%zu]\tIntArray factual size = [%zu]\n\n", arr.size, arr.factual_size);

    add_to_int_array(&arr, -1);
    add_to_int_array(&arr, -1);
    add_to_int_array(&arr, -1);
    print_int_array(&arr);
    printf("IntArray size = [%zu]\tIntArray factual size = [%zu]\n\n", arr.size, arr.factual_size);
}

#endif //TECHNOPARK_INTARRAY_H