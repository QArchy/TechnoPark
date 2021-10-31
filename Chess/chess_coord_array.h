#ifndef TECHNOPARK_CHESS_COORD_ARRAY_H
#define TECHNOPARK_CHESS_COORD_ARRAY_H

typedef struct chess_coord_array {
    chess_coord* coords; // массив координат
    size_t size; // размер (сколько выделено)
    size_t factual_size; // фактический размер (сколько записано)
} chess_coord_array;

void alloc_array(chess_coord_array* array, size_t size) {
    array->size = size; // записываем размер
    array->factual_size = 0; // в массиве нет элементов
    array->coords = (chess_coord*)calloc(array->size, sizeof(chess_coord)); // выделение памяти
}

void free_array(chess_coord_array* array) {
    free(array->coords); // освобождение памяти
}

void resize_array(chess_coord_array* array, size_t new_size) {
    chess_coord_array tmp; // создаем временный массив
    alloc_array(&tmp, array->size); // того же размера
    for (size_t i = 0; i < array->factual_size; i++)
        tmp.coords[i] = array->coords[i]; // копируем исходный массив
    tmp.factual_size = array->factual_size;

    free_array(array); // чистим и сразу же пересоздаем исходный
    alloc_array(array, new_size); // массив с новым размером

    if (tmp.factual_size != 0) { // если есть что копировать
        if (new_size >= tmp.size) // и размер увеличивается
            for (size_t i = 0; i < tmp.size; i++) // копируем все из
                array->coords[i] = tmp.coords[i]; // временного в исходный
        else // если размер уменьшается
            for (size_t i = 0; i < new_size; i++) // копируем n = new_size
                array->coords[i] = tmp.coords[i]; // элементов в исходный массив
    }
    array->factual_size = tmp.factual_size;
}

void add_coord_to_array(chess_coord_array* array, chess_coord coord) {
    if (array->factual_size == array->size) // если места нет
        resize_array(array, array->size + array->size / 10 + 1); // увеличиваем размер
    array->coords[array->factual_size++] = coord; // записываем координату
}

void output_array(chess_coord_array* array) {
    for (size_t i = 0; i < array->factual_size; i++) { // для всех координат
        output_chess_coord(array->coords[i]); // вызываем вывод координаты
    }
}

#endif //TECHNOPARK_CHESS_COORD_ARRAY_H