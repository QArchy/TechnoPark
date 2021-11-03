#ifndef TECHNOPARK_INTARRAY_H
#define TECHNOPARK_INTARRAY_H
#include <stdio.h>
#include <stdlib.h>

typedef struct IntArray {
    int* array; // динамический массив типа int
    size_t size; // размер (сколько выделено)
    size_t factual_size; // фактический размер (сколько записано)
} IntArray;

void alloc_int_array(IntArray* arr, const size_t size) {
    arr->size = size; // записываем размер
    arr->factual_size = 0; // в массиве нет элементов
    arr->array = (int*)calloc(arr->size, sizeof(int)); // выделяем память
}

void free_int_array(const IntArray* arr) {
    free(arr->array); // освобождаем память из под массива
}

void print_int_array(const IntArray* arr) {
    for (size_t i = 0; i < arr->factual_size; i++) // выводим каждый элемент
        printf("IntArray[%zu] = %d\n", i, arr->array[i]);
}

void resize_int_array(IntArray* arr, const size_t new_size) { //
    IntArray tmp; // создаем временный массив
    alloc_int_array(&tmp, arr->size);
    tmp.factual_size = arr->factual_size; // копируем в него исходный
    for (size_t i = 0; i < tmp.factual_size; i++) {
        tmp.array[i] = arr->array[i];
    }

    free_int_array(arr); // чистим и снова инициализируем
    alloc_int_array(arr, new_size); // исходный массив

    if (tmp.factual_size != 0) { // если есть что копировать
        if (new_size >= tmp.size) { // если увеличиваем размер
            for (int i = 0; i < tmp.factual_size; i++) // копируем все из
                arr->array[i] = tmp.array[i]; // временного
            arr->factual_size = tmp.factual_size;
        }
        else { // ели уменьшаем размер
            // и фактический размер временного массива больше или равен new_size
            if (tmp.factual_size >= arr->size) {
                for (int i = 0; i < arr->size; i++) // копируем n = new_size
                    arr->array[i] = tmp.array[i]; // элементов
                arr->factual_size = arr->size;
            }
            else { // если меньше
                for (int i = 0; i < tmp.factual_size; i++) // копируем n = new_size
                    arr->array[i] = tmp.array[i]; // элементов
                arr->factual_size = tmp.factual_size;
            }
        }
    }

    free_int_array(&tmp); // чистим временный массив
}

void add_to_int_array(IntArray* arr, int el) {
    if (arr->factual_size == arr->size) // если места нет
        resize_int_array(arr, arr->size + arr->size / 2 + 1); // увеличиваем размер
    arr->array[arr->factual_size++] = el; // добавляем элемент
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