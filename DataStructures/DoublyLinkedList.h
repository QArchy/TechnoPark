#ifndef TECHNOPARK_DOUBLY_LINKED_LIST_H
#define TECHNOPARK_DOUBLY_LINKED_LIST_H
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct DoublyLinkedListNode {
    int data; // данные
    struct DoublyLinkedListNode* pnext; // указатель на следующий узел
    struct DoublyLinkedListNode* pprev; // указатель на предыдущий узел
} DoublyLinkedListNode;

typedef struct DoublyLinkedList {
    DoublyLinkedListNode* head; // указатель на начало
    DoublyLinkedListNode* tail; // указатель на конец
} DoublyLinkedList;

void init_dlist(DoublyLinkedList* lst) {
    // записывает head и tail NULL
    lst->tail = lst->head = NULL;
}

void add_first(DoublyLinkedList* lst, int el) {
    if (lst->head == NULL) { // создаем в head новый узел
        lst->head = (DoublyLinkedListNode*)calloc(1, sizeof(DoublyLinkedListNode));
        lst->head->data = el; // записываем данные
        lst->head->pprev = NULL; // зануляем указатель на предыдущий узел
        lst->head->pnext = NULL; // зануляем указатель на следующий узел
        lst->tail = lst->head; // ставим tail на head
        return;
    }
    // поле pprev узла head указывает на новый узел
    lst->head->pprev = (DoublyLinkedListNode*)calloc(1, sizeof(DoublyLinkedListNode));
    lst->head->pprev->data = el; // записываем данные
    lst->head->pprev->pprev = NULL; // зануляем указатель нового узла на предыдущий узел
    lst->head->pprev->pnext = lst->head; // поле pnext нового узла указывает на head
    lst->head = lst->head->pprev; // передвигаем head на новый узел
}

void add_last(DoublyLinkedList* lst, int el) {
    if (lst->head == NULL) { // создаем в head новый узел
        lst->head = (DoublyLinkedListNode*)calloc(1, sizeof(DoublyLinkedListNode));
        lst->head->data = el; // записываем данные
        lst->head->pprev = NULL; // зануляем указатель на предыдущий узел
        lst->head->pnext = NULL; // зануляем указатель на следующий узел
        lst->tail = lst->head; // ставим tail на head
        return;
    }
    // поле pnext узда tail указывает на новый узел
    lst->tail->pnext = (DoublyLinkedListNode*)calloc(1, sizeof(DoublyLinkedListNode));
    lst->tail->pnext->data = el; // записываем данные
    lst->tail->pnext->pprev = lst->tail; // поле pprev нового узла указывает на tail
    lst->tail->pnext->pnext = NULL; // зануляем поле next нового узла
    lst->tail = lst->tail->pnext; // двигаем tail на новый узел
}

int dlist_contains(DoublyLinkedList* lst, int el) {
    assert(lst->head != NULL);
    DoublyLinkedListNode* tmp = lst->head; // создаем временный итератор
    while (tmp != NULL) { // пока не дошли до конца
        if (tmp->data == el) // ищем элемент
            return 1;
        tmp = tmp->pnext; // идем вперед
    }
    return -1;
}

int dlist_assign(DoublyLinkedList* lst, size_t ind, int el) {
    assert(lst->head != NULL);
    if (ind == 0) { // если элемент в начале
        lst->head->data = el;
        return 1;
    }

    DoublyLinkedListNode* tmp = lst->head; // создаем временный итератор
    while (ind > 0) { // пока не нашли нужный узел
        if (tmp == NULL) // если дошли до конца
            return -1; // неудача
        tmp = tmp->pnext; // идем вперед
        ind--;
    }
    tmp->data = el; // записывае м данные
    return 1;
}

void dlist_clear(DoublyLinkedList* lst) {
    while (lst->head != NULL) { // пока не дошли до конца
        DoublyLinkedListNode* tmp = lst->head; // запоминаем head
        lst->head = lst->head->pnext; // двигаем head вперед
        free(tmp); // удаляем бывший head
    }
    lst->tail = lst->head; // восстанавливаем состояние списка до вызова функции init
}

int remove_first(DoublyLinkedList* lst) {
    assert(lst->head != NULL);
    if (lst->head == lst->tail) {
        dlist_clear(lst);
        return 1;
    }
    lst->head = lst->head->pnext; // двигаем head вперед
    free(lst->head->pprev); // удаляем предыдущий элемент
    lst->head->pprev = NULL; // и зануляем указатель
    return 1;
}

int remove_last(DoublyLinkedList* lst) {
    assert(lst->head != NULL);
    if (lst->head == lst->tail) {
        dlist_clear(lst);
        return 1;
    }
    lst->tail = lst->tail->pprev; //двигаем tail назад
    free(lst->tail->pnext); // удаляем следующий элемент
    lst->tail->pnext = NULL; //и зануляем указатель
    return 1;
}

int dlist_remove_el(DoublyLinkedList* lst, int el) {
    assert(lst->head != NULL);
    if (lst->head->data == el) // если элемент в начале
        return remove_first(lst); // вызываем удаление из начала

    DoublyLinkedListNode* tmp = lst->head; // создаем временный итератор
    while (tmp->pnext->data != el) { // пока следующий элемент не искомый
        tmp = tmp->pnext; // идем вперед
        if (tmp->pnext == NULL) // если элемента нет
            return -1; // то его нет
    }
    if (tmp->pnext == lst->tail) // если элемент в конце
        return remove_last(lst); // вызываем удаление конца
    DoublyLinkedListNode* tmp_next = tmp->pnext; // если элемент в середине
    tmp->pnext = tmp->pnext->pnext; // перебрасываем указатель на следующий элемент через 1
    tmp->pnext->pnext->pprev = tmp->pnext; // связываем элемент после искомого с предыдущим
    free(tmp_next); // удаляем искомый узел
    return 1;
}

int* get_first(DoublyLinkedList* lst) {
    assert(lst->head != NULL);
    return &lst->head->data;
}

int* get_last(DoublyLinkedList* lst) {
    assert(lst->head != NULL);
    return &lst->tail->data;
}

int* get(DoublyLinkedList* lst, size_t ind) {
    assert(lst->head != NULL);
    if (ind == 0) // если элемент в начале
        return &lst->head->data; // возвращаем первый элемент
    DoublyLinkedListNode* tmp = lst->head; // создаем временный итератор
    while (ind > 0) { // пока индекс больше нуля
        tmp = tmp->pnext; // идем вперед
        assert(tmp != NULL);
        ind--;
    }
    return &tmp->data;
}

void print_dlist(DoublyLinkedList* lst) {
    if (lst->head == NULL) { // если список пуст
        printf("List is empty\n"); // то он пуст
        return;
    }
    DoublyLinkedListNode* tmp = lst->head; // создаем временный итератор
    putchar('[');
    while(tmp != NULL) { // пока не дошли до конца
        printf("%d", tmp->data); // выводим данные
        tmp = tmp->pnext; // идем вперед
    }
    putchar(']');
}

void test_DoublyLinkedList() {
    DoublyLinkedList lst;
    init_dlist(&lst);
    print_dlist(&lst);
    putchar('\n');

    dlist_clear(&lst);
    init_dlist(&lst);
    print_dlist(&lst);
    putchar('\n');

    add_first(&lst, 3);
    add_last(&lst, 4);
    add_first(&lst, 2);
    add_last(&lst, 5);
    add_first(&lst, 1);
    add_last(&lst, 6);
    add_first(&lst, 0);
    print_dlist(&lst);
    putchar('\n');

    printf("\nList remove [%d] ? >> [%d]\n", 0, dlist_remove_el(&lst, 0));
    print_dlist(&lst);
    putchar('\n');

    printf("\nList remove [%d] ? >> [%d]\n", 6, dlist_remove_el(&lst, 6));
    print_dlist(&lst);
    putchar('\n');

    printf("\nList remove [%d] ? >> [%d]\n", 3, dlist_remove_el(&lst, 3));
    print_dlist(&lst);
    putchar('\n');

    printf("\nList contains [%d] ? >> [%d]\n", 1, dlist_contains(&lst, 1));
    print_dlist(&lst);
    putchar('\n');

    printf("\nList contains [%d] ? >> [%d]\n", 5, dlist_contains(&lst, 5));
    print_dlist(&lst);
    putchar('\n');

    printf("\nList contains [%d] ? >> [%d]\n", 2, dlist_contains(&lst, 2));
    print_dlist(&lst);
    putchar('\n');

    printf("\nList remove first >> [%d]\n", remove_first(&lst));
    print_dlist(&lst);
    putchar('\n');

    printf("\nList remove last >> [%d]\n", remove_last(&lst));
    print_dlist(&lst);
    putchar('\n');

    dlist_clear(&lst);
    init_dlist(&lst);
    print_dlist(&lst);
    putchar('\n');
}

#endif //TECHNOPARK_DOUBLY_LINKED_LIST_H