#ifndef TECHNOPARK_KNIGHT_H
#define TECHNOPARK_KNIGHT_H
#include "DataStructures.h"

chess_coord_array* get_knight_permutations(chess_coord coord) {
    chess_coord_array* array;
    alloc_array(&array, 0);
    chess_coord tmp = coord;

    tmp.digit = coord.digit + 1;
    tmp.letter = coord.letter - 2;
    if (check_border(tmp) == 1)
        add_coord_to_array(&array, &tmp);
    tmp = coord;

    tmp.digit = coord.digit + 2;
    tmp.letter = coord.letter - 1;
    if (check_border(tmp) == 1)
        add_coord_to_array(&array, &tmp);
    tmp = coord;

    tmp.digit = coord.digit + 1;
    tmp.letter = coord.letter + 2;
    if (check_border(tmp) == 1)
        add_coord_to_array(&array, &tmp);
    tmp = coord;

    tmp.digit = coord.digit + 2;
    tmp.letter = coord.letter + 1;
    if (check_border(tmp) == 1)
        add_coord_to_array(&array, &tmp);
    tmp = coord;

    tmp.digit = coord.digit - 1;
    tmp.letter = coord.letter - 2;
    if (check_border(tmp) == 1)
        add_coord_to_array(&array, &tmp);
    tmp = coord;

    tmp.digit = coord.digit - 2;
    tmp.letter = coord.letter - 1;
    if (check_border(tmp) == 1)
        add_coord_to_array(&array, &tmp);
    tmp = coord;

    tmp.digit = coord.digit - 1;
    tmp.letter = coord.letter + 2;
    if (check_border(tmp) == 1)
        add_coord_to_array(&array, &tmp);
    tmp = coord;

    tmp.digit = coord.digit - 2;
    tmp.letter = coord.letter + 1;
    if (check_border(tmp) == 1)
        add_coord_to_array(&array, &tmp);

    return array;
}

#pragma region Meetup
void compare_steps(chess_coord_tree_array** first_permutations, chess_coord_tree_array** second_permutations, chess_coord_tree_array** array, int whos_move) {
    for (int i = 0; i < (*first_permutations)->factual_size; i++)
        for (int j = 0; j < (*second_permutations)->factual_size; j++) {
            if ((*first_permutations)->trees[i]->coord->digit != (*second_permutations)->trees[j]->coord->digit ||
                    (*first_permutations)->trees[i]->coord->letter != (*second_permutations)->trees[j]->coord->letter)
                continue;
            if (whos_move == 1)
                add_tree_to_tree_array(&(*array), &(*first_permutations)->trees[i]);
            else
                add_tree_to_tree_array(&(*array), &(*second_permutations)->trees[j]);
        }
}

void get_move(chess_coord_tree** tree, chess_coord_tree_array** array, int level) {
    if (level == 1) {
        add_tree_to_tree_array(&(*array), &(*tree));
        return;
    }
    for (int i = 0; i < (*tree)->num_children; i++)
        get_move(&(*tree)->children[i], &(*array), level - 1);
}

void form_new_move(chess_coord_tree** tree, int level) {
    if (level == 1) {
        chess_coord_array *permutations = get_knight_permutations(*(*tree)->coord);
        (*tree)->num_children = permutations->factual_size;
        (*tree)->children = (chess_coord_tree**)calloc((*tree)->num_children, sizeof(chess_coord_tree*));
        for (int i = 0; i < (*tree)->num_children; i++)
            alloc_tree(&((*tree)->children[i]), &permutations->coords[i], &(*tree), (*tree)->info, 0);
        free_array(&permutations);
        return;
    }
    for (int i = 0; i < (*tree)->num_children; i++)
        form_new_move(&(*tree)->children[i], level - 1);
}

chess_coord_tree_array* get_knights_meet_pos(chess_coord one, chess_coord two) {
    chess_coord_tree_array* array;
    alloc_tree_array(&array, 0);

    chess_coord_tree* first_tree;
    alloc_tree(&first_tree, &one, NULL, 1,0);
    chess_coord_tree* second_tree;
    alloc_tree(&second_tree, &two, NULL, 2, 0);

    chess_coord_tree_array* one_level_array;
    chess_coord_tree_array* two_level_array;

    int i = 1;
    while (array->factual_size == 0) {
        alloc_tree_array(&one_level_array, 0);
        alloc_tree_array(&two_level_array, 0);

        //сравнение хода i первого коня с ходом i + 1 второго
        form_new_move(&second_tree, i);
        get_move(&first_tree, &one_level_array, i);
        get_move(&second_tree, &two_level_array, i + 1);
        compare_steps(&one_level_array, &two_level_array, &array, 2);
        if (array->factual_size != 0) {
            delete_duplicates(&array);
            return array;
        }

        //сравнение хода i + 1 первого коня с ходом i + 1 второго
        free_tree_array(&one_level_array);
        free_tree_array(&two_level_array);
        alloc_tree_array(&one_level_array, 0);
        alloc_tree_array(&two_level_array, 0);

        form_new_move(&first_tree, i);
        get_move(&first_tree, &one_level_array, i + 1);
        get_move(&second_tree, &two_level_array, i + 1);
        compare_steps(&one_level_array, &two_level_array, &array, 1);

        i++;
        free_tree_array(&one_level_array);
        free_tree_array(&two_level_array);
    }

    delete_duplicates(&array);
    return array;
}

#pragma endregion
#pragma region Check

void check_knight_permutations() {
    print_deck();
    chess_coord one;
    printf("Input knight coord : \n");
    input_chess_coord(&one);
    chess_coord_array* coord = get_knight_permutations(one);
    for (int i = 0; i < coord->size; i++)
        output_chess_coord(&coord->coords[i]);
    free_array(&coord);
}

void check_knights_meet_pos() {
    print_deck();
    chess_coord one;
    printf("Attention : second knight moves first\n");
    printf("Input first knight coord : \n");
    input_chess_coord(&one);
    chess_coord two;
    printf("Input second knight coord : \n");
    input_chess_coord(&two);
    chess_coord_tree_array* array = get_knights_meet_pos(one, two);
    output_tree_array(&array, KNIGHT_CODE);
    free_tree_array(&array);
}

#pragma endregion
#endif //TECHNOPARK_KNIGHT_H
