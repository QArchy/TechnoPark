#include "Chess.h"

int main() {
    while (1) {
        figure_info info_1;
        input_figure_info(&info_1);
        figure_info info_2;
        input_figure_info(&info_2);
        check_meet_pos(info_1, info_2);
    }
    return 0;
}