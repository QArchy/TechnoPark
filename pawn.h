#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H
#include "Settings.h"

chess_coord_array* get_pawn_permutations(chess_coord coord) {
    chess_coord_array* permutations_array = (chess_coord_array*)calloc(1, sizeof(chess_coord_array));
    if (coord.digit == MAX_N) {
        permutations_array->size = 0;
        permutations_array->coords = NULL;
        return permutations_array;
    }
    permutations_array->size = MAX_N - coord.digit + 1; // +1 включение текущего coord
    permutations_array->coords = (chess_coord*)calloc(permutations_array->size, sizeof(chess_coord));
    for (int i = 0; i < permutations_array->size; i++) {
        permutations_array->coords[i].letter = coord.letter;
        permutations_array->coords[i].digit = i + coord.digit;
    }
    return permutations_array;
}

chess_coord get_pawns_meet_pos(chess_coord one, chess_coord two) {
    // возвращается позиция встречи, принадлежащая верхней пешке
    // (пешки стоят друг перед другом)
    chess_coord coord;
    if (one.letter != two.letter) {
        coord.letter = coord.digit = -1;
        return coord;
    }
    coord.letter = one.letter;
    int i;
    int j;
    if (one.digit < two.digit) {
        i = one.digit;
        j = two.digit;
    } else {
        i = two.digit;
        j = one.digit;
    }
    while (i <= j) {
        i++;
        j--;
    }
    coord.digit = i;
    return coord;
}

int find_pawn_way(chess_coord one, chess_coord two) {
    if (one.letter != two.letter) {
        return -1;
    }
    return 1;
}

#pragma region CHECK

void check_pawns_meet_function() {
    print_deck();
    chess_coord one;
    chess_coord two;
    input_chess_coord(&one);
    input_chess_coord(&two);
    chess_coord coord = get_pawns_meet_pos(one, two);
    output_chess_coord(&coord);
}

void check_pawns_find_way() {
    print_deck();
    chess_coord one;
    chess_coord two;
    input_chess_coord(&one);
    input_chess_coord(&two);
    printf("%1d", find_pawn_way(one, two));
}

void check_pawns_permutations() {
    print_deck();
    chess_coord one;
    input_chess_coord(&one);
    chess_coord_array* array = get_pawn_permutations(one);
    for (int i = 0; i < array->size; i++)
        output_chess_coord(&array->coords[i]);
}

#pragma endregion
#endif //CHESS_PAWN_H