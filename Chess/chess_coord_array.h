#ifndef TECHNOPARK_CHESS_COORD_ARRAY_H
#define TECHNOPARK_CHESS_COORD_ARRAY_H

typedef struct chess_coord_array {
    chess_coord* coords;
    size_t size;
    size_t factual_size;
} chess_coord_array;

void alloc_array(chess_coord_array* array, size_t size) {
    array->size = size;
    array->factual_size = 0;
    array->coords = (chess_coord*)calloc(array->size, sizeof(chess_coord));
}

void free_array(chess_coord_array* array) {
    free(array->coords);
}

void resize_array(chess_coord_array* array, size_t new_size) {
    chess_coord_array tmp;
    alloc_array(&tmp, array->size);
    for (size_t i = 0; i < array->factual_size; i++) {
        tmp.coords[i].digit = array->coords[i].digit;
        tmp.coords[i].letter = array->coords[i].letter;
    }
    tmp.factual_size = array->factual_size;

    free_array(array);
    alloc_array(array, new_size);

    if (tmp.factual_size != 0) {
        if (new_size >= tmp.factual_size)
            for (size_t i = 0; i < tmp.size; i++)
                array->coords[i] = tmp.coords[i];
        else
            for (size_t i = 0; i < new_size; i++)
                array->coords[i] = tmp.coords[i];
    }
    array->factual_size = tmp.factual_size;
}

void add_coord_to_array(chess_coord_array* array, chess_coord coord) {
    if (array->factual_size == array->size)
        resize_array(array, array->size + array->size / 10 + 1);
    array->coords[array->factual_size++] = coord;
}

void output_array(chess_coord_array* array) {
    for (size_t i = 0; i < array->factual_size; i++) {
        output_chess_coord(array->coords[i]);
    }
}

#endif //TECHNOPARK_CHESS_COORD_ARRAY_H