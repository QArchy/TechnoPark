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

/*

 */

void compare_steps(chess_coord_array** first_permutations, chess_coord_array** second_permutations, chess_coord_array** array) {
    for (int i = 0; i < (*first_permutations)->size; i++)
        for (int j = 0; j < (*second_permutations)->size; j++) {
            if ((*first_permutations)->coords[i].digit != (*second_permutations)->coords[j].digit ||
                    (*first_permutations)->coords[i].letter != (*second_permutations)->coords[j].letter)
                continue;
            add_coord_to_array(&(*array), &(*first_permutations)->coords[i]);
        }
}

void get_move(chess_coord_tree** tree, chess_coord_array** array, int level) {
    if (level == 1)
        add_coord_to_array(&(*array), &(*(*tree)->coord));
    for (int i = 0; i < (*tree)->num_children; i++)
        get_move(&(*tree)->children[i], &(*array), level - 1);
}

void form_new_move(chess_coord_tree** tree, int level) {
    if (level == 1) {
        chess_coord_array *permutations = get_knight_permutations(*(*tree)->coord);
        for (int i = 0; i < (*tree)->num_children; i++)
            alloc_tree(&((*tree)->children[i]), &permutations->coords[i], 8);
        free_array(&permutations);
    }
    for (int i = 0; i < (*tree)->num_children; i++)
        form_new_move(&(*tree)->children[i], level - 1);
}

void find_meets(chess_coord_tree** one, chess_coord_tree** two, chess_coord_array** array) {
    chess_coord_array* one_level_array;
    chess_coord_array* two_level_array;

    int i = 1;
    while ((*array)->factual_size == 0) {
        alloc_array(&one_level_array, 0);
        alloc_array(&two_level_array, 0);

        //сравнение хода i первого коня с ходом i + 1 второго
        form_new_move(&(*two), i);
        get_move(&(*one), &one_level_array, i);
        get_move(&(*two), &two_level_array, i + 1);
        compare_steps(&one_level_array, &two_level_array, &(*array));
        if ((*array)->factual_size != 0)
            return;

        //сравнение хода i + 1 первого коня с ходом i + 1 второго
        free_array(&one_level_array);
        free_array(&two_level_array);
        alloc_array(&one_level_array, 0);
        alloc_array(&two_level_array, 0);

        form_new_move(&(*one), i);
        form_new_move(&(*two), i);
        get_move(&(*one), &one_level_array, i + 1);
        get_move(&(*two), &two_level_array, i + 1);
        compare_steps(&one_level_array, &two_level_array, &(*array));

        i++;
        free_array(&one_level_array);
        free_array(&two_level_array);
    }
}

chess_coord_array* get_knights_meet_pos(chess_coord one, chess_coord two) {
    chess_coord_array* array;
    alloc_array(&array, 0);

    chess_coord_tree* first_tree;
    alloc_tree(&first_tree, &one, 8);
    chess_coord_tree* second_tree;
    alloc_tree(&second_tree, &two, 8);

    find_meets(&first_tree, &second_tree, &array);
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
    printf("Input first knight coord : \n");
    input_chess_coord(&one);
    chess_coord two;
    printf("Input second knight coord : \n");
    input_chess_coord(&two);
    chess_coord_array* coord = get_knights_meet_pos(one, two);
    for (int i = 0; i < coord->size; i++)
        output_chess_coord(&coord->coords[i]);
    free_array(&coord);
}

#pragma endregion
#endif //TECHNOPARK_KNIGHT_H
