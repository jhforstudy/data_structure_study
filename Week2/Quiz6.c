#define MAX_DEGREE 101
#include <stdio.h>
#include <stdbool.h>
typedef struct polynomial {
    int degree;
    float coef[MAX_DEGREE];
} polynomial;

// 함수 definition
polynomial Zero();
bool IsZero(polynomial);
void PrintPoly(polynomial);
float Coef(polynomial, int);
int LeadExp(polynomial);
polynomial Remove(polynomial, int);
polynomial Attach(polynomial, float, int);

// 메인 함수
int main() {
    // A(x) = 3x^6 + 2x^5 + 4
    // B(x) = x^4 + 10x^3 + 3x^2 + 1
    polynomial A = Zero();
    polynomial B = Zero();

    // Attach
    A = Attach(A, 3, 6);
    A = Attach(A, 2, 5);
    A = Attach(A, 41, 0);

    B = Attach(B, 1, 4);
    B = Attach(B, 10, 3);
    B = Attach(B, 3, 2);
    B = Attach(B, 1, 0);

    // print
    printf("A(x) = ");
    PrintPoly(A);
    printf("B(x) = ");
    PrintPoly(B);

    // Remove
    A = Remove(A, 6);
    B = Remove(B, 4);

    // print
    printf("\nA(x) = ");
    PrintPoly(A);
    printf("B(x) = ");
    PrintPoly(B);

}

polynomial Zero() {
    polynomial temp;
    temp.degree = 0;
    for (int i=0; i<MAX_DEGREE; i++) {
        temp.coef[i] = 0;
    }
    return temp;
}

bool IsZero(polynomial poly) {
    for (int i=0; i<=poly.degree; i++) {
        if (poly.coef[i] != 0) {
            return false;
        }
    }
    return true;
}

void PrintPoly(polynomial poly) {
    for (int i=MAX_DEGREE-1; i>=0; i--) {
        if (poly.coef[i] == 0) {
            continue;
        }
        else{
            if (i == 0) {
                printf("%.2f\n", poly.coef[i]);
            }
            else {
                printf("%.2f x^%d + ", poly.coef[i], i);
            }
        }
    }
}

float Coef(polynomial poly, int inp_degree) {
    return poly.coef[inp_degree];
}

int LeadExp(polynomial poly) {
    for (int i=MAX_DEGREE-1; i>=0; i--) {
        if (poly.coef[i] != 0) {
            return i;
        }
    }
}

polynomial Remove(polynomial poly, int inp_degree) {
    poly.coef[inp_degree] = 0;
    if (inp_degree == poly.degree) {
        for (int i=inp_degree; i>=0; i--) {
            if (poly.coef[i] != 0) {
                poly.degree = i;
                break;
            }
        }
    }
    return poly;
}

polynomial Attach(polynomial poly, float inp_coef, int inp_degree) {
    poly.coef[inp_degree] += inp_coef;
    if (inp_degree >= poly.degree) {
        poly.degree = inp_degree;
    }
    return poly;
}