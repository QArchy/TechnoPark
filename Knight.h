#ifndef TECHNOPARK_KNIGHT_H
#define TECHNOPARK_KNIGHT_H
#include "Settings.h"

chess_coord_array* get_knight_permutations(chess_coord coord) {
    chess_coord_array* array = (chess_coord_array*)calloc(1, sizeof(chess_coord_array));
    array->size = 0;
    array->factual_size = 0;
    chess_coord tmp = coord;

    tmp.digit = coord.digit + 1;
    tmp.letter = coord.letter - 2;
    if (check_border(tmp))
        add_coord_to_array(&array, &tmp);
    tmp = coord;

    tmp.digit = coord.digit + 2;
    tmp.letter = coord.letter - 1;
    if (check_border(tmp))
        add_coord_to_array(&array, &tmp);
    tmp = coord;

    tmp.digit = coord.digit + 1;
    tmp.letter = coord.letter + 2;
    if (check_border(tmp))
        add_coord_to_array(&array, &tmp);
    tmp = coord;

    tmp.digit = coord.digit + 2;
    tmp.letter = coord.letter + 1;
    if (check_border(tmp))
        add_coord_to_array(&array, &tmp);
    tmp = coord;

    tmp.digit = coord.digit - 1;
    tmp.letter = coord.letter - 2;
    if (check_border(tmp))
        add_coord_to_array(&array, &tmp);
    tmp = coord;

    tmp.digit = coord.digit - 2;
    tmp.letter = coord.letter - 1;
    if (check_border(tmp))
        add_coord_to_array(&array, &tmp);
    tmp = coord;

    tmp.digit = coord.digit - 1;
    tmp.letter = coord.letter + 2;
    if (check_border(tmp))
        add_coord_to_array(&array, &tmp);
    tmp = coord;

    tmp.digit = coord.digit - 2;
    tmp.letter = coord.letter + 1;
    if (check_border(tmp))
        add_coord_to_array(&array, &tmp);

    return array;
}

#pragma region Check

void check_knight_permutations() {
    print_deck();
    chess_coord one;
    input_chess_coord(&one);
    chess_coord_array* coord = get_knight_permutations(one);
    for (int i = 0; i < coord->size; i++)
        output_chess_coord(&coord->coords[i]);
}

#pragma endregion
#endif //TECHNOPARK_KNIGHT_H
