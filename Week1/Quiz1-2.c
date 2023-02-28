#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 3
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

void main(void) {
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);

    // ascending order
    if (x >= y) {
        if (y >= z) {
            printf("%d %d %d\n", z, y, x);
        }
        else {
            printf("%d ", y);
            if (x >= z) {
                printf("%d %d\n", z, x);
            }
            else {
                printf("%d %d\n", x, z);
            }
        }
    }
    else {
        if (y < z) {
            printf("%d %d %d\n", x, y, z);
        }
        else {
            if (x < z) {
                printf("%d %d ", x, z);
            }
            else {
                printf("%d %d ", z, x);
            }
            printf("%d\n", y);
        }
    }
}