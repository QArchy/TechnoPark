#ifndef TECHNOPARK_CHESS_COORD_ARRAY_H
#define TECHNOPARK_CHESS_COORD_ARRAY_H

typedef struct chess_coord_array {
    chess_coord* coords;
    int size;
    int factual_size;
} chess_coord_array;

void alloc_array(chess_coord_array** array, int size) {
    (*array) = (chess_coord_array*)calloc(1, sizeof(chess_coord_array));
    (*array)->size = size;
    (*array)->factual_size = 0;
    (*array)->coords = (chess_coord*)calloc((*array)->size, sizeof(chess_coord));
}

void free_array(chess_coord_array** array) {
    free((*array)->coords);
    free((*array));
}

void resize_array(chess_coord_array*** array, int new_size) {
    chess_coord_array* tmp = (chess_coord_array*)calloc(1, sizeof(chess_coord_array));
    tmp->coords = (chess_coord*)calloc((*(*array))->size, sizeof(chess_coord));
    for (int i = 0; i < (*(*array))->size; i++) {
        tmp->coords[i].digit = (*(*array))->coords[i].digit;
        tmp->coords[i].letter = (*(*array))->coords[i].letter;
    }

    free((*(*array))->coords);
    int tmp_factual_size = (*(*array))->factual_size;
    free((*(*array)));
    (*(*array)) = (chess_coord_array*)calloc(1, sizeof(chess_coord_array));
    (*(*array))->size = new_size;
    (*(*array))->factual_size = tmp_factual_size;
    (*(*array))->coords = (chess_coord*)calloc((*(*array))->size, sizeof(chess_coord));

    for (int i = 0; i < (*(*array))->factual_size; i++)
        (*(*array))->coords[i] = tmp->coords[i];

    free_array(&tmp);
}

void add_coord_to_array(chess_coord_array** array, chess_coord* coord) {
    if ((*array)->factual_size == (*array)->size)
        resize_array(&array, (*array)->size + (*array)->size / 10 + 1);
    (*array)->coords[(*array)->factual_size++] = *coord;
}

void output_array(chess_coord_array* array) {
    for (int i = 0; i < array->size; i++) {
        output_chess_coord(&array->coords[i]);
    }
}

#endif //TECHNOPARK_CHESS_COORD_ARRAY_H
