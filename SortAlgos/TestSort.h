#ifndef TECHNOPARK_TEST_SORT_H
#define TECHNOPARK_TEST_SORT_H
#include "../DataStructures/IntArray.h"

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

#include "Comb.h"
#include "Insertion.h"
#include "Merge.h"
#include "Quick.h"
#include "Select.h"
#include "Shaker.h"

void test_sort(void(*SortFunc)(IntArray*)) {
    IntArray arr;
    const int SIZE = 10;
    alloc_int_array(&arr, 10);

    for (int i = 0; i < SIZE; i++) {
        if (i % 2 == 0)
            add_to_int_array(&arr, - SIZE - i);
        else
            add_to_int_array(&arr, SIZE - i);
        add_to_int_array(&arr, i);
    }
    print_int_array(&arr); putchar('\n');

    SortFunc(&arr);

    print_int_array(&arr);
    free_int_array(&arr);
}

#endif //TECHNOPARK_TEST_SORT_H
