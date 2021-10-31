#ifndef TECHNOPARK_BUBBLE_H
#define TECHNOPARK_BUBBLE_H
#include "../DataStructures/IntArray.h"

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void BubbleSort(IntArray* arr) {
    // проходимся N - 1 раз по массиву
    for (size_t i = 0; i < arr->factual_size - 1; i++) {
        size_t bool = 0;
        // проходимся по массиву до N - 1 - i
        /*
         * почему до N - 1 - i ?
         * потому что при первом проходе по внутреннему циклу
         * мы гарантированно ставим максимальный элемент массива
         * в конец, тоесть при каждом проходе мы перетаскиваем максимальный
         * элемент части массива размера N - 1 - i в конец
         */
        for (size_t j = 0; j < arr->factual_size - 1 - i; j++)
            if (arr->array[j] > arr->array[j + 1]) {
                // если следующий элемент меньше предыдущего
                // меняем их местами
                swap(&arr->array[j], &arr->array[j + 1]);
                bool = 1; // обмен произошел!
            }
        if (bool == 0) // если обмен не произошел
            return; // массив отсортрован
    }
}

#endif //TECHNOPARK_BUBBLE_H
