#ifndef TECHNOPARK_CHESS_COORD_H
#define TECHNOPARK_CHESS_COORD_H

typedef struct chess_coord {
    int digit;
    int letter;
} chess_coord;

void assign_coord(chess_coord* coord, int digit, int letter) {
    coord->digit = digit;
    coord->letter = letter;
}

void input_chess_coord(chess_coord* coord) {
    printf("Input digit >> ");
    scanf("%d", &coord->digit);
    assert(coord->digit > 0);
    assert(coord->digit < 9);
    getc(stdin);
    printf("Input letter >> ");
    char c;
    scanf("%c", &c);
    coord->letter = 0;
    if (c >= 65 && c <= 72)
        coord->letter = c - 64;
    if (c >= 97 && c <= 104)
        coord->letter = c - 96;
    assert(coord->letter != 0);
    getc(stdin);
}

void output_chess_coord(chess_coord* coord) {
    printf("Digit : %1d\t", coord->digit);
    printf("Letter : %1c\n", coord->letter + 64);
}

#endif //TECHNOPARK_CHESS_COORD_H
