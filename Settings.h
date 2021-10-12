#ifndef CHESS_SETTINGS_H
#define CHESS_SETTINGS_H
#include <stdlib.h>
#include <stdio.h>

const int MAX_N = 8;
const int PAWN_CODE = 6;
const int KNIGHT_CODE = 5;

typedef struct chess_coord {
    int digit;
    int letter;
} chess_coord;

typedef struct chess_coord_array {
    chess_coord* coords;
    int size;
    int factual_size;
} chess_coord_array;

int check_border(chess_coord coord) {
    if (coord.digit < 0 || coord.digit > 8)
        return -1;
    if (coord.letter < 0 || coord.letter > 8)
        return -1;
    return 1;
}

void input_chess_coord(chess_coord* coord) {
    printf("Input digit : ");
    scanf("%d", &coord->digit);
    getc(stdin);
    printf("Input letter : ");
    char c;
    scanf("%c", &c);
    coord->letter = c - 64;
    getc(stdin);
}

void resize_array(chess_coord_array*** array, int new_size) {
    chess_coord_array* tmp = (chess_coord_array*)calloc(1, sizeof(chess_coord_array));
    tmp->coords = (chess_coord*)calloc((*(*array))->size, sizeof(chess_coord));
    for (int i = 0; i < (*(*array))->size; i++) {
        tmp->coords[i].digit = (*(*array))->coords[i].digit;
        tmp->coords[i].letter = (*(*array))->coords[i].letter;
    }

    free((*(*array))->coords);
    int tmp_factual_size = (*(*array))->factual_size;
    free((*(*array)));
    (*(*array)) = (chess_coord_array*)calloc(1, sizeof(chess_coord_array));
    (*(*array))->size = new_size;
    (*(*array))->factual_size = tmp_factual_size;
    (*(*array))->coords = (chess_coord*)calloc((*(*array))->size, sizeof(chess_coord));

    for (int i = 0; i < (*(*array))->factual_size; i++)
        (*(*array))->coords[i] = tmp->coords[i];

    free(tmp->coords);
    free(tmp);
}

void add_coord_to_array(chess_coord_array** array, chess_coord* coord) {
    if ((*array)->factual_size == (*array)->size)
        resize_array(&array, (*array)->size + (*array)->size / 10 + 1);
    (*array)->coords[(*array)->factual_size++] = *coord;
}

void output_chess_coord(chess_coord* coord) {
    printf("Digit : %1d\t", coord->digit);
    printf("Letter : %1c\n", coord->letter + 65);
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