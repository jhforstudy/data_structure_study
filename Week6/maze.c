#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STACK_SIZE 100
#define MAX_ROWS 7 
#define MAX_COLS 7
#define EXIT_ROW 5
#define EXIT_COL 5

// Struct for stack
typedef struct element {
    int row;
    int col;
    int dir;
} element;

// Global variable (stack)
element stack[MAX_STACK_SIZE];
int top;

// Functions for stack
// ==================================================================
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
// ==================================================================

// Struct for path
typedef struct offset {
    short int vert;     // -1, 0, +1
    short int horiz;    // -1, 0, +1
} offset;

//  Name |   Dir |   .vert   |   .horiz
//  N    |   0   |   -1      |    0
//  NE   |   1   |   -1      |   +1
//  E    |   2   |    0      |   +1
//  SE   |   3   |   +1      |   +1
//  S    |   4   |   +1      |    0
//  SW   |   5   |   +1      |   -1
//  W    |   6   |    0      |   -1
//  NW   |   7   |   -1      |   -1

// Global variable (maze & path)
offset move[8];
int maze[MAX_ROWS][MAX_COLS], mark[MAX_ROWS][MAX_COLS];

// Functions for path
// ==================================================================
void path(int maze[MAX_ROWS][MAX_COLS], int mark[MAX_ROWS][MAX_COLS], offset move[8]) {
    int i, row, col, nextRow, nextCol, dir;
    bool found = false;
    element position;

    mark[1][1] = 1; top = 0;
    stack[0].row = 1; stack[0].col = 1; stack[0].dir = 0;

    // stack이 비거나, found = true 되기 전까지
    while (top > -1 && !found) {
        // stack 최상단의 row, col, dir 사용
        position = pop();
        row = position.row;
        col = position.col;
        dir = position.dir;

        // 8가지 방향에 대해
        while (dir < 8 && !found) {
            // 다음 위치 확인
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            // 목적지를 찾았으면, 끝내기
            if (nextRow == EXIT_ROW && nextCol == EXIT_COL)
                found = true;
            else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
                mark[nextRow][nextCol] = 1;
                position.row = row;
                position.col = col;
                position.dir = ++dir;
                push(position);
                row = nextRow;  col = nextCol;  dir = 0;
            }
            else
                ++dir;
        }
    }

    // After path finding
    if (found) {
        printf("The path is:\n");
        printf("row   col\n");
        for (i=0; i<=top; i++)
            printf("%2d%5d\n", stack[i].row, stack[i].col);
        printf("%2d%5d\n", row, col);
        printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
    }
    else
        printf("The maze does not have a path\n");
}
// ==================================================================

int main() {
    int maze[MAX_ROWS][MAX_COLS] = {
        {1,1,1,1,1,1,1},
        {1,0,0,1,1,0,1},
        {1,1,1,0,0,1,1},
        {1,1,1,0,1,1,1},
        {1,1,0,1,0,1,1},
        {1,0,1,1,0,0,1},
        {1,1,1,1,1,1,1}
    };
    int mark[MAX_ROWS][MAX_COLS] = {
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0}
    };
    offset N;
    N.vert = -1;
    N.horiz = 0;
    offset NE;
    NE.vert = -1;
    NE.horiz = 1;
    offset E;
    E.vert = 0;
    E.horiz = 1;
    offset SE;
    SE.vert = 1;
    SE.horiz = 1;
    offset S;
    S.vert = 1;
    S.horiz = 0;
    offset SW;
    SW.vert = 1;
    SW.horiz = -1;
    offset W;
    W.vert = 0; 
    W.horiz = -1;
    offset NW;
    NW.vert = 1;
    NW.horiz = -1;

    offset move[8] = {N, NE, E, SE, S, SW, W, NW};

    top = -1;
    path(maze, mark, move);

    return 0;
}