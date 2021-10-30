#ifndef TECHNOPARK_SIMPLY_LINKED_LIST_H
#define TECHNOPARK_SIMPLY_LINKED_LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct SimplyLinkedListNode {
    int data;
    struct SimplyLinkedListNode* pnext;
} SimplyLinkedListNode;

typedef struct SimplyLinkedList {
    SimplyLinkedListNode* head;
    SimplyLinkedListNode* tail;
} SimplyLinkedList;

void init_slist(SimplyLinkedList* lst) {
    lst->tail = lst->head = (SimplyLinkedListNode*)calloc(1, sizeof(SimplyLinkedListNode));
    lst->head->pnext = NULL;
}

void add_to_slist(SimplyLinkedList* lst, int el) {
    lst->tail->pnext = (SimplyLinkedListNode*)calloc(1, sizeof(SimplyLinkedListNode));
    lst->tail->data = el;
    lst->tail = lst->tail->pnext;
    lst->tail->pnext = NULL;
}

int slist_contains(SimplyLinkedList* lst, int el) {
    SimplyLinkedListNode* tmp = lst->head;
    while (tmp != lst->tail) {
        if (tmp->data == el)
            return 1;
        tmp = tmp->pnext;
    }
    return -1;
}

int slist_assign(SimplyLinkedList* lst, size_t ind, int el) {
    SimplyLinkedListNode* tmp = lst->head;
    while (ind != 1) {
        if (tmp == lst->tail)
            return -1;
        tmp = tmp->pnext;
        ind--;
    }
    tmp->data = el;
    return 1;
}

void slist_clear(SimplyLinkedList* lst) {
    while (lst->head != lst->tail) {
        SimplyLinkedListNode* tmp = lst->head;
        lst->head = lst->head->pnext;
        free(tmp);
    }
    lst->tail = lst->head;
}

int slist_remove_el(SimplyLinkedList* lst, int el) {
    if (lst->head == lst->tail)
        return -1;
    if (lst->head->data == el) { // если элемент в начале
        if (lst->head->pnext == lst->tail) { // и единстенный
            free(lst->head);
            lst->head = lst->tail;
            return 1;
        }
        SimplyLinkedListNode* tmp = lst->head;
        lst->head = lst->head->pnext;
        free(tmp);
        return 1;
    }

    SimplyLinkedListNode* tmp = lst->head;
    while (tmp->pnext->data != el) {
        tmp = tmp->pnext;
        if (tmp->pnext == lst->tail) // если элемента нет
            return -1;
    }
    if (tmp->pnext->pnext == lst->tail) { // если элемент в конце
        free(lst->tail);
        lst->tail = tmp->pnext;
        lst->tail->pnext = NULL;
        return 1;
    }
    SimplyLinkedListNode* tmp_next = tmp->pnext; // если элемент в середине
    tmp->pnext = tmp->pnext->pnext;
    free(tmp_next);
    return 1;
}

void print_slist(SimplyLinkedList* lst) {
    if (lst->head == lst->tail) {
        printf("List is empty\n");
        return;
    }
    SimplyLinkedListNode* tmp = lst->head;
    putchar('[');
    while(tmp != lst->tail) {
        printf("%d", tmp->data);
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