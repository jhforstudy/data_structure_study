#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows, cols;
    scanf("%d %d", &rows, &cols);

    // 2차원 동적할당
    int** whole = (int**)malloc(rows * sizeof(int*));
    for (int i=0; i<rows; i++) {
        whole[i] = (int*)malloc(cols * sizeof(int));
    }

    // 메모리 반납
    for (int i=0; i<rows; i++) {
        free(whole[i]);
    }
    free(whole);

    return 0;
}