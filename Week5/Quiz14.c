#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 8

typedef struct queue {
    int key
} element;

element queue[MAX_QUEUE_SIZE];
int front = 0;
int rear = 0;

void queueFull() {
    fprintf(stderr, "Stack is full\n");
    exit(EXIT_FAILURE);
}

element queueEmpty() {
    fprintf(stderr, "Stack is empty\n");
    element e;
    exit(EXIT_FAILURE);
    return e;
}

void addq(element item) {
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    if (front == rear) {
        queueFull();
    }
    queue[rear] = item;
}

element deleteq() {
    if (front == rear)
        return queueEmpty();
    front = (front + 1) % MAX_QUEUE_SIZE;
    return queue[front]; 
}  

void printq() {
    int curr = front;
    while (curr != rear) {
        curr = (curr + 1) % MAX_QUEUE_SIZE;
        printf("%d ", queue[curr].key);
    }
    printf("\n\n");
}

int main() {
    element curr_e;
    // initialize
    for (int i=0; i<MAX_QUEUE_SIZE; i++) {
        curr_e.key = -1;
        queue[i] = curr_e;
    }        

    // push 7 items
    for (int i=0; i<7; i++) {
        curr_e.key = rand() % 10;
        addq(curr_e);
        printf("Push %d into a queue.\n", curr_e.key);
        printq();
    }
    
    // pop 5 items
    for (int i=0; i<5; i++) {
        curr_e = deleteq();
        printf("Pop %d from a queue.\n", curr_e.key);
        printq();
    }

    // push 5 items again
    for (int i=0; i<5; i++) {
        curr_e.key = rand() % 10 + 1;
        addq(curr_e);
        printf("Push %d into a queue.\n", curr_e.key);
        printq();
    }
}