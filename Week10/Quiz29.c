#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;

typedef struct node {
    int data;
    treePointer leftChild, rightChild;
} node;

treePointer newNode(int _data) {
    treePointer new_node = malloc(sizeof(node));

    new_node->data = _data;
    new_node->leftChild = NULL;
    new_node->rightChild = NULL;

    return new_node;
}

int treeAdd(treePointer tree) {
    if (!tree) return 0;
    return treeAdd(tree->leftChild) + tree->data + treeAdd(tree->rightChild);
}

void PrintTree(treePointer n) {
    if (!n) return;
    PrintTree(n->leftChild);
    printf("%d ", n->data);
    PrintTree(n->rightChild);
}

void DeleteTree(treePointer n) {
    if (!n) return;
    DeleteTree(n->leftChild);
    DeleteTree(n->rightChild);
    free(n);
}

int main() {
    treePointer head = newNode(5);
    head->leftChild = newNode(2);
    head->rightChild = newNode(3);
    head->leftChild->leftChild = newNode(1);
    head->leftChild->rightChild = newNode(4);
    head->rightChild->leftChild = newNode(6);
    head->rightChild->rightChild = newNode(7);
    
    PrintTree(head);
    printf("\n");

    int total_sum = treeAdd(head);
    printf("Sum = %d\n", total_sum);

    DeleteTree(head);
    printf("Delete Success.\n");
    return 0;
}