#ifndef TECHNOPARK_DOUBLY_LINKED_LIST_H
#define TECHNOPARK_DOUBLY_LINKED_LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct DoublyLinkedListNode {
    int data;
    struct DoublyLinkedListNode* pnext;
    struct DoublyLinkedListNode* pprev;
} DoublyLinkedListNode;

typedef struct DoublyLinkedList {
    DoublyLinkedListNode* head;
    DoublyLinkedListNode* tail;
} DoublyLinkedList;

void init_dlist(DoublyLinkedList* lst) {
    lst->tail = lst->head = (DoublyLinkedListNode*)calloc(1, sizeof(DoublyLinkedListNode));
    lst->head->pnext = NULL;
    lst->head->pprev = NULL;
}

void add_first(DoublyLinkedList* lst, int el) {
    lst->head->pprev = (DoublyLinkedListNode*)calloc(1, sizeof(DoublyLinkedListNode));
    lst->head->pprev->pnext = lst->head;
    lst->head = lst->head->pprev;
    lst->head->pprev = NULL;
    lst->head->data = el;
}

void add_last(DoublyLinkedList* lst, int el) {
    lst->tail->pnext = (DoublyLinkedListNode*)calloc(1, sizeof(DoublyLinkedListNode));
    lst->tail->data = el;
    lst->tail->pnext->pprev = lst->tail;
    lst->tail = lst->tail->pnext;
    lst->tail->pnext = NULL;
}

int dlist_contains(DoublyLinkedList* lst, int el) {
    DoublyLinkedListNode* tmp = lst->head;
    while (tmp != lst->tail) {
        if (tmp->data == el)
            return 1;
        tmp = tmp->pnext;
    }
    return -1;
}

int dlist_assign(DoublyLinkedList* lst, size_t ind, int el) {
    DoublyLinkedListNode* tmp = lst->head;
    while (ind != 1) {
        if (tmp == lst->tail)
            return -1;
        tmp = tmp->pnext;
        ind--;
    }
    tmp->data = el;
    return 1;
}

void dlist_clear(DoublyLinkedList* lst) {
    while (lst->head != NULL) {
        DoublyLinkedListNode* tmp = lst->head;
        lst->head = lst->head->pnext;
        free(tmp);
    }
    lst->tail = lst->head;
}

int remove_first(DoublyLinkedList* lst) {
    if (lst->head == lst->tail)
        return -1;
    lst->head = lst->head->pnext;
    free(lst->head->pprev);
    lst->head->pprev = NULL;
    return 1;
}

int remove_last(DoublyLinkedList* lst) {
    if (lst->head == lst->tail)
        return -1;
    lst->tail = lst->tail->pprev;
    free(lst->tail->pnext);
    lst->tail->pnext = NULL;
    return 1;
}

int dlist_remove_el(DoublyLinkedList* lst, int el) {
    if (lst->head == lst->tail)
        return -1;
    if (lst->head->data == el) // если элемент в начале
        return remove_first(lst);

    DoublyLinkedListNode* tmp = lst->head;
    while (tmp->pnext->data != el) {
        tmp = tmp->pnext;
        if (tmp->pnext == lst->tail) // если элемента нет
            return -1;
    }
    if (tmp->pnext->pnext == lst->tail) // если элемент в конце
        return remove_last(lst);
    DoublyLinkedListNode* tmp_next = tmp->pnext; // если элемент в середине
    tmp->pnext = tmp->pnext->pnext;
    tmp->pnext->pnext->pprev = tmp->pnext;
    free(tmp_next);
    return 1;
}

void print_dlist(DoublyLinkedList* lst) {
    if (lst->head == lst->tail) {
        printf("List is empty\n");
        return;
    }
    DoublyLinkedListNode* tmp = lst->head;
    putchar('[');
    while(tmp != lst->tail) {
        printf("%d", tmp->data);
        tmp = tmp->pnext;
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

    printf("List remove [%d] ? >> [%d]\n", 34, dlist_remove_el(&lst, 34));
    print_dlist(&lst);
    putchar('\n');

    printf("List contains [%d] ? >> [%d]\n", 34, dlist_contains(&lst, 34));
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