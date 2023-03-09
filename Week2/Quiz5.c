#include <stdio.h>

// 직사각형 : 4개의 x, y 좌표
typedef struct rectangle {
    int first_x;
    int first_y;
    int second_x;
    int second_y;
    int third_x;
    int third_y;
    int fourth_x;
    int fourth_y;
} rectangle;

// 삼각형 : 3개의 x, y 좌표
typedef struct triangle {
    int first_x;
    int first_y;
    int second_x;
    int second_y;
    int third_x;
    int third_y;
} triangle;

// 원 : 중심 x, y 좌표 + 반지름
typedef struct circle {
    int x;
    int y;
    float radius;
} circle;

int main() {
    rectangle r1;
    triangle t1;
    circle c1;

    // 직사각형
    r1.first_x = 1;
    r1.first_y = 1;
    r1.second_x = 2;
    r1.second_y = 2;
    r1.third_x = 3;
    r1.third_y = 3;
    r1.fourth_x = 4;
    r1.fourth_y = 4;

    // 삼각형
    t1.first_x = 1;
    t1.first_x = 1;
    t1.second_x = 2;
    t1.second_y = 5;
    t1.third_x = 3;
    t1.third_y = 7;

    // 원
    c1.x = 3;
    c1.y = 3;
    c1.radius = 5.2;

    return 0;
}