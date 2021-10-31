#include "SortAlgos/Bubble.h"

int main() {
    IntArray arr;
    const int SIZE = 10;
    alloc_int_array(&arr, 10);

    for (int i = 0; i < SIZE; i++)
        add_to_int_array(&arr, SIZE - i);
    print_int_array(&arr); putchar('\n');

    BubbleSort(&arr);

    print_int_array(&arr);
    free_int_array(&arr);
    return 0;
}