#ifndef TECHNOPARK_CHESS_H
#define TECHNOPARK_CHESS_H
#include <stdlib.h>
#pragma region Constants
const size_t MIN_N = 1;
const size_t MAX_N = 8;
const size_t PAWN = 1;
const size_t KNIGHT = 2;
const size_t KING = 3;
const size_t QUEEN = 4;
const size_t BISHOP = 5;
const size_t ROOK = 6;
#pragma endregion
#include "DataStructures.h"
#pragma region Standart_Functions
int check_border(chess_coord coord) {
    if (coord.digit < MIN_N || coord.digit > MAX_N)
        return 0;
    if (coord.letter < MIN_N || coord.letter > MAX_N)
        return 0;
    return 1;
}

void print_deck() {
    printf(" \t");
    for (size_t i = 0; i < MAX_N; i++)
        printf("%c\t", (char)i + 65);
    printf("\n");
    for (size_t i = 0; i < MAX_N; i++) {
        printf("%zu\t", MAX_N - i);
        for (size_t j = 0; j < MAX_N; j++)
            printf("*\t");
        printf("%zu\t", MAX_N - i);
        printf("\n");
    }
    printf(" \t");
    for (size_t i = 0; i < MAX_N; i++)
        printf("%c\t", (char)i + 65);
    printf("\n");
}
#pragma endregion
#pragma region Permutations
chess_coord_array* get_pawn_permutations(chess_coord coord, figure_info info) {
    chess_coord_array* array = (chess_coord_array*)calloc(1, sizeof(chess_coord_array));
    alloc_array(array, 0);

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

    add_coord_to_array(array,  tmp);
    return array;
}

chess_coord_array* get_knight_permutations(chess_coord coord) {
    chess_coord_array* array = (chess_coord_array*)calloc(1, sizeof(chess_coord_array));
    alloc_array(array, 0);
    chess_coord tmp = coord;

    tmp.digit = coord.digit + 1;
    tmp.letter = coord.letter - 2;
    if (check_border(tmp) == 1)
        add_coord_to_array(array, tmp);
    tmp = coord;

    tmp.digit = coord.digit + 2;
    tmp.letter = coord.letter - 1;
    if (check_border(tmp) == 1)
        add_coord_to_array(array, tmp);
    tmp = coord;

    tmp.digit = coord.digit + 1;
    tmp.letter = coord.letter + 2;
    if (check_border(tmp) == 1)
        add_coord_to_array(array, tmp);
    tmp = coord;

    tmp.digit = coord.digit + 2;
    tmp.letter = coord.letter + 1;
    if (check_border(tmp) == 1)
        add_coord_to_array(array, tmp);
    tmp = coord;

    tmp.digit = coord.digit - 1;
    tmp.letter = coord.letter - 2;
    if (check_border(tmp) == 1)
        add_coord_to_array(array, tmp);
    tmp = coord;

    tmp.digit = coord.digit - 2;
    tmp.letter = coord.letter - 1;
    if (check_border(tmp) == 1)
        add_coord_to_array(array, tmp);
    tmp = coord;

    tmp.digit = coord.digit - 1;
    tmp.letter = coord.letter + 2;
    if (check_border(tmp) == 1)
        add_coord_to_array(array, tmp);
    tmp = coord;

    tmp.digit = coord.digit - 2;
    tmp.letter = coord.letter + 1;
    if (check_border(tmp) == 1)
        add_coord_to_array(array, tmp);

    return array;
}

chess_coord_array* get_king_permutations(chess_coord coord) {
    chess_coord_array* array = (chess_coord_array*)calloc(1, sizeof(chess_coord_array));
    alloc_array(array, 0);
    chess_coord tmp = coord;

    tmp.digit = coord.digit + 1;
    tmp.letter = coord.letter + 1;
    if (check_border(tmp) == 1)
        add_coord_to_array(array, tmp);
    tmp = coord;

    tmp.digit = coord.digit + 1;
    if (check_border(tmp) == 1)
        add_coord_to_array(array, tmp);
    tmp = coord;

    tmp.digit = coord.digit + 1;
    tmp.letter = coord.letter - 1;
    if (check_border(tmp) == 1)
        add_coord_to_array(array, tmp);
    tmp = coord;

    tmp.letter = coord.letter - 1;
    if (check_border(tmp) == 1)
        add_coord_to_array(array, tmp);
    tmp = coord;

    tmp.digit = coord.digit - 1;
    tmp.letter = coord.letter - 1;
    if (check_border(tmp) == 1)
        add_coord_to_array(array, tmp);
    tmp = coord;

    tmp.digit = coord.digit - 1;
    if (check_border(tmp) == 1)
        add_coord_to_array(array, tmp);
    tmp = coord;

    tmp.digit = coord.digit - 1;
    tmp.letter = coord.letter + 1;
    if (check_border(tmp) == 1)
        add_coord_to_array(array, tmp);
    tmp = coord;

    tmp.letter = coord.letter + 1;
    if (check_border(tmp) == 1)
        add_coord_to_array(array, tmp);

    return array;
}

chess_coord_array* get_queen_permutations(chess_coord coord) {
    chess_coord_array* array = (chess_coord_array*)calloc(1, sizeof(chess_coord_array));
    alloc_array(array, 0);
    chess_coord tmp = coord;

    // bishop permutations
    while(1) {
        tmp.letter--;
        tmp.digit--;
        if (check_border(tmp) == 0)
            break;
        add_coord_to_array(array, tmp);
    }
    tmp = coord;

    while(1) {
        tmp.letter++;
        tmp.digit++;
        if (check_border(tmp) == 0)
            break;
        add_coord_to_array(array, tmp);
    }
    tmp = coord;

    while(1) {
        tmp.digit++;
        tmp.letter--;
        if (check_border(tmp) == 0)
            break;
        add_coord_to_array(array, tmp);
    }
    tmp = coord;

    while(1) {
        tmp.digit--;
        tmp.letter++;
        if (check_border(tmp) == 0)
            break;
        add_coord_to_array(array, tmp);
    }
    tmp = coord;

    //rook permutations
    while(1) {
        tmp.letter--;
        if (check_border(tmp) == 0)
            break;
        add_coord_to_array(array, tmp);
    }
    tmp = coord;

    while(1) {
        tmp.letter++;
        if (check_border(tmp) == 0)
            break;
        add_coord_to_array(array, tmp);
    }
    tmp = coord;

    while(1) {
        tmp.digit--;
        if (check_border(tmp) == 0)
            break;
        add_coord_to_array(array, tmp);
    }
    tmp = coord;

    while(1) {
        tmp.digit++;
        if (check_border(tmp) == 0)
            break;
        add_coord_to_array(array, tmp);
    }

    return array;
}

chess_coord_array* get_bishop_permutations(chess_coord coord) {
    chess_coord_array* array = (chess_coord_array*)calloc(1, sizeof(chess_coord_array));
    alloc_array(array, 0);
    chess_coord tmp = coord;

    while(1) {
        tmp.letter--;
        tmp.digit--;
        if (check_border(tmp) == 0)
            break;
        add_coord_to_array(array, tmp);
    }
    tmp = coord;

    while(1) {
        tmp.letter++;
        tmp.digit++;
        if (check_border(tmp) == 0)
            break;
        add_coord_to_array(array, tmp);
    }
    tmp = coord;

    while(1) {
        tmp.digit++;
        tmp.letter--;
        if (check_border(tmp) == 0)
            break;
        add_coord_to_array(array, tmp);
    }
    tmp = coord;

    while(1) {
        tmp.digit--;
        tmp.letter++;
        if (check_border(tmp) == 0)
            break;
        add_coord_to_array(array, tmp);
    }

    return array;
}

chess_coord_array* get_rook_permutations(chess_coord coord) {
    chess_coord_array* array = (chess_coord_array*)calloc(1, sizeof(chess_coord_array));
    alloc_array(array, 0);
    chess_coord tmp = coord;

    while(1) {
        tmp.letter--;
        if (check_border(tmp) == 0)
            break;
        add_coord_to_array(array, tmp);
    }
    tmp = coord;

    while(1) {
        tmp.letter++;
        if (check_border(tmp) == 0)
            break;
        add_coord_to_array(array, tmp);
    }
    tmp = coord;

    while(1) {
        tmp.digit--;
        if (check_border(tmp) == 0)
            break;
        add_coord_to_array(array, tmp);
    }
    tmp = coord;

    while(1) {
        tmp.digit++;
        if (check_border(tmp) == 0)
            break;
        add_coord_to_array(array, tmp);
    }

    return array;
}

chess_coord_array* get_permutations(chess_coord coord, figure_info info) {
    if (info.figure_code == PAWN)
        return get_pawn_permutations(coord, info);
    else if (info.figure_code == KNIGHT)
        return get_knight_permutations(coord);
    else if (info.figure_code == KING)
        return get_king_permutations(coord);
    else if (info.figure_code == QUEEN)
        return get_queen_permutations(coord);
    else if (info.figure_code == BISHOP)
        return get_bishop_permutations(coord);
    else if (info.figure_code == ROOK)
        return get_rook_permutations(coord);

    return NULL;
}
#pragma endregion
#pragma region MeetAlgo
size_t compare_parents(chess_coord_tree* tree_1, chess_coord_tree* tree_2) {
    if (tree_1 == NULL || tree_2 == NULL)
        return 0;
    if (tree_1->coord.digit == tree_2->coord.digit && tree_1->coord.letter == tree_2->coord.letter)
        return compare_parents(tree_1->parent, tree_2->parent);
    else
        return 1;
}

void compare_steps(chess_coord_tree_array* first_permutations, chess_coord_tree_array* second_permutations,
                   chess_coord_tree_array* array, size_t whose_move) {
    for (size_t i = 0; i < first_permutations->factual_size; i++)
        for (size_t j = 0; j < second_permutations->factual_size; j++) {
            if (first_permutations->trees[i]->coord.digit != second_permutations->trees[j]->coord.digit ||
                first_permutations->trees[i]->coord.letter != second_permutations->trees[j]->coord.letter)
                continue;
            if (whose_move == 1) {
                size_t bool = 1;
                for (size_t k = 0; k < array->factual_size && k < first_permutations->factual_size; k++)
                    if (compare_parents(first_permutations->trees[i], array->trees[k]) == 0) {
                        bool = 0;
                        break;
                    }
                if (bool == 0)
                    break;
                add_tree_to_tree_array(array, first_permutations->trees[i]);
            }
            else {
                size_t bool = 1;
                for (size_t k = 0; k < array->factual_size && k < second_permutations->factual_size; k++)
                    if (compare_parents(second_permutations->trees[j], array->trees[k]) == 0) {
                        bool = 0;
                        break;
                    }
                if (bool == 0)
                    continue;
                add_tree_to_tree_array(&(*array), second_permutations->trees[j]);
            }
        }
}

void get_move(chess_coord_tree* tree, chess_coord_tree_array* array, size_t level) {
    if (level == 1) {
        add_tree_to_tree_array(array, tree);
        return;
    }
    for (size_t i = 0; i < tree->num_children; i++)
        get_move(tree->children[i], array, level - 1);
}

void form_new_move(chess_coord_tree* tree, size_t level) {
    if (level == 1) {
        chess_coord_array *permutations = get_permutations(tree->coord, tree->info);
        tree->num_children = permutations->factual_size;
        tree->children = (chess_coord_tree**)calloc(tree->num_children, sizeof(chess_coord_tree*));
        for (size_t i = 0; i < tree->num_children; i++) {
            tree->children[i] = (chess_coord_tree*)calloc(1, sizeof(chess_coord_tree));
            alloc_tree(tree->children[i], permutations->coords[i], tree, tree->info, 0);
        }
        free_array(permutations);
        return;
    }
    for (size_t i = 0; i < tree->num_children; i++)
        form_new_move(tree->children[i], level - 1);
}

chess_coord_tree_array* get_meet_pos(chess_coord one, figure_info first, chess_coord two,
                                     figure_info second) {
    chess_coord_tree_array* array = (chess_coord_tree_array*)calloc(1, sizeof(chess_coord_tree_array));
    alloc_tree_array(array, 0);

    chess_coord_tree* first_tree = (chess_coord_tree*)calloc(1, sizeof(chess_coord_tree));
    alloc_tree(first_tree, one, NULL, first,0);
    chess_coord_tree* second_tree = (chess_coord_tree*)calloc(1, sizeof(chess_coord_tree));;
    alloc_tree(second_tree, two, NULL, second, 0);

    chess_coord_tree_array one_level_array;
    chess_coord_tree_array two_level_array;

    size_t i = 1;
    while (array->factual_size == 0) {
        alloc_tree_array(&one_level_array, 0);
        alloc_tree_array(&two_level_array, 0);

        //сравнение хода i первой фигуры с ходом i + 1 второй
        form_new_move(second_tree, i);
        get_move(first_tree, &one_level_array, i);
        get_move(second_tree, &two_level_array, i + 1);
        if (two_level_array.factual_size == 0) { // вторая пешка достигла границы
            free_tree_array(&one_level_array);
            free_tree_array(&two_level_array);
            free_tree(first_tree);
            free_tree(second_tree);
            return NULL;
        }
        compare_steps(&one_level_array, &two_level_array, array, 2);
        if (array->factual_size != 0)
            return array;

        //сравнение хода i + 1 первой фигуры с ходом i + 1 второй
        free_tree_array(&one_level_array);
        free_tree_array(&two_level_array);
        alloc_tree_array(&one_level_array, 0);
        alloc_tree_array(&two_level_array, 0);

        form_new_move(first_tree, i);
        get_move(first_tree, &one_level_array, i + 1);
        get_move(second_tree, &two_level_array, i + 1);
        compare_steps(&one_level_array, &two_level_array, array, 1);

        i++;
        free_tree_array(&one_level_array);
        free_tree_array(&two_level_array);
    }

    return array;
}
#pragma endregion
#pragma region FindWay
void compare_step (chess_coord_tree_array* permutations, chess_coord coord,
                   chess_coord_tree_array* array) {
    for (size_t i = 0; i < permutations->factual_size; i++)
        if (permutations->trees[i]->coord.digit == coord.digit &&
        permutations->trees[i]->coord.letter == coord.letter)
            add_tree_to_tree_array(array, permutations->trees[i]);
}

chess_coord_tree_array* get_way(chess_coord coord, chess_coord aim, figure_info info) {
    chess_coord_tree_array* array = (chess_coord_tree_array*)calloc(1, sizeof(chess_coord_tree_array));
    alloc_tree_array(array, 0);

    chess_coord_tree* tree = (chess_coord_tree*)calloc(1, sizeof(chess_coord_tree));;
    alloc_tree(tree, coord, NULL, info, 0);

    chess_coord_tree_array level_array;

    size_t i = 1;
    while (array->factual_size == 0) {
        alloc_tree_array(&level_array, 0);

        form_new_move(tree, i);
        get_move(tree, &level_array, i);
        if (level_array.factual_size == 0) { // пешка достигла границы
            free_tree_array(&level_array);
            free_tree(tree);
            return NULL;
        }
        compare_step(&level_array, aim, array);
        if (array->factual_size != 0)
            return array;

        i++;
        free_tree_array(&level_array);
    }

    return array;
}
#pragma endregion
#pragma region Check
void check_permutations() {
    //print_deck();
    figure_info figure;
    input_figure_info(&figure);

    chess_coord one;
    if (figure.figure_code == PAWN)
        printf("Input pawn coord : \n");
    else if (figure.figure_code == KNIGHT)
        printf("Input knight coord : \n");
    else if (figure.figure_code == KING)
        printf("Input king coord : \n");
    else if (figure.figure_code == QUEEN)
        printf("Input queen coord : \n");
    else if (figure.figure_code == BISHOP)
        printf("Input bishop coord : \n");
    else printf("Input rook coord : \n");
    input_chess_coord(&one);

    if (figure.figure_code == PAWN)
        printf("Pawn's permutations : \n");
    else if (figure.figure_code == KNIGHT)
        printf("Knight's permutations : \n");
    else if (figure.figure_code == KING)
        printf("King's permutations : \n");
    else if (figure.figure_code == QUEEN)
        printf("Queen's permutations : \n");
    else if (figure.figure_code == BISHOP)
        printf("Bishop's permutations : \n");
    else printf("Rook's permutations : \n");

    chess_coord_array* coord = get_permutations(one, figure);
    output_array(coord);
    free_array(coord);
}

void check_way() {
    //print_deck();
    figure_info figure;
    figure.num_figure = 1;
    input_figure_info(&figure);

    chess_coord coord;
    if (figure.figure_code == PAWN)
        printf("Input pawn coord : \n");
    else if (figure.figure_code == KNIGHT)
        printf("Input knight coord : \n");
    else if (figure.figure_code == KING)
        printf("Input king coord : \n");
    else if (figure.figure_code == QUEEN)
        printf("Input queen coord : \n");
    else if (figure.figure_code == BISHOP)
        printf("Input bishop coord : \n");
    else printf("Input rook coord : \n");
    input_chess_coord(&coord);

    chess_coord aim;
    printf("Input aim : \n");
    input_chess_coord(&aim);

    if (figure.figure_code == PAWN)
        printf("Pawn's way to [%zu;%c]: \n", aim.digit, (char)aim.letter + 64);
    else if (figure.figure_code == KNIGHT)
        printf("Knight's way to [%zu;%c]: \n", aim.digit, (char)aim.letter + 64);
    else if (figure.figure_code == KING)
        printf("King's way to [%zu;%c]: \n", aim.digit, (char)aim.letter + 64);
    else if (figure.figure_code == QUEEN)
        printf("Queen's way to [%zu;%c]: \n", aim.digit, (char)aim.letter + 64);
    else if (figure.figure_code == BISHOP)
        printf("Bishop's way to [%zu;%c]: \n", aim.digit, (char)aim.letter + 64);
    else printf("Rook's way to [%zu;%c]: \n", aim.digit, (char)aim.letter + 64);

    chess_coord_tree_array* array = get_way(coord, aim, figure);
    if (array == NULL)
        printf("Figures unable to meet\n");
    else {
        output_tree_array(array);
        full_free_tree_array(array);
    }
}

void check_meet_pos() {
    //print_deck();
    figure_info first_figure;
    figure_info second_figure;
    first_figure.num_figure = 1;
    second_figure.num_figure = 2;

    input_figure_info(&first_figure);
    chess_coord one;
    if (first_figure.figure_code == PAWN) {
        printf("Input first figure (pawn) coord : \n");
    }
    else if (first_figure.figure_code == KNIGHT) {
        printf("Input first figure (knight) coord : \n");
    }
    else if (first_figure.figure_code == KING) {
        printf("Input first figure (king) coord : \n");
    }
    else if (first_figure.figure_code == QUEEN) {
        printf("Input first figure (queen) coord : \n");
    }
    else if (first_figure.figure_code == BISHOP) {
        printf("Input first figure (bishop) coord : \n");
    }
    else printf("Input first figure (rook) coord : \n");
    input_chess_coord(&one);

    if (first_figure.figure_code == PAWN)
        printf("Attention : [%d]pawn moves first\n", 1);
    else if (first_figure.figure_code == KNIGHT)
        printf("Attention : [%d]knight moves first\n", 1);
    else if (first_figure.figure_code == KING)
        printf("Attention : [%d]king moves first\n", 1);
    else if (first_figure.figure_code == QUEEN)
        printf("Attention : [%d]queen moves first\n", 1);
    else if (first_figure.figure_code == BISHOP)
        printf("Attention : [%d]bishop moves first\n", 1);
    else printf("Attention : [%d]rook moves first\n", 1);

    input_figure_info(&second_figure);
    chess_coord two;
    if (second_figure.figure_code == PAWN)
        printf("Input second figure (pawn) coord : \n");
    else if (second_figure.figure_code == KNIGHT)
        printf("Input second figure (knight) coord : \n");
    else if (second_figure.figure_code == KING)
        printf("Input second figure (king) coord : \n");
    else if (second_figure.figure_code == QUEEN)
        printf("Input second figure (queen) coord : \n");
    else if (second_figure.figure_code == BISHOP)
        printf("Input second figure (bishop) coord : \n");
    else printf("Input second figure (rook) coord : \n");
    input_chess_coord(&two);

    // reverse ввода так как алгоритм просчитывает сначала ход второй фигуры
    chess_coord_tree_array* array = get_meet_pos(two, second_figure, one, first_figure);
    if (array == NULL)
        printf("Figures unable to meet\n");
    else {
        output_tree_array(array);
        full_free_tree_array(array);
    }
}
#pragma endregion
#endif //TECHNOPARK_CHESS_H