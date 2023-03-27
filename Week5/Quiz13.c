#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef struct stack {
    int key
} element;

element stack[MAX_STACK_SIZE];
int top = -1;

void stackFull() {
    fprintf(stderr, "Stack is full\n");
    exit(EXIT_FAILURE);
}

element stackEmpty() {
    fprintf(stderr, "Stack is empty\n");
    element e;
    exit(EXIT_FAILURE);
    return e;
}

void push(element item) {
    if (top >= MAX_STACK_SIZE-1) {
        stackFull();
        return;
    }
    stack[++top] = item;
}

element pop() {
    if (top == -1) {
        return stackEmpty();
    }
    return stack[top--];
}

int main() {
    element curr_e;
    int reversed[10];

    for (int i=0; i<10; i++) {
        curr_e.key = rand() % 1000;
        push(curr_e);
        printf("Push %d into a stack.\n", curr_e.key);
    }

    // Pop & put into reversed array
    for (int i=0; i<10; i++) {
        curr_e = pop();
        reversed[9-i] = curr_e.key;    // reversed way
    }
    
    // Print
    printf("FIFO -> ");
    for (int i=0; i<9; i++)
        printf("%d, ", reversed[i]);
    printf("%d\n", reversed[9]);
}