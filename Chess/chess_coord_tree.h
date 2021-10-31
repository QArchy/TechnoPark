#ifndef TECHNOPARK_CHESS_COORD_TREE_H
#define TECHNOPARK_CHESS_COORD_TREE_H

typedef struct chess_coord_tree {
    chess_coord coord;
    size_t num_children;
    struct chess_coord_tree** children;
    struct chess_coord_tree* parent;
    figure_info info;
} chess_coord_tree;

void alloc_tree(chess_coord_tree* tree, chess_coord coord, chess_coord_tree* parent,
                figure_info info, size_t num_children) {
    if (parent == NULL)
        tree->parent = NULL;
    else
        tree->parent = parent;

    tree->coord = coord;
    tree->info = info;

    tree->num_children = num_children;
    tree->children = (chess_coord_tree**)calloc(tree->num_children, sizeof(chess_coord_tree*));
}

void free_tree(chess_coord_tree* tree) {
    if (tree == NULL)
        return;

    tree->parent = NULL;
    for (size_t i = 0; i < tree->num_children; i++)
        free_tree(tree->children[i]);
    free(tree->children);
}

int get_height(chess_coord_tree* bottom_leaf) {
    if(bottom_leaf == NULL)
        return 0;
    return 1 + get_height(bottom_leaf->parent);
}

#endif //TECHNOPARK_CHESS_COORD_TREE_H