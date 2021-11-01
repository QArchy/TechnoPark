#ifndef TECHNOPARK_SELECT_H
#define TECHNOPARK_SELECT_H

size_t find_min_element(int* arr, size_t size) {
    // ставим индекс минимального элемента в ноль
    size_t min_ind = 0;
    for (size_t i = 1; i < size; i++) // идем по массиву
        // если i-ый элемент меньше минимального
        if (arr[i] < arr[min_ind])
            min_ind = i; // обновляем минимальный
    return min_ind; // возвращаеи индекс минимального элемента
}

void SelectionSort(IntArray* arr) {
    // идем по массиву
    for (size_t i = 0; i < arr->factual_size; i++)
        // меняем местами i-ый элемент и минимальный элемент
        // неотсортированной части массива
        swap(&arr->array[i],&arr->array
        [find_min_element(arr->array + i, arr->factual_size - i) + i]);
}

#endif //TECHNOPARK_SELECT_H
