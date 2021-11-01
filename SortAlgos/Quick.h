#ifndef TECHNOPARK_QUICK_H
#define TECHNOPARK_QUICK_H

size_t partition(int* arr, size_t left, size_t right) {
    // опорный элемент - среднее между первым и последним
    double pivot = (double)(arr[left] + arr[right]) / 2;
    size_t i = left; // итератор left
    size_t j = right; // итератор right
    // цикл перебрасывает все элементы меньше опорного влево
    // а больше опорного - вправо
    while(1) { // пока true
        // находим элемент больше опорного
        while (arr[i] < pivot) // пока i-ый элемент меньше опорного
            i++; // шагаем вправо
        // находим элемент меньше опорного
        while (arr[j] > pivot) // пока j-ый элемент больше опорного
            j--; // шагаем влево
        if (i >= j) // если i встретился или перескочил j
            return i; // возвращаем j
            /// можем вернуть i, но тогда
        swap(&arr[i++], &arr[j--]); // меняем i-ый и j-ый местами
    }
}

void sort(int* arr, size_t left, size_t right) {
    // если левая границы массива меньше правой
    if (left < right) {
        // берем индес разбиения
        size_t p = partition(arr, left, right);
        /// здесь нужно передать не p а p - 1
        sort(arr, left, p); // сортируем левую часть массива
        /// a здесь передать не p + 1 а p
        sort(arr, p + 1, right); // и правую
    }
}

void QuickSort(IntArray* arr) {
    sort(arr->array, 0, (int)arr->factual_size);
}

#endif //TECHNOPARK_QUICK_H