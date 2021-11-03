#ifndef TECHNOPARK_BALANCED_BINARY_SEARCH_TREE_H
#define TECHNOPARK_BALANCED_BINARY_SEARCH_TREE_H
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "IntArray.h"

typedef struct BinaryTreeNode {
    int value; // данные
    size_t height; // высота данного узла
    struct BinaryTreeNode* right; // левый узел
    struct BinaryTreeNode* left; // правый узел
} BinaryTreeNode;

size_t max(size_t a, size_t b) {
    if (a > b)
        return a;
    return b;
}

size_t height(BinaryTreeNode** node) {
    if ((*node) == NULL)
        return 0;
    // возвращаем высоту узла
    return (*node)->height;
}

void set_height(BinaryTreeNode** node) {
    // высота узла равна высоте максимальной потомков + 1
    (*node)->height = 1 + max(height(&(*node)->left), height(&(*node)->right));
}

void singleRotateLeft(BinaryTreeNode** node) {
    /* помещает указатель node на node-right
     * ставя node на место node-right-left
     * c сохранением структуры дерева */
    // запоминаем правого потомка узла
    BinaryTreeNode* right = (*node)->right;
    // правый потомок узла теперь левый потомок левого ула
    (*node)->right = right->left;
    // обновляем высоту узла
    set_height(node);
    // левый узел левого узла указывает на исходный узел
    right->left = (*node);
    // указатель на исходный узел теперь указывает
    // на бывшего правого потомка
    (*node) = right;
    // обновляем высоту узла
    set_height(node);
}

void singleRotateRight(BinaryTreeNode** node) {
    /* помещает указатель node на node-left
     * ставя node на место node-left-right
     * c сохранением структуры дерева */
    // запоминаем левого потомка узла
    BinaryTreeNode* left = (*node)->left;
    // левый потомок узла теперь правый потомок левого ула
    (*node)->left = left->right;
    // обновляем высоту узла
    set_height(node);
    // правый узел левого узла указывает на исходный узел
    left->right = (*node);
    // указатель на исходный узел теперь указывает
    // на бывшего левого потомка
    (*node) = left;
    // обновляем высоту узла
    set_height(node);
}

void doubleRotateLeft(BinaryTreeNode** node) {
    singleRotateRight(&(*node)->right);
    singleRotateLeft(node);
}

void doubleRotateRight(BinaryTreeNode** node) {
    singleRotateLeft(&(*node)->left);
    singleRotateRight(node);
}

void rotateLeft(BinaryTreeNode** node) {
    BinaryTreeNode* right = (*node)->right;
    size_t left_height = height(&right->left);
    size_t right_height = height(&right->right);
    if (right_height > left_height)
        singleRotateLeft(node);
    else
        doubleRotateLeft(node);
}

void rotateRight(BinaryTreeNode** node) {
    BinaryTreeNode* left = (*node)->left;
    size_t left_height = height(&left->left);
    size_t right_height = height(&left->right);
    if (left_height > right_height)
        singleRotateRight(node);
    else
        doubleRotateRight(node);
}

void rebalance(BinaryTreeNode** node) {
    size_t left_height = height(&(*node)->left);
    size_t right_height = height(&(*node)->right);
    if (right_height > left_height + 1)
        rotateLeft(node);
    else if (left_height > right_height + 1)
        rotateRight(node);
    else
        set_height(node);
}

void insert(BinaryTreeNode** node, int el) {
    if ((*node) == NULL) {
        (*node) = (BinaryTreeNode *) calloc(1, sizeof(BinaryTreeNode));
        (*node)->value = el;
        (*node)->height = 0;
        (*node)->left = (*node)->right = NULL;
    }
    else if (el < (*node)->value) {
        insert(&(*node)->left, el);
        rebalance(node);
    } else if (el > (*node)->value) {
        insert(&(*node)->right, el);
        rebalance(node);
    }
}

int removeSmallest(BinaryTreeNode** node) {
    if ((*node)->left == NULL) {
        int result = (*node)->value;
        BinaryTreeNode* tmp = (*node);
        (*node) = (*node)->right;
        free(tmp);
        return result;
    }
    int result = removeSmallest(&(*node)->left);
    rebalance(node);
    return result;
}

int removeBiggest(BinaryTreeNode** node) {
    if ((*node)->right == NULL) {
        int result = (*node)->value;
        BinaryTreeNode* tmp = (*node);
        (*node) = (*node)->left;
        free(tmp);
        return result;
    }
    int result = removeBiggest(&(*node)->right);
    rebalance(node);
    return result;
}

void remove_el(BinaryTreeNode** node, int el) {
    assert((*node) != NULL);
    if (el < (*node)->value) {
        remove_el(&(*node)->left, el);
        rebalance(node);
    } if (el > (*node)->value) {
        remove_el(&(*node)->right, el);
        rebalance(node);
    } else if ((*node)->left == NULL) {
        BinaryTreeNode *tmp = (*node);
        (*node) = (*node)->right;
        free(tmp);
    } else if ((*node)->right == NULL) {
        BinaryTreeNode *tmp = (*node);
        (*node) = (*node)->left;
        free(tmp);
    } else {
        (*node)->value = removeSmallest(&(*node)->right);
        rebalance(node);
    }
}

typedef struct BinaryTree {
    BinaryTreeNode* root;
} BinaryTree;

void initBinaryTree(BinaryTree* tree) { tree->root = NULL; }

void form_tree(BinaryTree* tree, int* arr, size_t size) {
    for (size_t i = 0; i < size; i++)
        insert(&tree->root, arr[i]);
}

void sort_up_via_tree(int* arr, size_t size) {
    BinaryTree tree;
    initBinaryTree(&tree);
    for (size_t i = 0; i < size; i++)
        insert(&tree.root, arr[i]);
    for (size_t i = 0; i < size; i++)
        arr[i] = removeSmallest(&tree.root);
}

void sort_down_via_tree(int* arr, size_t size) {
    BinaryTree tree;
    initBinaryTree(&tree);
    for (size_t i = 0; i < size; i++)
        insert(&tree.root, arr[i]);
    for (size_t i = 0; i < size; i++)
        arr[i] = removeBiggest(&tree.root);
}

void test_BinaryTree() {
    IntArray arr;
    alloc_int_array(&arr, 0);

    for (int i = 0; i < 10; i++)
        if (i % 2 == 0)
            add_to_int_array(&arr, 10 - i);
        else
            add_to_int_array(&arr, 10 - i + 1);

    sort_down_via_tree(arr.array, arr.factual_size);
    for (size_t i = 0; i < arr.factual_size; i++)
        printf("%d\t", arr.array[i]);
}

#endif //TECHNOPARK_BALANCED_BINARY_SEARCH_TREE_H