#ifndef TECHNOPARK_CHESS_COORD_TREE_H
#define TECHNOPARK_CHESS_COORD_TREE_H

typedef struct chess_coord_tree {
    chess_coord* coord;
    int num_children;
    struct chess_coord_tree** children;
    struct chess_coord_tree* parent;
    int info;
} chess_coord_tree;

void alloc_tree(chess_coord_tree** tree, chess_coord* coord, chess_coord_tree** parent, int info, int num_children) {
    (*tree) = (chess_coord_tree*)calloc(1, sizeof(chess_coord_tree));
    (*tree)->coord = (chess_coord*)calloc(1, sizeof(chess_coord));

    if (parent == NULL)
        (*tree)->parent = NULL;
    else
        (*tree)->parent = (*parent);
    (*tree)->coord->letter = coord->letter;
    (*tree)->coord->digit = coord->digit;
    (*tree)->info = info;

    (*tree)->num_children = num_children;
    (*tree)->children = (chess_coord_tree**)calloc((*tree)->num_children, sizeof(chess_coord_tree*));
}

void free_tree(chess_coord_tree** tree) {
    if ((*tree) == NULL)
        return;

    (*tree)->parent = NULL;
    free((*tree)->coord);
    for (int i = 0; i < (*tree)->num_children; i++) {
        free_tree(&(*tree)->children[i]);
    }
    free((*tree)->children);
}

#endif //TECHNOPARK_CHESS_COORD_TREE_H
