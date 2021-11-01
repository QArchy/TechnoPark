#ifndef TECHNOPARK_COMB_H
#define TECHNOPARK_COMB_H

void CombSort(IntArray* arr) {
    double factor = 1.247; // фактор уменьшения размера
    // начальный шаг максимален
    double step = (double)(arr->factual_size - 1);
    while (step >= 1) { // пока шаг больше или равен единице
        // проходимся по массиву с условием i + step < N
        for (size_t i = 0; i + (int)step < arr->factual_size; i++)
            // если i-ый элемент больше i+step-го
            if (arr->array[i] > arr->array[i + (int)step])
                // меняем их
                swap(&arr->array[i], &arr->array[i + (int)step]);
        step /= factor; // делим шаг на фактор уменьшения размера
    }
}

#endif //TECHNOPARK_COMB_H