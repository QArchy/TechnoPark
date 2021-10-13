#ifndef TECHNOPARK_CHESS_COORD_H
#define TECHNOPARK_CHESS_COORD_H

typedef struct chess_coord {
    int digit;
    int letter;
} chess_coord;

void assign_coord(chess_coord* coord, int digit, int letter) {
    (*coord).digit = digit;
    (*coord).letter = letter;
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

void output_chess_coord(chess_coord* coord) {
    printf("Digit : %1d\t", coord->digit);
    printf("Letter : %1c\n", coord->letter + 64);
}

#endif //TECHNOPARK_CHESS_COORD_H
