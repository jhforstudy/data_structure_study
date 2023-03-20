#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* failure;

void fail(char* string, char* pat) {
    int i;
    int n = strlen(pat);
    failure[0] = -1;
    // j = 1 ~ n-1 반복
    for (int j=1; j<n; j++) {
        // 시작은 failure[j-1]
        i = failure[j-1];
        while (pat[j] != pat[i+1] && i>=0)
            i = failure[i];
        // 이동 완료 후, 다음 인덱스와 마지막 인덱스 확인
        if (pat[j] == pat[i+1]) failure[j] = i+1;
        else failure[j] = -1;
    }
}

int pmatch(char* string, char* pat) {
    int i=0;
    int j=0;
    int lens = strlen(string);
    int lenp = strlen(pat);

    // // while loop
    // while (i < lens && j < lenp) {
    //     if (string[i] == pat[j]) {
    //         i++;
    //         j++;
    //     }
    //     else if (j == 0) i++;
    //     else j = failure[j-1]+1;
    // }

    // for loop
    for (i=0; i<lens && j<lenp; i++) {
        if (string[i] == pat[j]) j++;
        else if (j==0) continue;
        else {
            i--;
            j = failure[j-1]+1;
        }
    }

    return (j == lenp ? i-lenp : -1);
}


int main() {
    char* string = "hello world!";
    char* pat = "wor";

    // get a failure function
    failure = (int*)malloc(sizeof(int) * strlen(pat));
    fail(string, pat);

    // Print failure function
    for (int i=0; i<strlen(pat); i++)
        printf("%d ", failure[i]);
    printf("\n");

    // pmatch
    int idx = pmatch(string, pat);
    printf("Index : %d\n", idx);

    // free memory
    free(failure);

    return 0;
}