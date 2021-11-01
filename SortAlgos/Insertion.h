#ifndef TECHNOPARK_INSERTION_H
#define TECHNOPARK_INSERTION_H

int binarySearch(int* a, int item, int left, int right) { // O(n^2) худший
    // если правая граница массива меньше или равна левой
    if (right <= left) {
        if (item > a[left]) // и элемент больше чем в левой границе
            return left + 1; // позиция вставки - справа от него
        return left; // иначе позиция вставки - левая граница
    }

    // середина рассматриваемой части массива
    int mid = (left + right) / 2;

    if (item == a[mid]) // если элемент равен среднему
        return mid + 1; // позиция вставки - справа от него

    if (item > a[mid]) // если элемент больше среднего
        // ищем позицию в правой части массива
        return binarySearch(a, item,mid + 1, right);
    // если элемент меньше среднего
    // ищем позицию в левой части массива
    return binarySearch(a, item, left, mid - 1);
}

void BinaryInsertionSort(IntArray* arr) {
    // идем по массиву
    for (int i = 1; i < arr->factual_size; ++i)
    {
        int tmp = arr->array[i]; // запоминаем i-ый элемент
        // находим позицию вставки i-го элемента
        int position = binarySearch(arr->array, tmp, 0, i - 1);

        // передвигаем все элементы [position ... i - 1] вправо для вставки tmp
        int j = i; // запонимаем i-ю позицию
        while (j != position) { // пока не дошли до позиции вставки
            // ставим j-1-ый элемент на место j-го
            arr->array[j] = arr->array[j - 1];
            j--;
        }
        arr->array[j] = tmp; // записать tmp
    }
}

void InsertionSort(IntArray* arr) {
    // идем по массиву
    for (size_t i = 1; i < arr->factual_size; i++) {
        int tmp = arr->array[i]; // запоминаем i-ый элемент
        size_t j = i; // запоминаем j-ю позицию
        // пока j-1-ый элемент больше tmp
        // cтавим j-1-ый элемент на место j-го
        while (j > 0 && arr->array[j - 1] > tmp) {
            arr->array[j] = arr->array[j - 1];
            j--;
        }
        // записываем в найденное место tmp
        arr->array[j] = tmp;
    }
}

#endif //TECHNOPARK_INSERTION_H