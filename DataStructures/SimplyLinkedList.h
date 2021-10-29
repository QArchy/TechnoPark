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
    SimplyLinkedListNode* tmp = lst->head;
    while(tmp != NULL)
        tmp = tmp->pnext;
    lst->tail = tmp = (SimplyLinkedListNode*)calloc(1, sizeof(SimplyLinkedListNode));
    lst->tail->data = el;
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
        if (tmp->pnext == NULL) // если элемента нет
            return -1;
        tmp = tmp->pnext;
    }
    if (tmp->pnext == lst->tail) { // если элемент в tail
        free(lst->tail);
        lst->tail = tmp;
        lst->tail->pnext = NULL;
        return 1;
    }
    SimplyLinkedListNode* tmp_next = tmp->pnext; // если элемент в середине
    free(tmp_next);
    tmp->pnext = tmp->pnext->pnext;
}

void printlst(SimplyLinkedList* lst) {
    SimplyLinkedListNode* tmp = lst->head;
    putchar('[');
    while(tmp != NULL) {
        printf("%d", tmp->data);
        tmp = tmp->pnext;
    }
    putchar(']');
}

#endif //TECHNOPARK_SIMPLY_LINKED_LIST_H