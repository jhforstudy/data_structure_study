#include <stdio.h>
#include <stdlib.h>

typedef struct polyNode* polyPointer;
typedef struct polyNode {
    int coef;
    int expon;
    polyPointer link;
} polyNode;

void attach(int coefficient, int exponent, polyPointer* ptr) {
    polyPointer temp;
    temp = malloc(sizeof(*temp));
    temp->coef = coefficient;
    temp->expon = exponent;
    (*ptr)->link = temp;
    *ptr = temp;
}

// void erase(polyPointer *ptr) {
//     polyPointer temp;
//     while (*ptr) {
//         temp = *ptr;
//         *ptr = (*ptr)->link;
//         free(temp);
//     }
// }

void erase(polyPointer *ptr) {
    polyPointer temp;
    for (; *ptr; free(temp)) {
        printf("%dx^%d 삭제\n", (*ptr)->coef, (*ptr)->expon);
        temp = *ptr;
        *ptr=(*ptr)->link;
    }
}

void printpoly(polyPointer* ptr) {
    polyPointer temp = *ptr;
    while (temp) {
        printf("%dx^%d + ", temp->coef, temp->expon);
        temp = temp->link;
    }
    printf("\n");
}

int COMPARE(int a, int b) {
    if (a < b)
        return -1;
    else if (a == b)
        return 0;
    else
        return 1;
}

polyPointer padd(polyPointer a, polyPointer b) {
    polyPointer c, rear, temp;
    int sum;
    rear = malloc(sizeof(*rear));
    c = rear;   // dummy
    while (a && b) {
        switch (COMPARE(a->expon, b->expon)) {
            case -1:    // a->expon < b->expon
                attach(b->coef, b->expon, &rear);
                b = b->link;
                break;
            case 0:     // a->expon == b->expon
                sum = a->coef + b->coef;
                if (sum) attach(sum, a->expon, &rear);
                a = a->link;
                b = b->link;
                break;
            case 1:     // a->expon > b->expon
                attach(a->coef, a->expon, &rear);
                a = a->link;
        }
    }

    for (; a; a = a->link) attach(a->coef, a->expon, &rear);
    for (; b; b = b->link) attach(b->coef, b->expon, &rear);
    rear->link = NULL;

    temp = c;
    c = c->link;
    free(temp);

    return c;
}

int main() {
    polyPointer a = malloc(sizeof(*a));
    polyPointer b = malloc(sizeof(*b));

    a->coef = 1;
    a->expon = 1;
    a->link = NULL;
    b->coef = 2;
    b->expon = 2;
    b->link = NULL;

    printpoly(&a);
    printpoly(&b);

    polyPointer c = padd(a, b);

    erase(&c);

    return 0;
}