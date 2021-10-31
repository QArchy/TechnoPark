#ifndef TECHNOPARK_FIGURE_INFO_H
#define TECHNOPARK_FIGURE_INFO_H
#include <string.h>
#include <ctype.h>

typedef struct figure_info {
    size_t direction_up;
    size_t num_figure;
    size_t figure_code;
} figure_info;

void input_figure_info(figure_info* info) {
    printf("Input figure name (in english) : ");
    char figure_name[7];
    scanf("%s", figure_name);

    size_t i = 0;
    while (figure_name[i] != '\0') {
        figure_name[i] = (char)tolower(figure_name[i]);
        i++;
    }

    info->figure_code = 0;
    if (strcmp(figure_name, "pawn") == 0)
        info->figure_code = 1;
    else if (strcmp(figure_name, "knight") == 0)
        info->figure_code = 2;
    else if (strcmp(figure_name, "king") == 0)
        info->figure_code = 3;
    else if (strcmp(figure_name, "queen") == 0)
        info->figure_code = 4;
    else if (strcmp(figure_name, "bishop") == 0)
        info->figure_code = 5;
    else if (strcmp(figure_name, "rook") == 0)
        info->figure_code = 6;
    assert(info->figure_code != 0);

    if (info->figure_code == PAWN) {
        printf("Input pawn direction (up/down) : ");
        char direction[5];
        scanf("%s", direction);

        size_t j = 0;
        while (direction[j] != '\0') {
            direction[j] = (char) tolower(direction[j]);
            j++;
        }

        info->direction_up = 2;
        if (strcmp(direction, "up") == 0) {
            info->direction_up = 1;
        }
        else if (strcmp(direction, "down") == 0) {
            info->direction_up = 0;
        }

        assert(info->direction_up != 2);
    }
}

#endif //TECHNOPARK_FIGURE_INFO_H