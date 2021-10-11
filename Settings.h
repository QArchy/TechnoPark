#ifndef CHESS_SETTINGS_H
#define CHESS_SETTINGS_H
#include <stdlib.h>
#include <stdio.h>

const int MAX_N = 8;
const int PAWN_CODE = 6;

typedef struct chess_coord {
    int digit;
    int letter;
} chess_coord;

typedef struct chess_coord_array {
    chess_coord* coords;
    int size;
} chess_coord_array;

void input_chess_coord(chess_coord* coord) {
    printf("Input digit : ");
    scanf("%d", &coord->digit);
    getc(stdin);
    printf("Input letter : ");
    char c;
    scanf("%c", &c);
    coord->letter = c - 65;
    getc(stdin);
}

void resize_array(chess_coord_array* array, int new_size) {
    chess_coord_array* tmp = (chess_coord_array*)calloc(1, sizeof(chess_coord_array));
    tmp->coords = (chess_coord*)calloc(array->size, sizeof(chess_coord));
    for (int i = 0; i < array->size; i++) {
        tmp->coords[i].digit = array->coords[i].digit;
        tmp->coords[i].letter = array->coords[i].letter;
    }

    free(array->coords);
    free(array);
    array = (chess_coord_array*)calloc(1, sizeof(chess_coord_array));
    array->coords = (chess_coord*)calloc(new_size, sizeof(chess_coord));

    for (int i = 0; i < array->size; i++)
        array->coords[i] = tmp->coords[i];

    free(tmp->coords);
    free(tmp);
}

void output_chess_coord(chess_coord* coord) {
    printf("Vertical coord : %1d\t", coord->digit);
    printf("Horizontal coord : %1d\n", coord->letter);
}

void output_array(chess_coord_array* array) {
    printf("Permutations : \n");
    for (int i = 0; i < array->size; i++) {
        output_chess_coord(&array->coords[i]);
    }
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
        printf("\n");
    }
}

#endif //CHESS_SETTINGS_H