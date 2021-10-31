#ifndef TECHNOPARK_SIMPLY_LINKED_LIST_H
#define TECHNOPARK_SIMPLY_LINKED_LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct SimplyLinkedListNode {
    int data; // данные
    struct SimplyLinkedListNode* pnext; // указатель на следующий элемент
} SimplyLinkedListNode;

typedef struct SimplyLinkedList {
    SimplyLinkedListNode* head; // указатель на начало
    SimplyLinkedListNode* tail; // флаг конца списка
} SimplyLinkedList;

void init_slist(SimplyLinkedList* lst) { // выделяем память под новый элемент в head
    lst->tail = lst->head = (SimplyLinkedListNode*)calloc(1, sizeof(SimplyLinkedListNode));
    lst->head->pnext = NULL; // зануляем указатель на следующий элемент
}

void add_to_slist(SimplyLinkedList* lst, int el) { // выделяем память в tail->next
    lst->tail->pnext = (SimplyLinkedListNode*)calloc(1, sizeof(SimplyLinkedListNode));
    lst->tail->data = el; // записывает в конец данные
    lst->tail = lst->tail->pnext; // двигаем флаг конца списка вперед
    lst->tail->pnext = NULL; // зануляем указатель на следующий элемент
}

int slist_contains(SimplyLinkedList* lst, int el) {
    SimplyLinkedListNode* tmp = lst->head; // создаем временный итератор
    while (tmp != lst->tail) { // пока не дошли до конца
        if (tmp->data == el) // ищем элемент
            return 1;
        tmp = tmp->pnext; // идем вперед
    }
    return -1;
}

int slist_assign(SimplyLinkedList* lst, size_t ind, int el) {
    SimplyLinkedListNode* tmp = lst->head; // создаем временный итератор
    while (ind != 1) { // пока не дошли до нужного элемента
        if (tmp == lst->tail) // проверка выхода за границы списка
            return -1;
        tmp = tmp->pnext; // идем вперед
        ind--;
    }
    tmp->data = el; // записываем значение
    return 1;
}

void slist_clear(SimplyLinkedList* lst) {
    while (lst->head != lst->tail) { // пока не дошли до конца
        SimplyLinkedListNode* tmp = lst->head; // запоминаем head
        lst->head = lst->head->pnext; // двигаем head вперед
        free(tmp); // чистим память из под бывшего начала
    }
    lst->tail = lst->head; // восстанавливаем состояние списка до вызова функции init
}

int slist_remove_el(SimplyLinkedList* lst, int el) {
    if (lst->head == lst->tail) // если список пуст
        return -1; // неудача
    if (lst->head->data == el) { // если элемент в начале
        if (lst->head->pnext == lst->tail) { // и единстенный
            free(lst->head); // чистим глову
            lst->head = lst->tail; // восстанавливаем состояние списка до вызова функции init
            return 1;
        }
        SimplyLinkedListNode* tmp = lst->head; // запоминаем head
        lst->head = lst->head->pnext; // двигаем head вперед
        free(tmp); // чистим память из под бывшего начала
        return 1;
    }

    SimplyLinkedListNode* tmp = lst->head; // создаем временный итератор
    while (tmp->pnext->data != el) { // пока следующий элемент не искомый
        tmp = tmp->pnext; // идем вперед
        if (tmp->pnext == lst->tail) // если элемента нет
            return -1; // неудача
    }
    if (tmp->pnext->pnext == lst->tail) { // если элемент в конце
        free(lst->tail); // чистим конец
        lst->tail = tmp->pnext; // двигаем tail назад
        lst->tail->pnext = NULL; // обновляем поле tail->next
        return 1;
    } // если элемент в середине
    SimplyLinkedListNode* tmp_next = tmp->pnext; // запоминаем его
    tmp->pnext = tmp->pnext->pnext; // перебрасываем next через один элемент
    free(tmp_next); // удаляем искомый элемент
    return 1;
}

void print_slist(SimplyLinkedList* lst) {
    if (lst->head == lst->tail) { // если список пуст
        printf("List is empty\n"); // то он пуст
        return;
    }
    SimplyLinkedListNode* tmp = lst->head; // создаем временный итератор
    putchar('[');
    while(tmp != lst->tail) { // пока не дошли до конца
        printf("%d", tmp->data); // выводим данные
        tmp = tmp->pnext;
    }
    putchar(']');
}

void test_SimplyLinkedList() {
    SimplyLinkedList lst;
    init_slist(&lst);
    print_slist(&lst);
    putchar('\n');

    slist_clear(&lst);
    init_slist(&lst);
    print_slist(&lst);
    putchar('\n');

    printf("List remove [%d] ? >> [%d]\n", 34, slist_remove_el(&lst, 34));
    print_slist(&lst);
    putchar('\n');

    printf("List contains [%d] ? >> [%d]\n", 34, slist_contains(&lst, 34));
    print_slist(&lst);
    putchar('\n');

    add_to_slist(&lst, 0);
    add_to_slist(&lst, 1);
    add_to_slist(&lst, 2);
    add_to_slist(&lst, 3);
    add_to_slist(&lst, 4);
    add_to_slist(&lst, 5);
    add_to_slist(&lst, 6);
    print_slist(&lst);
    putchar('\n');

    printf("\nList remove [%d] ? >> [%d]\n", 0, slist_remove_el(&lst, 0));
    print_slist(&lst);
    putchar('\n');

    printf("\nList remove [%d] ? >> [%d]\n", 6, slist_remove_el(&lst, 6));
    print_slist(&lst);
    putchar('\n');

    printf("\nList remove [%d] ? >> [%d]\n", 3, slist_remove_el(&lst, 3));
    print_slist(&lst);
    putchar('\n');

    printf("\nList contains [%d] ? >> [%d]\n", 1, slist_contains(&lst, 1));
    print_slist(&lst);
    putchar('\n');

    printf("\nList contains [%d] ? >> [%d]\n", 5, slist_contains(&lst, 5));
    print_slist(&lst);
    putchar('\n');

    printf("\nList contains [%d] ? >> [%d]\n", 2, slist_contains(&lst, 2));
    print_slist(&lst);
    putchar('\n');

    slist_clear(&lst);
    init_slist(&lst);
    print_slist(&lst);
    putchar('\n');
}

#endif //TECHNOPARK_SIMPLY_LINKED_LIST_H