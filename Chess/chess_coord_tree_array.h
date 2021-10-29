#ifndef TECHNOPARK_CHESS_COORD_TREE_ARRAY_H
#define TECHNOPARK_CHESS_COORD_TREE_ARRAY_H

typedef struct chess_coord_tree_array {
    struct chess_coord_tree** trees;
    int size;
    int factual_size;
} chess_coord_tree_array;

void alloc_tree_array(chess_coord_tree_array** array, int size) {
    (*array) = (chess_coord_tree_array *)calloc(1, sizeof(chess_coord_tree_array));
    (*array)->size = size;
    (*array)->factual_size = 0;
    (*array)->trees = (chess_coord_tree**)calloc((*array)->size, sizeof(chess_coord_tree*));
}

void free_tree_array(chess_coord_tree_array** array) {
    free((*array)->trees);
    free((*array));
}

void full_free_tree_array(chess_coord_tree_array** array) {
    for (int i = 0; i < (*array)->factual_size; i++)
        free_tree(&(*array)->trees[i]);
    free((*array)->trees);
    free((*array));
}

void resize_tree_array(chess_coord_tree_array** array, int new_size) {
    chess_coord_tree_array* tmp;
    alloc_tree_array(&tmp, (*array)->size);
    for (int i = 0; i < (*array)->factual_size; i++)
        tmp->trees[i] = (*array)->trees[i];
    tmp->factual_size = (*array)->factual_size;

    free_tree_array(&(*array));

    (*array) = (chess_coord_tree_array*)calloc(1, sizeof(chess_coord_tree_array));
    (*array)->size = new_size;
    (*array)->trees = (chess_coord_tree**)calloc((*array)->size, sizeof(chess_coord_tree*));

    if (new_size >= tmp->factual_size) {
        for (int i = 0; i < tmp->factual_size; i++)
            (*array)->trees[i] = tmp->trees[i];
        (*array)->factual_size = tmp->factual_size;
    }
    else {
        for (int i = 0; i < new_size; i++)
            (*array)->trees[i] = tmp->trees[i];
        (*array)->factual_size = new_size;
    }

    free_tree_array(&tmp);
}

void add_tree_to_tree_array(chess_coord_tree_array** array, chess_coord_tree** tree) {
    if ((*array)->factual_size == (*array)->size)
        resize_tree_array(&(*array), (*array)->size + (*array)->size / 10 + 1);
    (*array)->trees[(*array)->factual_size++] = *tree;
}

void get_level_number(chess_coord_tree** tree, int* level) {
    if(*tree == NULL)
        return;
    *level += 1;
    get_level_number(&(*tree)->parent, &(*level));
}

void output_leaf(chess_coord_tree** leaf, int step) {
    if ((*leaf) == NULL)
        return;
    output_leaf(&(*leaf)->parent, step - 1);

    for (int i = 0; i < step - 1; i++)
        putchar('\t');

    if ((*leaf)->info.figure_code == PAWN)
        printf("%d Pawn's step#%d\n", (*leaf)->info.num_figure, step);
    else if ((*leaf)->info.figure_code == KNIGHT)
        printf("%d Knight's step#%d\n", (*leaf)->info.num_figure, step);
    else if ((*leaf)->info.figure_code == KING)
        printf("%d King's step#%d\n", (*leaf)->info.num_figure, step);
    else if ((*leaf)->info.figure_code == QUEEN)
        printf("%d Queen's step#%d\n", (*leaf)->info.num_figure, step);
    else if ((*leaf)->info.figure_code == BISHOP)
        printf("%d Bishop's step#%d\n", (*leaf)->info.num_figure, step);
    else printf("%d Rook's step#%d\n", (*leaf)->info.num_figure, step);

    for (int i = 0; i < step; i++)
        putchar('\t');
    output_chess_coord((*leaf)->coord);
}

void output_tree_array(chess_coord_tree_array** array) {
    for (int i = 0; i < (*array)->factual_size; i++) {
        int step = 0;
        get_level_number(&(*array)->trees[i], &step);
        output_leaf(&(*array)->trees[i], step);
        putchar('\n');
    }
}

#endif //TECHNOPARK_CHESS_COORD_TREE_ARRAY_H