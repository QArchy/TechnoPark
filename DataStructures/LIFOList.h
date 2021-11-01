#ifndef TECHNOPARK_LIFO_LIST_H
#define TECHNOPARK_LIFO_LIST_H
#include "DoublyLinkedList.h"

typedef struct LIFOList {
    DoublyLinkedList lst; // стэк на основе списка
} LIFOList;

void init_LIFOList(LIFOList* lifo) {
    init_dlist(&lifo->lst); // инициализируем список
}

void clear_LIFOList(LIFOList* lifo) {
    dlist_clear(&lifo->lst); // чистим список
}

void push(LIFOList* lifo, int el) {
    add_last(&lifo->lst, el); // добавлям в конец списка
}

int pop(LIFOList* lifo) {
    int last = *get_last(&lifo->lst); // берем последний элемент списка
    remove_last(&lifo->lst); // удаляем последний элемент списка
    return last; // возвращаем значение
}

int peek(LIFOList* lifo) {
    // берем последний элемент списка
    return *get_last(&lifo->lst); // и возвращаем значение
}

void test_LIFOList() {
    LIFOList lifo;
    init_LIFOList(&lifo);
    clear_LIFOList(&lifo);
    init_LIFOList(&lifo);

    for (int i = 0; i < 10; i++) {
        push(&lifo, i);
        printf("Peek = %d\n", peek(&lifo));
    }

    putchar('\n');
    for (int i = 0; i < 5; i++)
        printf("Pop = %d\n", pop(&lifo));

    putchar('\n');
    printf("Peek = %d\n", peek(&lifo));

    clear_LIFOList(&lifo);
}

#endif //TECHNOPARK_LIFO_LIST_H