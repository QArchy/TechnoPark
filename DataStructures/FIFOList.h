#ifndef TECHNOPARK_FIFO_LIST_H
#define TECHNOPARK_FIFO_LIST_H
#include "DoublyLinkedList.h"

typedef struct FIFOList {
    DoublyLinkedList lst; // очередь на основе списка
} FIFOList;

void init_FIFOList(FIFOList* fifo) {
    init_dlist(&fifo->lst); // инициализируем список
}

void clear_FIFOList(FIFOList* fifo) {
    dlist_clear(&fifo->lst); // чистим список
}

void enqueue(FIFOList* fifo, int el) {
    add_first(&fifo->lst, el); // добавляем элемент в начало списка
}

int dequeue(FIFOList* fifo) {
    int last = *get_last(&fifo->lst); // берем последний элемент списка
    remove_last(&fifo->lst); // удаляем последний элемент списка
    return last; // возвращаем значение
}

int peek(FIFOList* fifo) {
    // берем последний элемент списка
    return *get_last(&fifo->lst); // и возвращаем значение
}

void test_FIFOList() {
    FIFOList fifo;
    init_FIFOList(&fifo);
    clear_FIFOList(&fifo);
    init_FIFOList(&fifo);

    for (int i = 0; i < 10; i++)
        enqueue(&fifo, i);
    printf("Peek = %d\n", peek(&fifo));

    putchar('\n');
    for (int i = 0; i < 5; i++)
        printf("Pop = %d\n", dequeue(&fifo));

    putchar('\n');
    printf("Peek = %d\n", peek(&fifo));

    clear_FIFOList(&fifo);
}

#endif //TECHNOPARK_FIFO_LIST_H