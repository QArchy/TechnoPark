#ifndef TECHNOPARK_SHAKER_H
#define TECHNOPARK_SHAKER_H

void ShakerSort(IntArray* arr) {
    size_t left = 0; // левая граница массива
    size_t right = arr->factual_size - 1; // правая граница
    while (left < right) { // пока границы не сошлись
        size_t bool = 0;
        for (size_t i = right; i > left; i--) { // проходим справа налево
            // если предыдущий элемент больше следующего
            if (arr->array[i] < arr->array[i - 1]) {
                // меняем их
                swap(&arr->array[i], &arr->array[i - 1]);
                bool = 1; // обмен произошел
            }
        }
        if (bool == 0) // если обмена не было
            return; // массив отсортирован
        left++; // сдвигаем левую границу вправо
        // так как минимальный элемент гарантировано находится в начале

        bool = 0;
        for (size_t i = left; i < right; i++) // проходим слева направо
            // если следующий элемент меньше предыдущего
            if (arr->array[i] > arr->array[i + 1]) {
                // меняем их
                swap(&arr->array[i], &arr->array[i + 1]);
                bool = 1; // обмен произошел
            }
        if (bool == 0) // если обмена не было
            return; // массив отсортирован
        right--; //сдвигаем правую границу влево
        // так как максимальный элемент гарантировано находится в конце
    }
}

#endif //TECHNOPARK_SHAKER_H