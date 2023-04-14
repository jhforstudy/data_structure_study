#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode {
    int data;
    listPointer link;
} listNode;

listPointer create2() {
    listPointer first, second;

    first = malloc(sizeof(*first));
    second = malloc(sizeof(*second));
    
    second->data = 20;
    second->link = NULL;

    first->data = 10;
    first->link = second;

    return first;
}

void insert50(listPointer* first, listPointer x) {
    listPointer temp;
    temp = malloc(sizeof(*temp));
    temp->data = 50;
    if (*first) {
        temp->link = x->link;
        x->link = temp;
    }
    else {
        temp->link = NULL;
        *first = temp;
    }
}

// void delete(listPointer* first, listPointer trail, listPointer x) {
//     if (trail) 
//         trail->link = x->link;
//     else
//         *first = (*first)->link;
//     free(x);
// }

void delete(listPointer* first, listPointer x) {
    // x가 맨 처음에 존재하면
    if ((*first) == x) {
        *first = (*first)->link;
        printf("%d 삭제 완료\n", x->data);
        free(x);
        return;
    }
    
    // 아니면, linked list 탐색
    listPointer temp = *first;
    while (temp != NULL) {
        // 다음 노드가 x이면
        if (temp->link == x) {
            // x의 다음을 temp의 다음으로 연결 
            temp->link = x->link;
            printf("%d 삭제 완료\n", x->data);
            free(x);
            return;
        }
        // 다음 노드로 이동
        temp = temp->link;
    }
    printf("존재하지 않음\n");
}

void print_list(listPointer* first) {
    listPointer temp = *first;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->link;
    }
    printf("\n");
}

int main() {
    listPointer start = create2();
    insert50(&start, start->link);
    print_list(&start);
    delete(&start, start->link->link);
    print_list(&start);

    return 0;
}