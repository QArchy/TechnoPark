#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H
#include "DataStructures.h"

chess_coord get_pawn_permutations(chess_coord coord) {
    chess_coord permutation = coord;
    if (coord.digit == MAX_N)
        return permutation;
    permutation.digit += 1;
    return permutation;
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
    printf("Input first pawn coord : \n");
    input_chess_coord(&one);
    printf("Input second pawn coord : \n");
    input_chess_coord(&two);
    chess_coord coord = get_pawns_meet_pos(one, two);
    output_chess_coord(&coord);
}

void check_pawn_find_way() {
    print_deck();
    chess_coord one;
    chess_coord two;
    printf("Input first coord : \n");
    input_chess_coord(&one);
    printf("Input first second coord : \n");
    input_chess_coord(&two);
    printf("%1d", find_pawn_way(one, two));
}

void check_pawn_permutations() {
    print_deck();
    chess_coord one;
    printf("Input pawn coord : \n");
    input_chess_coord(&one);
    chess_coord coord = get_pawn_permutations(one);
    output_chess_coord(&coord);
}
#pragma endregion
#endif //CHESS_PAWN_H