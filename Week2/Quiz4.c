#include <stdio.h>
#include <stdlib.h>
int** make2Darray(int*, int);

int main() {
    int length[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    int** myArray;
    int size = sizeof(length)/sizeof(int);

    myArray = make2Darray(length, size);

    for (int i=0; i<sizeof(length)/sizeof(int); i++)
        free(myArray[i]);
    free(myArray);
    printf("\n메모리 반납 완료\n");
    
    return 0;
}

int** make2Darray(int* list, int len) {
    // double ptr 선언
    int** tempArray = (int**)malloc(len * sizeof(int*));

    // 각 row마다 length[i]만큼의 메모리 동적할당
    for (int i=0; i<len; i++) {
        tempArray[i] = (int*)malloc(list[i] * sizeof(int));
        printf("%d번째 row : 크기 %d의 배열 생성\n", i+1, list[i]);
    }

    return tempArray;
}