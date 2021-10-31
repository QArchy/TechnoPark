#ifndef TECHNOPARK_CHESS_COORD_TREE_ARRAY_H
#define TECHNOPARK_CHESS_COORD_TREE_ARRAY_H

typedef struct chess_coord_tree_array {
    struct chess_coord_tree** trees; // массив указателей на деревья
    size_t size; // размер (сколько выделено)
    size_t factual_size; // фактический размер (сколько записано)
} chess_coord_tree_array;

void alloc_tree_array(chess_coord_tree_array* array, size_t size) {
    array->size = size; // записываем размер
    array->factual_size = 0; // в массиве нет элементов
    array->trees = (chess_coord_tree**)calloc(array->size, sizeof(chess_coord_tree*)); // выделение памяти
}

void free_tree_array(chess_coord_tree_array* array) {
    free(array->trees); // освобождаем память
}

void full_free_tree_array(chess_coord_tree_array* array) {
    for (size_t i = 0; i < array->factual_size; i++) // освобождаем память
        free_tree(get_root(array->trees[i])); // из под всех записанный деревьев
    free(array->trees); // и из под массива
}

void resize_tree_array(chess_coord_tree_array* array, size_t new_size) {
    chess_coord_tree_array tmp; // создаем временный массив
    alloc_tree_array(&tmp, array->size); // того же размера
    for (size_t i = 0; i < array->factual_size; i++) // копируем в него исходный
        tmp.trees[i] = array->trees[i];
    tmp.factual_size = array->factual_size;

    free_tree_array(array); // чистим и сразу же пересоздаем исходный
    alloc_tree_array(array, new_size); // массив с новым размером

    if (tmp.factual_size != 0) { // если есть что копироватт
        if (new_size >= tmp.factual_size) // и размер увеличивается
            for (size_t i = 0; i < tmp.size; i++) // копируем весь временный
                array->trees[i] = tmp.trees[i]; // массив в исходный
        else // если размер уменьшается
            for (size_t i = 0; i < new_size; i++) // копируем n = new_size
                array->trees[i] = tmp.trees[i]; // элементов в исходный массив
    }
    array->factual_size = tmp.factual_size;
}

void add_tree_to_tree_array(chess_coord_tree_array* array, chess_coord_tree* tree) {
    if (array->factual_size == array->size) // если места нет
        resize_tree_array(array, array->size + array->size / 10 + 1); // увеличиваем размер
    array->trees[array->factual_size++] = tree; // записываем указатель на дерево
}

void output_leaf(chess_coord_tree* leaf, size_t step) {
    if (leaf == NULL) // если узел пуст
        return; // выходим из рекурсии
    output_leaf(leaf->parent, step - 1); // идем вверх по дереву

    for (size_t i = 0; i < step - 1; i++) // красивая табуляция
        putchar('\t');

    if (leaf->info.figure_code == PAWN) // в зависимости от кода фигуры выводим нужное
        printf("%d Pawn's step#%zu\n", leaf->info.num_figure, step); // сообщение
    else if (leaf->info.figure_code == KNIGHT)
        printf("%d Knight's step#%zu\n", leaf->info.num_figure, step);
    else if (leaf->info.figure_code == KING)
        printf("%d King's step#%zu\n", leaf->info.num_figure, step);
    else if (leaf->info.figure_code == QUEEN)
        printf("%d Queen's step#%zu\n", leaf->info.num_figure, step);
    else if (leaf->info.figure_code == BISHOP)
        printf("%d Bishop's step#%zu\n", leaf->info.num_figure, step);
    else printf("%d Rook's step#%zu\n", leaf->info.num_figure, step);

    for (size_t i = 0; i < step; i++) // красивая табуляция
        putchar('\t');
    output_chess_coord(leaf->coord); // вывод координаты (хода)
}

void output_tree_array(chess_coord_tree_array* array) {
    for (size_t i = 0; i < array->factual_size; i++) { // выводим все записанные деревья
        output_leaf(array->trees[i], get_height(array->trees[i])); // и их родителей
        putchar('\n'); // с красивым форматированием
    }
}

#endif //TECHNOPARK_CHESS_COORD_TREE_ARRAY_H