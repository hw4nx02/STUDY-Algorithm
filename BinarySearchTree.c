#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10

struct node {
    int key;
    struct node* l;
    struct node* r; 
};

struct Queue {
    struct node* queue[SIZE];
    int front, rear;
};

void queueInit(struct Queue* queue) {
    queue->front = queue->rear = -1;
}
void enqueue(struct Queue* q, struct node* input) {
    if (q->rear == SIZE - 1) {
        printf("Overflow");
        return;
    }

    if (input != NULL) {
        q->queue[++q->rear] = input;
    }
}
struct node* dequeue(struct Queue* q) {
    if (q->front == q->rear) {
        printf("Queue is empty");
        return NULL;
    }

    return q->queue[++q->front];
}

/**
 * 이진 탐색 트리 초기화
 */
struct node* treeInit() {
    struct node* head;

    head = (struct node*)malloc(sizeof(*head));
    head -> l = NULL;
    head -> r = NULL;
    head -> key = 0;

    return head;
}

/**
 * 이진 탐색 트리 탐색
 * head - 이진 탐색 트리 헤드 노드의 포인터
 * xkey - 탐색할 키
 * 
 * 출력 - 탐색할 키를 갖는 노드의 포인터
 */
struct node* treeSearch(struct node* head, int xkey) {
    struct node* current;
    current = head -> r;
    while(current != NULL) {
        printf(" -> %d", current->key);
        
        if (xkey == current->key) return current;
        if (xkey < current->key) current = current->l;
        if (xkey > current->key) current = current->r;
    }

    return NULL;
}

/**
 * 이진 탐색 트리 삽입
 */
void treeInsert(struct node* head, int xkey) {
    struct node *parent, *current;
    parent = head;
    current = parent->r;
    while(current != NULL) {
        parent = current;
        if (xkey == current->key) return;
        else if (xkey < current->key) current = current->l;
        else current = current->r;
    }

    current = (struct node*) malloc(sizeof(*current));
    current->key = xkey;
    current->l = NULL;
    current->r = NULL;

    if (xkey < parent->key) parent->l = current;
    else parent->r = current;
}

/**
 * 이진 탐색 트리 삭제
 */
// void treeDelete(struct node* head, int xkey) {
//     // parent: 삭제할 노드의 부모 노드

//     struct node *parent, *c, *target, *x;
//     parent = head;
//     x = head->r;
//     x = treeSearch(x, xkey); // 삭제할 키 탐색
//     if (x == NULL) return;
//     else target = x;
//     if (target->r == NULL) x = target->l; // 오른쪽 자식 없는 경우
//     // 오른쪽 자식 있는데
//     else if (target->r->l == NULL) { // 오른쪽 자식의 왼쪽 자식 없는 경우
//         x = target->r;
//         x->l = target->l;
//     }
//     else { // 오른쪽 자식의 왼쪽 자식 있는 경우
//         c = x->r;
//         while(c->l->l != NULL) c = c->l;
//         x = c->l;
//         c->l = x->r;
//         x->l = target->l;
//         x->r = target->r;
//     }

//     free(target);
//     if (xkey < parent->key) parent->l = x;
//     else parent->r = x;
// }
void treeDelete(struct node* head, int xkey) {
    struct node *parent = head, *target = head->r;

    // 1. target 찾기 + parent 추적
    while (target != NULL && target->key != xkey) {
        parent = target;
        if (xkey < target->key) target = target->l;
        else target = target->r;
    }

    if (target == NULL) return; // 존재하지 않음

    struct node *replacement;

    // 2. case 1: 오른쪽 자식 없음
    if (target->r == NULL) {
        replacement = target->l;
    }
    // 3. case 2: 오른쪽 자식 있고, 그 자식에 왼쪽 자식 없음
    else if (target->r->l == NULL) {
        replacement = target->r;
        replacement->l = target->l;
    }
    // 4. case 3: 오른쪽 서브트리에 왼쪽 자식 있음 (중위후계자 찾기)
    else {
        struct node *succParent = target->r;
        struct node *succ = succParent->l;

        while (succ->l != NULL) {
            succParent = succ;
            succ = succ->l;
        }

        succParent->l = succ->r;
        succ->l = target->l;
        succ->r = target->r;
        replacement = succ;
    }

    // 5. parent 갱신
    if (xkey < parent->key) parent->l = replacement;
    else parent->r = replacement;

    free(target);
}

void printTree(struct node* head) {
    struct Queue* q;
    q = (struct Queue*)malloc(sizeof(*q));
    queueInit(q);    

    int currentLevelNodes = 1;
    int nextLevelNodes = 0;
    enqueue(q, head->r);
    printf("\n");
    while (q->front != q->rear) {
        struct node* current = dequeue(q);
        currentLevelNodes--;

        if (current != NULL) {
            printf("%d ", current->key);

            enqueue(q, current->l);
            enqueue(q, current->r);
            nextLevelNodes += 2;
        }

        if (currentLevelNodes == 0) {
            printf("\n");
            currentLevelNodes = nextLevelNodes;
            nextLevelNodes = 0;
        }
    }
}

int main() {
    struct node* head = treeInit();

    srand(time(0));
    printf("임의로 생성된 %d개의 숫자들: ", SIZE);
    for (int i = 0; i < SIZE; i++) {
        int num =  rand() % 10 + 1;
        treeInsert(head, num);
        printf("%d ", num);
    }

    printTree(head);

    int key;
    printf("\n탐색할 키를 입력: ");
    scanf("%d", &key);
    treeSearch(head, key);

    printf("\n삭제할 키를 입력: ");
    scanf("%d", &key);
    treeDelete(head, key);
    printTree(head);
}