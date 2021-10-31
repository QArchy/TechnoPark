#ifndef TECHNOPARK_CHESS_COORD_H
#define TECHNOPARK_CHESS_COORD_H

typedef struct chess_coord {
    int digit; // координата по оси у
    int letter; // координата по оси х
} chess_coord;

int compare_coords(chess_coord one, chess_coord two) {
    if (one.digit == two.digit && one.letter == two.letter)
        return 1; // если поля координат совпадаю, вернем 1
    return 0;
}

void input_chess_coord(chess_coord* coord) {
    printf("Input digit >> ");
    scanf("%u", &coord->digit); // ввод цифры
    getchar();
    assert(coord->digit >= MIN_N); // проверка выхода на границы
    assert(coord->digit <= MAX_N);

    printf("Input letter >> ");
    char c;
    scanf("%c", &c); // ввод буквы
    getchar();
    coord->letter = 0; // приводим char к int
    if (c >= 65 && c <= 72)
        coord->letter = c - 64;
    if (c >= 97 && c <= 104)
        coord->letter = c - 96;
    assert(coord->letter != 0); // проверка корректности ввода
}

void output_chess_coord(chess_coord coord) {
    printf("Digit : %d\t", coord.digit); // вывод цифры
    printf("Letter : %c\n", (char)coord.letter + 64); // вывод буквы
}

#endif //TECHNOPARK_CHESS_COORD_H
