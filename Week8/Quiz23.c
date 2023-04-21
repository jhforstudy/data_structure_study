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

listPointer invert(listPointer lead) {
    listPointer middle, trail;
    middle = NULL;
    while (lead) {
        trail = middle;
        middle = lead;
        lead = lead->link;
        middle->link = trail;
    }
    return middle;
}

void print_list(listPointer* first) {
    listPointer temp = *first;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->link;
    }
    printf("\n");
}

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

listPointer invertedCopyList(listPointer ptr) {
    // 1. 새로운 리스트 생성
    listPointer copy;
    listPointer lead = copy;
    // 2. copy함
    while (ptr != NULL) {
        copy = malloc(sizeof(*copy));
        copy->data = ptr->data;
        copy->link = NULL;
        copy = copy->link;
        ptr = ptr->link;
    }
    // 3. 뒤집음
    listPointer middle, trail;
    middle = NULL;
    while (lead) {
        trail = middle;
        middle = lead;
        lead = lead->link;
        middle->link = trail;
    }
    // 4. 결과 반환
    return middle;
}

int main() {
    listPointer start = create2();
    insert50(&start, start->link);
    print_list(&start);
    listPointer inverted = invertedCopyList(start);
    print_list(&inverted);
}