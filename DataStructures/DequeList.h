#ifndef TECHNOPARK_DEQUE_LIST_H
#define TECHNOPARK_DEQUE_LIST_H
#include <assert.h>
#include "DoublyLinkedList.h"

typedef struct DequeList {
    DoublyLinkedList lst; // дек на основе спика
} DequeList;

void init_DequeList(DequeList* deq) {
    init_dlist(&deq->lst); // инициализация списка
}

void clear_DequeList(DequeList* deq) {
    dlist_clear(&deq->lst); // очистка дека
}

void enqueue_first(DequeList* deq, int el) {
    add_first(&deq->lst, el); // добавляем элемент в начало списка
}

void enqueue_last(DequeList* deq, int el) {
    add_last(&deq->lst, el); // добавляем элемент в конец списка
}

int dequeue_first(DequeList* deq) {
    int first = *get_first(&deq->lst); // берем первый элемент списка
    remove_first(&deq->lst); // удаляем первый элемент списка
    return first; // возвращаем значение
}

int dequeue_last(DequeList* deq) {
    int last = *get_last(&deq->lst); // берем последний элемент списка
    remove_last(&deq->lst); // удаляем последний элемент списка
    return last; // возвращаем значение
}

int peek_first(DequeList* deq) {
    // берем первый элемент списка
    return *get_first(&deq->lst); // и возвращаем значение
}

int peek_last(DequeList* deq) {
    // берем последний элемент списка
    return *get_last(&deq->lst); // и возвращаем значение
}

void test_DequeList() {
    DequeList deq;
    init_DequeList(&deq);
    clear_DequeList(&deq);
    init_DequeList(&deq);

    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            enqueue_first(&deq, 10 - i);
            printf("PeekFirst = %d\n", peek_first(&deq));
        }
        else {
            enqueue_last(&deq, i);
            printf("PeekLast = %d\n", peek_last(&deq));
        }
    }
    putchar('\n');

    for (int i = 0; i < 5; i++) {
        printf("[%d]DequeueFirst = %d\n", i, dequeue_first(&deq));
        printf("[%d]DequeueLast = %d\n", i, dequeue_last(&deq));
    }

    clear_DequeList(&deq);
}

#endif //TECHNOPARK_DEQUE_LIST_H