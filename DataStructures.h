#ifndef CHESS_SETTINGS_H
#define CHESS_SETTINGS_H
#include <stdlib.h>
#include <stdio.h>
#include "chess_coord.h"
#include "chess_coord_tree.h"
#include "chess_coord_array.h"
#include "chess_coord_tree_array.h"
const int MAX_N = 8;
const int PAWN_CODE = 1;
const int KNIGHT_CODE = 2;

int check_border(chess_coord coord) {
    if (coord.digit <= 0 || coord.digit > 8)
        return -1;
    if (coord.letter <= 0 || coord.letter > 8)
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

#endif //CHESS_SETTINGS_H