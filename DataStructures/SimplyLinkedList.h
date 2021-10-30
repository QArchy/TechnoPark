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

void init_list(SimplyLinkedList* lst) {
    lst->tail = lst->head = (SimplyLinkedListNode*)calloc(1, sizeof(SimplyLinkedListNode));
    lst->head->pnext = NULL;
}

void add(SimplyLinkedList* lst, int el) {
    lst->tail->pnext = (SimplyLinkedListNode*)calloc(1, sizeof(SimplyLinkedListNode));
    lst->tail->data = el;
    lst->tail = lst->tail->pnext;
    lst->tail->pnext = NULL;
}

int contains(SimplyLinkedList* lst, int el) {
    SimplyLinkedListNode* tmp = lst->head;
    while (tmp != NULL) {
        if (tmp->data == el)
            return 1;
        tmp = tmp->pnext;
    }
    return -1;
}

void clear(SimplyLinkedList* lst) {
    while (lst->head != NULL) {
        SimplyLinkedListNode* tmp = lst->head;
        lst->head = lst->head->pnext;
        free(tmp);
    }
    lst->tail = lst->head;
}

int remove_el(SimplyLinkedList* lst, int el) {
    if (lst->head == lst->tail)
        return -1;
    if (lst->head->data == el) { // если элемент в начале
        if (lst->head == lst->tail) { // и единстенный
            free(lst->head);
            lst->tail = lst->head = NULL;
            return 1;
        }
        SimplyLinkedListNode* tmp = lst->head;
        lst->head = lst->head->pnext;
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

void printlst(SimplyLinkedList* lst) {
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
    init_list(&lst);
    printlst(&lst);
    putchar('\n');

    clear(&lst);
    init_list(&lst);
    printlst(&lst);
    putchar('\n');

    printf("List remove [%d] ? >> [%d]\n", 34, remove_el(&lst, 34));
    printlst(&lst);
    putchar('\n');

    printf("List contains [%d] ? >> [%d]\n", 34, contains(&lst, 34));
    printlst(&lst);
    putchar('\n');

    add(&lst, 0);
    add(&lst, 1);
    add(&lst, 2);
    add(&lst, 3);
    add(&lst, 4);
    add(&lst, 5);
    add(&lst, 6);
    printlst(&lst);
    putchar('\n');

    printf("\nList remove [%d] ? >> [%d]\n", 0, remove_el(&lst, 0));
    printlst(&lst);
    putchar('\n');

    printf("\nList remove [%d] ? >> [%d]\n", 6, remove_el(&lst, 6));
    printlst(&lst);
    putchar('\n');

    printf("\nList remove [%d] ? >> [%d]\n", 3, remove_el(&lst, 3));
    printlst(&lst);
    putchar('\n');

    printf("\nList contains [%d] ? >> [%d]\n", 1, contains(&lst, 1));
    printlst(&lst);
    putchar('\n');

    printf("\nList contains [%d] ? >> [%d]\n", 5, contains(&lst, 5));
    printlst(&lst);
    putchar('\n');

    printf("\nList contains [%d] ? >> [%d]\n", 2, contains(&lst, 2));
    printlst(&lst);
    putchar('\n');

    clear(&lst);
    init_list(&lst);
    printlst(&lst);
    putchar('\n');
}

#endif //TECHNOPARK_SIMPLY_LINKED_LIST_H