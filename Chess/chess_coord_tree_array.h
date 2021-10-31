#ifndef TECHNOPARK_CHESS_COORD_TREE_ARRAY_H
#define TECHNOPARK_CHESS_COORD_TREE_ARRAY_H

typedef struct chess_coord_tree_array {
    struct chess_coord_tree** trees;
    size_t size;
    size_t factual_size;
} chess_coord_tree_array;

void alloc_tree_array(chess_coord_tree_array* array, size_t size) {
    array->size = size;
    array->factual_size = 0;
    array->trees = (chess_coord_tree**)calloc(array->size, sizeof(chess_coord_tree*));
}

void free_tree_array(chess_coord_tree_array* array) {
    free(array->trees);
}

void full_free_tree_array(chess_coord_tree_array* array) {
    for (size_t i = 0; i < array->factual_size; i++)
        free_tree(array->trees[i]);
    free(array->trees);
    free(array);
}

void resize_tree_array(chess_coord_tree_array* array, size_t new_size) {
    chess_coord_tree_array tmp;
    alloc_tree_array(&tmp, array->size);
    for (size_t i = 0; i < array->factual_size; i++)
        tmp.trees[i] = array->trees[i];
    tmp.factual_size = array->factual_size;

    free_tree_array(array);
    alloc_tree_array(array, new_size);

    if (tmp.factual_size != 0) {
        if (new_size >= tmp.factual_size)
            for (size_t i = 0; i < tmp.size; i++)
                array->trees[i] = tmp.trees[i];
        else
            for (size_t i = 0; i < new_size; i++)
                array->trees[i] = tmp.trees[i];
    }
    array->factual_size = tmp.factual_size;
}

void add_tree_to_tree_array(chess_coord_tree_array* array, chess_coord_tree* tree) {
    if (array->factual_size == array->size)
        resize_tree_array(array, array->size + array->size / 10 + 1);
    array->trees[array->factual_size++] = tree;
}

void output_leaf(chess_coord_tree* leaf, size_t step) {
    if (leaf == NULL)
        return;
    output_leaf(leaf->parent, step - 1);

    for (size_t i = 0; i < step - 1; i++)
        putchar('\t');

    if (leaf->info.figure_code == PAWN)
        printf("%zu Pawn's step#%zu\n", leaf->info.num_figure, step);
    else if (leaf->info.figure_code == KNIGHT)
        printf("%zu Knight's step#%zu\n", leaf->info.num_figure, step);
    else if (leaf->info.figure_code == KING)
        printf("%zu King's step#%zu\n", leaf->info.num_figure, step);
    else if (leaf->info.figure_code == QUEEN)
        printf("%zu Queen's step#%zu\n", leaf->info.num_figure, step);
    else if (leaf->info.figure_code == BISHOP)
        printf("%zu Bishop's step#%zu\n", leaf->info.num_figure, step);
    else printf("%zu Rook's step#%zu\n", leaf->info.num_figure, step);

    for (size_t i = 0; i < step; i++)
        putchar('\t');
    output_chess_coord(leaf->coord);
}

void output_tree_array(chess_coord_tree_array* array) {
    for (size_t i = 0; i < array->factual_size; i++) {
        output_leaf(array->trees[i], get_height(array->trees[i]));
        putchar('\n');
    }
}

#endif //TECHNOPARK_CHESS_COORD_TREE_ARRAY_H