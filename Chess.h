#ifndef TECHNOPARK_CHESS_H
#define TECHNOPARK_CHESS_H
#pragma region Constants
const int MIN_N = 1;
const int MAX_N = 8;
const int PAWN = 1; // 3 bit
const int KNIGHT = 2; // 4 bit
const int KING = 3; // 5 bit
const int QUEEN = 4; // 6 bit
const int BISHOP = 5; // 7 bit
const int ROOK = 6; // 8 bit
#pragma endregion

#include "DataStructures.h"

#pragma region Standart_Functions
int check_border(const chess_coord coord) {
    if (coord.digit < MIN_N || coord.digit > MAX_N)
        return -1;
    if (coord.letter < MIN_N || coord.letter > MAX_N)
        return -1;
    return 1;
}

void print_deck() {
    printf(" \t");
    for (int i = 0; i < MAX_N; i++)
        printf("%c\t", i + 65);
    printf("\n");
    for (int i = 0; i < MAX_N; i++) {
        printf("%1d\t", MAX_N - i);
        for (int j = 0; j < MAX_N; j++)
            printf("*\t");
        printf("%1d\t", MAX_N - i);
        printf("\n");
    }
    printf(" \t");
    for (int i = 0; i < MAX_N; i++)
        printf("%c\t", i + 65);
    printf("\n");
}
#pragma endregion

#pragma region Permutations
chess_coord_array* get_pawn_permutations(const chess_coord coord, figure_info info) {
    chess_coord_array* array;
    alloc_array(&array, 0);

    chess_coord tmp = coord;

    if (info.direction_up == 1) {
        if (tmp.digit == MAX_N)
            return array;
        tmp.digit += 1;
    }
    else {
        if (tmp.digit == MIN_N)
            return array;
        tmp.digit -= 1;
    }

    add_coord_to_array(&array,  &tmp);
    return array;
}

chess_coord_array* get_knight_permutations(const chess_coord coord) {
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

chess_coord_array* get_permutations(const chess_coord coord, figure_info info) {
    if (info.figure_code == PAWN)
        return get_pawn_permutations(coord, info);
    else if (info.figure_code == KNIGHT)
        return get_knight_permutations(coord);
    return NULL;
}
#pragma endregion

#pragma region MeetAlgo
void compare_steps(chess_coord_tree_array** first_permutations, chess_coord_tree_array** second_permutations, chess_coord_tree_array** array, int whose_move) {
    for (int i = 0; i < (*first_permutations)->factual_size; i++)
        for (int j = 0; j < (*second_permutations)->factual_size; j++) {
            if ((*first_permutations)->trees[i]->coord->digit != (*second_permutations)->trees[j]->coord->digit ||
                (*first_permutations)->trees[i]->coord->letter != (*second_permutations)->trees[j]->coord->letter)
                continue;
            if (whose_move == 1)
                add_tree_to_tree_array(&(*array), &(*first_permutations)->trees[i]);
            else
                add_tree_to_tree_array(&(*array), &(*second_permutations)->trees[j]);
        }
}

void get_move(chess_coord_tree** tree, chess_coord_tree_array** array, const int level) {
    if (level == 1) {
        add_tree_to_tree_array(&(*array), &(*tree));
        return;
    }
    for (int i = 0; i < (*tree)->num_children; i++)
        get_move(&(*tree)->children[i], &(*array), level - 1);
}

void form_new_move(chess_coord_tree** tree, const int level) {
    if (level == 1) {
        chess_coord_array *permutations = get_permutations(*(*tree)->coord, (*tree)->info);
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

chess_coord_tree_array* get_meet_pos(chess_coord one, figure_info first, chess_coord two, figure_info second) {
    chess_coord_tree_array* array;
    alloc_tree_array(&array, 0);

    chess_coord_tree* first_tree;
    alloc_tree(&first_tree, &one, NULL, first,0);
    chess_coord_tree* second_tree;
    alloc_tree(&second_tree, &two, NULL, second, 0);

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
        if (two_level_array->factual_size == 0) {// вторая пешка достигла границы
            free_tree_array(&one_level_array);
            free_tree_array(&two_level_array);
            free_tree(&first_tree);
            free_tree(&second_tree);
            return NULL;
        }
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
void check_permutations(figure_info figure) {
    print_deck();

    chess_coord one;
    if (figure.figure_code == PAWN)
        printf("Input pawn coord : \n");
    else if (figure.figure_code == KNIGHT)
        printf("Input knight coord : \n");
    input_chess_coord(&one);

    if (figure.figure_code == PAWN)
        printf("Pawn's permutations : \n");
    else if (figure.figure_code == KNIGHT)
        printf("Knight's permutations : \n");

    chess_coord_array* coord = get_permutations(one, figure);
    output_array(&coord);
    free_array(&coord);
}

void check_meet_pos(figure_info first_figure, figure_info second_figure) {
    print_deck();
    first_figure.num_figure = 1;
    second_figure.num_figure = 2;

    if (second_figure.figure_code == PAWN)
        printf("Attention : [%d]pawn moves first\n", 2);
    else if (second_figure.figure_code == KNIGHT)
        printf("Attention : [%d]knight moves first\n", 2);

    chess_coord one;
    if (first_figure.figure_code == PAWN)
        printf("Input first figure (pawn) coord : \n");
    else if (first_figure.figure_code == KNIGHT)
        printf("Input first figure (knight) coord : \n");
    input_chess_coord(&one);

    chess_coord two;
    if (second_figure.figure_code == PAWN)
        printf("Input second figure (pawn) coord : \n");
    else if (second_figure.figure_code == KNIGHT)
        printf("Input second figure (knight) coord : \n");
    input_chess_coord(&two);

    chess_coord_tree_array* array = get_meet_pos(one, first_figure, two, second_figure);
    if (array == NULL)
        printf("Figures unable to meet\n");
    else {
        output_tree_array(&array);
        full_free_tree_array(&array);
    }
}
#pragma endregion
#endif //TECHNOPARK_CHESS_H