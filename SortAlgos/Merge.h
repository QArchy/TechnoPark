#ifndef TECHNOPARK_MERGE_H
#define TECHNOPARK_MERGE_H

void Sort(IntArray* main, IntArray* buffer, size_t left, size_t mid, size_t right) {
    size_t k = left; // индекс k - в начале массива
    size_t i = left; // инедкс i - в начале массива
    size_t j = mid + 1; // индекс j - справа от середины разбиения
    /*
     * на каждом проходе цикла выбираем меньший элемент
     * из правой (j) и левой (i) части массива
     * и записываем его в буфер
    */
    // пока i не добралось до середины, а j до конца
    while(i <= mid || j <= right) {
        /// если i или j перескочили границу
        // если i-ый элемент меньше j-го
        if (j > right || (i <= mid && main->array[i] < main->array[j])) {
            buffer->array[k] = main->array[i]; // добавляем в буфер i-ый элемент
            i++;
        }
        /// то в правой части массива остались только большие элементы
        /// просто копируем их в buffer
        else { // если i-ый элемет больше либо равен j-му
            buffer->array[k] = main->array[j]; // добавляем в буфер j-ый элемент
            j++;
        }
        k++;
    }
}

void MergePartition(IntArray* main, IntArray* buffer, size_t left, size_t right) {
    // если левая границы меньше правой
    // (размер массива больше единицы)
    if (left < right) {
        size_t mid = (left + right) / 2; // середина массива
        MergePartition(main, buffer, left, mid); // сортируем левую часть
        MergePartition(main, buffer, mid + 1, right); // и правую
        // в результате разбиения в конце рекурсии получим массив размера 2
        // формируем в buffer отсортированный массив
        Sort(main, buffer, left, mid, right);
        // копируем сформированный buffer в main
        for (size_t q = left; q <= right; q++)
            main->array[q] = buffer->array[q];
    }
}

void MergeSort(IntArray* arr) {
    IntArray buffer; // создаем буферный массив
    alloc_int_array(&buffer, arr->size); // того же размера что и исходный
    // сортируем
    MergePartition(arr, &buffer, 0, arr->factual_size - 1);
    free_int_array(&buffer); // освобождаем память
}

#endif //TECHNOPARK_MERGE_H