#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_QUEUE 10

typedef struct {
    int key;
} element;

typedef struct queue* queuePointer;
typedef struct queue {
    element data;
    queuePointer link;
} queue;
queuePointer front[MAX_QUEUE];
queuePointer rear[MAX_QUEUE];

element queueEmpty() {
    fprintf(stderr, "Queue is empty\n");
    element e;
    exit(EXIT_FAILURE);
    return e;
}

// void addq(int i, element item) {
//     queuePointer temp;
//     temp = malloc(sizeof((*temp)));
//     temp->data = item;
//     temp->link = front[i];
//     if (front[i]) rear[i]->link = temp;
//     else front[i] = temp;
//     rear[i] = temp;
// }

void addq(int i, element item) {
    queuePointer temp;
    temp = malloc(sizeof((*temp)));
    temp->data = item;

    // queue의 맨 마지막으로 접근
    queuePointer t = front[i];
    // front에 무언가 존재하면
    if (t) {
        while (t->link) {
            t = t->link;
        }
        t->link = temp;
    }
    // 아무것도 없으면
    else {
        front[i] = temp;
    }
}

element deleteq(int i) {
    queuePointer temp = front[i];
    element item;
    if (!temp)  return queueEmpty();
    item = temp->data;
    front[i] = temp->link;
    free(temp);
    return item;
}

void printq() {
    queuePointer temp;
    for (int i=0; i<MAX_QUEUE; i++) {
        temp = front[i];
        printf("%d : ", i);
        while (temp) {
            printf("%d -> ", temp->data.key);
            temp = temp->link;
        }
        printf("\n");
    }
}

int main() {
    for (int i=0; i<10; i++) {
        element item;
        item.key = i * 10;
        addq(0, item);
    }
    printq();
    return 0;
}