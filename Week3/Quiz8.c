#define MAX_TERMS 101
#define ARRAY_SIZE 6
#define N_OF_ELEMENTS 8
#include <stdio.h>

typedef struct term {
    int row;
    int col;
    int value;
} term;

void AddTerm(term*, int, int, int);
void PrintTerm(term*);
void Transpose(term*, term*);

int main() {
    // Original array
    term a[MAX_TERMS];
    a[0].row = ARRAY_SIZE;
    a[0].col = ARRAY_SIZE;
    a[0].value = N_OF_ELEMENTS;

    // Transposed array
    term t_a[MAX_TERMS];
    t_a[0].row = ARRAY_SIZE;
    t_a[0].col = ARRAY_SIZE;
    t_a[0].value = N_OF_ELEMENTS;

    // Init
    for (int i=1; i<=a[0].value; i++) {
        a[i].row = -1;
        a[i].col = -1;
        a[i].value = 0;
        t_a[i].row = -1;
        t_a[i].col = -1;
        t_a[i].value = 0;
    }

    AddTerm(a, 0, 0, 15);
    AddTerm(a, 0, 3, 22);
    AddTerm(a, 0, 5, -15);
    AddTerm(a, 1, 1, 11);
    AddTerm(a, 1, 2, 3);
    AddTerm(a, 2, 3, -6);
    AddTerm(a, 4, 0, 91);
    AddTerm(a, 5, 2, 28);

    printf("before transpose\n");
    PrintTerm(a);

    // Transpose
    Transpose(a, t_a);

    printf("\nafter transpose\n");
    PrintTerm(t_a);

    return 0;
}


// New term
void AddTerm(term *whole_term, int row, int col, int value) {
    int i = 1;
    // row가 -1인 항까지 이동
    while ((whole_term + i)->row != -1) {
        i++;
    }
    // 해당 항에 적용
    (whole_term + i)->row = row;
    (whole_term + i)->col = col;
    (whole_term + i)->value = value;
}

// Print
void PrintTerm(term *whole_term) {
    printf("index\trow\tcolumn\tvalue\n");
    for (int i=1; i<=N_OF_ELEMENTS; i++) {
        printf("a[%d]\t%d\t%d\t%d\n", i, whole_term[i].row, whole_term[i].col, whole_term[i].value);
    }
}

// Transpose
void Transpose(term *original, term *transpose) {
    // rowTerms & init
    int rowTerms[ARRAY_SIZE];
    int startingPos[ARRAY_SIZE];
    for (int i=0; i<ARRAY_SIZE; i++) {
        rowTerms[i] = 0;
        startingPos[i] = 0;
    }

    // A. rowTerms 개수 세기
    // for (int i=1; i<=N_OF_ELEMENTS; i++) {
    //     rowTerms[original[i].col]++;
    // }
    // startingPos[0] = 1;
    // for (int i=1; i<ARRAY_SIZE; i++) {
    //     startingPos[i] = startingPos[i-1] + rowTerms[i-1];
    // }

    // B. rowTerms 사용 하지 말고, startingPos에 계속 추가하기
    for (int i=1; i<=N_OF_ELEMENTS; i++) {
        startingPos[original[i].col]++;
    }
    int prev = startingPos[0];
    int tmp = startingPos[0];
    startingPos[0] = 1;
    for (int i=1; i<ARRAY_SIZE; i++) {
        tmp = startingPos[i];   // 현재 인덱스를 임시 저장하고
        startingPos[i] = startingPos[i-1] + prev;   // 이전 인덱스와 더한다
        prev = tmp; // 임시 저장한 변수를 prev로 옮긴다
    }

    int j;
    for (int i=1; i<=N_OF_ELEMENTS; i++) {
        j = startingPos[original[i].col];
        transpose[j].row = original[i].col;
        transpose[j].col = original[i].row;
        transpose[j].value = original[i].value;
        startingPos[original[i].col]++;
    }

}