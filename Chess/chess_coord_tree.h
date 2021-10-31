#ifndef TECHNOPARK_CHESS_COORD_TREE_H
#define TECHNOPARK_CHESS_COORD_TREE_H

typedef struct chess_coord_tree {
    chess_coord coord; // координата (ход фигуры)
    figure_info info; // информация о фигуре, ходы которой хранятся // в данном дереве
    size_t num_children; // количество потомков
    struct chess_coord_tree** children; // массив указателей на потомков
    struct chess_coord_tree* parent; // указатель на родителя
} chess_coord_tree;

void alloc_tree(chess_coord_tree* tree, chess_coord coord, chess_coord_tree* parent,
                figure_info info, size_t num_children) {
    tree->parent = parent; // записываем указатель на родителя
    tree->coord = coord; // записываем координату (ход)
    tree->info = info; // и информацию о фигуре
    tree->num_children = num_children; // выделяем массив указателей на потомков
    tree->children = (chess_coord_tree**)calloc(tree->num_children, sizeof(chess_coord_tree*));
}

void free_tree(chess_coord_tree* tree) {
    if (tree == NULL) // если дерево пустое
        return; // выходим из рекурсии

    for(size_t i = 0; i < tree->num_children; i++) {
        free_tree(tree->children[i]); // рекурсивно опускаемся по дереву
        free(tree->children[i]);
    }
    tree->parent = NULL; // обнуляем все поля
    free(tree->children);
    tree->num_children = 0;
    tree->children = NULL;
}

int get_height(chess_coord_tree* bottom_leaf) {
    if(bottom_leaf == NULL) // если дошли до вершины
        return 0; // выходим их рекурсии
    return 1 + get_height(bottom_leaf->parent); // идем вверх по дереву
}

chess_coord_tree* get_root(chess_coord_tree* bottom_leaf) {
    if (bottom_leaf->parent == NULL) // если дошли до корня
        return bottom_leaf; // возвращаем его
    return get_root(bottom_leaf->parent); // идем вверх по дереву
}

#endif //TECHNOPARK_CHESS_COORD_TREE_H