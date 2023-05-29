#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// weight
// ===========================================================================

static const int prio_to_weight[40] = {
 /* -20 */     88761,     71755,     56483,     46273,     36291,
 /* -15 */     29154,     23254,     18705,     14949,     11916,
 /* -10 */      9548,      7620,      6100,      4904,      3906,
 /*  -5 */      3121,      2501,      1991,      1586,      1277,
 /*   0 */      1024,       820,       655,       526,       423,
 /*   5 */       335,       272,       215,       172,       137,
 /*  10 */       110,        87,        70,        56,        45,
 /*  15 */        36,        29,        23,        18,        15,
};

// linked list
// ===========================================================================

typedef struct LinkedNode {
    int load;       // Load weight
    int priority;   // priority
    float vruntime;   // virtual runtime  (ns)
    int runtime;    // real runtime (ns)
    struct LinkedNode *next;
} LinkedNode;



// RBTree
// ===========================================================================

typedef enum { RED, BLACK } color;

typedef struct Node {
    int load;       // Load weight
    int priority;   // priority
    float vruntime;   // virtual runtime  (ns)
    int runtime;    // real runtime (ns)
    color nodeColor;
    struct Node *left, *right, *parent;
} Node;

typedef struct RBTree {
    Node *root;
    Node *nil;
} RBTree;

Node* createNode(int prio, color nodeColor, Node *nil) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->load = prio_to_weight[prio];
    newNode->priority = prio;
    newNode->vruntime = 0;
    newNode->runtime = 0;
    newNode->nodeColor = nodeColor;
    newNode->left = newNode->right = newNode->parent = nil;
    return newNode;
}

RBTree* createRBTree() {
    RBTree *tree = (RBTree*)malloc(sizeof(RBTree));
    tree->nil = createNode(0, BLACK, NULL);
    tree->root = tree->nil;
    return tree;
}

void leftRotate(RBTree *tree, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != tree->nil)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == tree->nil)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rightRotate(RBTree *tree, Node *y) {
    Node *x = y->left;
    y->left = x->right;
    if (x->right != tree->nil)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == tree->nil)
        tree->root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void insertFixup(RBTree *tree, Node *z) {
    while (z->parent->nodeColor == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y->nodeColor == RED) {
                z->parent->nodeColor = BLACK;
                y->nodeColor = BLACK;
                z->parent->parent->nodeColor = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(tree, z);
                }
                z->parent->nodeColor = BLACK;
                z->parent->parent->nodeColor = RED;
                rightRotate(tree, z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y->nodeColor == RED) {
                z->parent->nodeColor = BLACK;
                y->nodeColor = BLACK;
                z->parent->parent->nodeColor = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->nodeColor = BLACK;
                z->parent->parent->nodeColor = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->nodeColor = BLACK;
}

void insertNode(RBTree *tree, Node *z) {
    Node *y = tree->nil;
    Node *x = tree->root;
    while (x != tree->nil) {
        y = x;
        if (z->vruntime < x->vruntime)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == tree->nil)
        tree->root = z;
    else if (z->vruntime < y->vruntime)
        y->left = z;
    else
        y->right = z;
    insertFixup(tree, z);
}

void insert(RBTree *tree, int prio) {
    Node *z = createNode(prio, RED, tree->nil);
    Node *y = tree->nil;
    Node *x = tree->root;
    while (x != tree->nil) {
        y = x;
        if (z->vruntime < x->vruntime)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == tree->nil)
        tree->root = z;
    else if (z->vruntime < y->vruntime)
        y->left = z;
    else
        y->right = z;
    insertFixup(tree, z);
}

Node* search(Node *x, int key) {
    if (x == NULL || x->load == key)
        return x;
    if (key < x->vruntime)
        return search(x->left, key);
    else
        return search(x->right, key);
}

void deleteFixup(RBTree *tree, Node *x) {
    while (x != tree->root && x->nodeColor == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->nodeColor == RED) {
                w->nodeColor = BLACK;
                x->parent->nodeColor = RED;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->nodeColor == BLACK && w->right->nodeColor == BLACK) {
                w->nodeColor = RED;
                x = x->parent;
            } else {
                if (w->right->nodeColor == BLACK) {
                    w->left->nodeColor = BLACK;
                    w->nodeColor = RED;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                w->nodeColor = x->parent->nodeColor;
                x->parent->nodeColor = BLACK;
                w->right->nodeColor = BLACK;
                leftRotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->nodeColor == RED) {
                w->nodeColor = BLACK;
                x->parent->nodeColor = RED;
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->nodeColor == BLACK && w->left->nodeColor == BLACK) {
                w->nodeColor = RED;
                x = x->parent;
            } else {
                if (w->left->nodeColor == BLACK) {
                    w->right->nodeColor = BLACK;
                    w->nodeColor = RED;
                    leftRotate(tree, w);
                    w = x->parent->left;
                }
                w->nodeColor = x->parent->nodeColor;
                x->parent->nodeColor = BLACK;
                w->left->nodeColor = BLACK;
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->nodeColor = BLACK;
}

void transplant(RBTree *tree, Node *u, Node *v) {
    if (u->parent == tree->nil)
        tree->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

void deleteNode(RBTree *tree, Node *z) {
    Node *y = z;
    Node *x;
    color yOriginalColor = y->nodeColor;
    if (z->left == tree->nil) {
        x = z->right;
        transplant(tree, z, z->right);
    } else if (z->right == tree->nil) {
        x = z->left;
        transplant(tree, z, z->left);
    } else {
        y = z->right;
        while (y->left != tree->nil)
            y = y->left;
        yOriginalColor = y->nodeColor;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->nodeColor = z->nodeColor;
    }
    if (yOriginalColor == BLACK)
        deleteFixup(tree, x);
    free(z);
}

void delete(RBTree *tree, int key) {
    Node *z = search(tree->root, key);
    if (z == NULL) {
        printf("Key %d not found in the tree.\n", key);
        return;
    }
    deleteNode(tree, z);
    printf("Key %d deleted from the tree.\n", key);
}

void deleteMin(RBTree *tree) {
    Node *z = tree->root;
    while (z->left != tree->nil) {
        z = z->left;
    }
    deleteNode(tree, z);
}

Node* findMin(RBTree *tree) {
    Node *z = tree->root;
    while (z->left != tree->nil) {
        z = z->left;
    }
    return z;
}

typedef struct QueueNode {
    Node* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

bool isEmpty(Queue* queue) {
    return (queue->front == NULL);
}

void enqueue(Queue* queue, Node* treeNode) {
    QueueNode* newQueueNode = (QueueNode*)malloc(sizeof(QueueNode));
    newQueueNode->treeNode = treeNode;
    newQueueNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = newQueueNode;
        queue->rear = newQueueNode;
    } else {
        queue->rear->next = newQueueNode;
        queue->rear = newQueueNode;
    }
}

Node* dequeue(Queue* queue) {
    if (isEmpty(queue))
        return NULL;

    QueueNode* frontNode = queue->front;
    Node* treeNode = frontNode->treeNode;

    queue->front = queue->front->next;
    if (queue->front == NULL)
        queue->rear = NULL;

    free(frontNode);
    return treeNode;
}

void levelOrderTraversal(Node* root, Node* nil) {
    if (root == nil)
        return;

    Queue* queue = createQueue();
    enqueue(queue, root);

    printf("Tree nodes in level order: \n");
    while (!isEmpty(queue)) {
        Node* current = dequeue(queue);
        printf("%.1f", current->vruntime);
        if (current->nodeColor == RED)
            printf("◯ ");
        else
            printf("◉ ");

        if (current->left != nil)
            enqueue(queue, current->left);
        if (current->right != nil)
            enqueue(queue, current->right);
    }

    printf("\n");
}

void printTree(RBTree* tree) {
    levelOrderTraversal(tree->root, tree->nil);
}

// Scheduling
// ===========================================================================

int checkDuplicate(int arr[], int num, int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (arr[i] == num) {
            return 1; // 중복이 발생하면 1을 반환
        }
    }
    return 0; // 중복이 발생하지 않으면 0을 반환
}

void createProcess(RBTree* tree) {
    int random_values[40];
    int i, j, random_value;
    srand(time(NULL));

    for (i = 0; i < 40; i++) {
        do {
            random_value = rand() % 40;
        } while (checkDuplicate(random_values, random_value, i)); // 중복 확인 후 다시 난수 생성

        // Add new node to tree
        insert(tree, random_value);
        random_values[i] = random_value;
        printf("%d ", random_value);
    }

    printf("\n");
}

int main() {
    struct timespec start_time, end_time;
    double execution_time;

    // RB Tree
    RBTree *tree = createRBTree();

    createProcess(tree);

    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (int i=0; i<50000; i++) {
        // Find min vruntime node 
        Node* min = findMin(tree);
        // Update runtime & vruntime
        min->runtime += 100;    // 100 ns
        min->vruntime += 100 * prio_to_weight[20] / prio_to_weight[min->priority];
        // Duplicate new Node
        Node* new_min = createNode(min->priority, RED, tree->nil);
        new_min->vruntime = min->vruntime;
        new_min->runtime = min->runtime;
        // Delete & re-locate the Node
        deleteMin(tree);
        insertNode(tree, new_min);
        // printTree(tree);
    }
    // 메모리 해제
    free(tree->nil);
    free(tree);

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    // 실행 시간 계산 (단위: 초)
    execution_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    printf("실행 시간: %.9f초\n", execution_time);

    return 0;
}