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

void delete_duplicates(chess_coord_tree_array** array) {
    int duplicates_counter = 0;
    int* duplicates_indices = (int*)calloc((*array)->factual_size, sizeof(int));
    for (int i = 0; i < (*array)->factual_size; i++)
        for (int j = i + 1; j < (*array)->factual_size; j++)
            if (i != j)
                    if ((*array)->trees[i]->coord->digit == (*array)->trees[j]->coord->digit ||
                        (*array)->trees[i]->coord->letter == (*array)->trees[j]->coord->letter)
                        duplicates_indices[duplicates_counter++] = j;

    chess_coord_tree_array* new;
    alloc_tree_array(&new, (*array)->factual_size - duplicates_counter);
    for (int i = 0; i < (*array)->factual_size; ++i) {
        int bool = 1;
        for (int j = 0; j < duplicates_counter; j++)
            if (i == duplicates_indices[j]) {
                bool = 0;
                break;
            }
        if (bool == 1)
            add_tree_to_tree_array(&new, &(*array)->trees[i]);
    }

    free_tree_array(&(*array));
    alloc_tree_array(&(*array), new->size);
    for (int i = 0; i < new->size; i++)
        add_tree_to_tree_array(&(*array), &new->trees[i]);

    free_tree_array(&new);
}

void get_level_number(chess_coord_tree** tree, int* level) {
    if(*tree == NULL)
        return;
    *level += 1;
    get_level_number(&(*tree)->parent, &(*level));
}

void output_leaf(chess_coord_tree** leaf, int step, int CODE) {
    if ((*leaf) == NULL)
        return;
    output_leaf(&(*leaf)->parent, step - 1, CODE);

    if (CODE == 2) {
        for (int i = 0; i < step - 1; i++)
            putchar('\t');
        printf("%d Knight's step#%d\n", (*leaf)->info, step);
    }
    for (int i = 0; i < step; i++)
        putchar('\t');
    output_chess_coord((*leaf)->coord);
}

void output_tree_array(chess_coord_tree_array** array, int CODE) {
    for (int i = 0; i < (*array)->factual_size; i++) {
        int step = 0;
        get_level_number(&(*array)->trees[i], &step);
        output_leaf(&(*array)->trees[i], step, CODE);
        putchar('\n');
    }
}

#endif //TECHNOPARK_CHESS_COORD_TREE_ARRAY_H