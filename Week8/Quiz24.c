#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 12

typedef struct node *nodePointer;
typedef struct node {
    int data;
    nodePointer link;
} node;

int main() {
    short int out[MAX_SIZE];
    nodePointer seq[MAX_SIZE];
    nodePointer x, y, top;
    int i, j, n;

    printf("Enter the size (<= %d) ", MAX_SIZE);
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        out[i] = 1; seq[i] = NULL;
    }
    printf("Enter a pair of numbers (-1 -1 to quit): ");
    scanf("%d %d", &i, &j);

    while (i >= 0) {
        x = malloc(sizeof(*x));
        x->data = j;    x->link = seq[i];   seq[i] = x;
        x = malloc(sizeof(*x));
        x->data = i;    x->link = seq[j];   seq[j] = x;
        printf("Enter a pair of numbers (-1 -1 to quit): ");
        scanf("%d %d", &i, &j);
    }

    for (i=0; i<n; i++) {
        if (out[i]) {
            printf("\nNew class: %5d", i);
            out[i] = 0; x = seq[i]; top = NULL;
            for (;;) {
                while (x) {
                    j = x->data;
                    if (out[j]) {
                        printf("%5d", j);   out[j] = 0;
                        y = x->link;    x->link = top;  top = x;    x = y;
                    }   else x = x->link;
                }
                if (!top) break;
                x = seq[top->data];
                top = top->link;
            }
        }
    }
    printf("\n");

    return 0;
}