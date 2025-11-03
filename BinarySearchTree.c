#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
#define qSIZE 10000

// --------------------- 구조체 정의 ----------------------------
struct node {
	int key;
	struct node* l;
	struct node* r;
};
struct node* treeInit() {
	struct node* head = (struct node*)malloc(sizeof(*head));

	if (head == NULL) return NULL;
	head->key = 0;
	head->l = NULL;
	head->r = NULL;

	return head;
}

struct Queue {
	struct node* queue[qSIZE];
	int front, rear;
};
void queueInit(struct Queue* q) {
	q->front = q->rear = -1;
}

// --------------------------------- 이진 탐색 트리 -------------------------------------
struct node* treeSearch(struct node* head, int key) {
	struct node* target = head->r;

	while (target != NULL) {
		if (target->key == key) return target;
		else if (target->key > key) target = target->l;
		else target = target->r;
	}

	return NULL;
}
void treeInsert(struct node* head, int key) {
	struct node* parent = head;
	struct node* newNode = parent->r;

	while (newNode != NULL) {
		parent = newNode;
		if (newNode->key == key) return;
		else if (newNode->key > key) newNode = newNode->l;
		else newNode = newNode->r;
	}

	newNode = (struct node*)malloc(sizeof(*newNode));
	if (newNode == NULL) return;
	newNode->key = key;
	newNode->l = NULL;
	newNode->r = NULL;

	if (parent->key < key) parent->r = newNode;
	else parent->l = newNode;
}

void treeDelete(struct node* head, int key) {
	// 1. parent: 삭제할 노드의 부모 노드
    // 2. target: 삭제할 노드
    // 3. replace: 삭제 노드와 교체할 노드
    // 4. rc: 삭제할 노드의 우측 노드
    struct node *parent, *target, *replace, *rc;

	parent = head; // 부모 노드 초기화
	target = head->r; // 찾는 노드를 초기화
    // 교수님 PDF는 target이 아니라 replace 기준.
    // replace를 사용하여 삭제할 노드를 찾는 이유가 있는지?

    /** 삭제할 노드와 그 부모 노드 탐색 */
	while (target != NULL && target->key != key) { 
        // NULL이 아니고 찾는 키가 아니면 계속 파고 들어가며 탐색
        parent = target;
        if (key < target->key) target = target->l;
        else target = target->r;
    }

	if (target == NULL) return; // 찾는 키가 없으면 NULL 반환
    // else target = replace; // 찾는 키가 있다면, target 노드도 삭제할 노드를 가리키게 함

	if (target->r == NULL) { // 1. 삭제 노드의 우측 노드가 비었으면
		replace = target->l; // 교체 노드는 삭제 노드의 좌측 노드
	}
    // 2. 삭제 노드의 우측 노드는 있지만,
	else if (target->r->l == NULL) { // 그 우측 노드의 좌측 자식 노드는 비었을 때
			replace = target->r; // 삭제 노드의 우측 노드를 교체 노드로 하고
			replace->l = target->l; // 교체 노드가 삭제 노드의 자식을 물려 받게함
    }
    // 3. 삭제 노드의 우측 노드고 있고,
    else { // 그 우측 노드의 좌측 노드도 있으면
			rc = target->r; // rc는 삭제 노드의 우측 노드

            // rc->l이 삭제 노드 우측 트리에서 최솟값을 가리킬 때까지 이동 
			while (rc->l->l != NULL) rc = rc->l;
			
			replace = rc->l; // 교체 노드는 최솟값 노드
            rc->l = replace->r; // 최솟값 노드의 부모는 최솟값 노드의 우측 노드를 물려받음
            replace->l = target->l; //교체 노드는 삭제 노드의 자식을 모두 물려받음
            replace->r = target->r;
		}

    // 삭제 노드가 원래 있던 위치(l or r)를 찾아 교체 노드 연결
	if (parent->key > key) parent->l = replace;
	else parent->r = replace;

    free(target);
}

// ------------------------------------------- 큐 ----------------------------------------------
void enqueue(struct Queue* q, struct node* input) {
	if (q->rear == qSIZE-1) {
		printf("queue is full");
		return;
	}

	q->queue[++q->rear] = input;
	return;
}
struct node* dequeue(struct Queue* q) {
	if (q->front == q->rear) {
		printf("queue is empty");
		return NULL;
	}

	return q->queue[++q->front];
}

/**
 * 트리 출력
 */
void treePrint(struct node* head) {
    // 헤드가 NULL이거나 루트 노드가 NULL이면 빈 나무
    if (head == NULL || head->r == NULL) {
        printf("(empty tree)\n");
        return;
    }

    // 큐 초기화
    struct Queue* q = (struct Queue*)malloc(sizeof(*q));
    queueInit(q);
    enqueue(q, head->r);

    int level = 0; // 이진 탐색 트리 레벨
    int maxDepth = 6; // 트리가 너무 깊어지면 무한 출력 방지
    int nodesInCurrentLevel = 1; // 현재 레벨의 노드 개수
    int nodesInNextLevel = 0; // 다음 레벨의 노드 개수

    while ((q->front!=q->rear) && level < maxDepth) {
        // 큐가 비어 있지 않고, 최대 출력 높이보다 레벨이 작다면 계속 반복
        int spacing = (1 << (maxDepth - level)); // 간격: 2^(depth-level)
        // 2^6개 * 2^0 -> 2^5개 * 2^1 -> 2^4개 * 2^2 ...
        // 산술적으로 6제곱을 계속해서 만듦.

        while (nodesInCurrentLevel--) { // 현재 레밸 노드 개수 줄여가며 dequeue
            struct node* node = dequeue(q);

            // 앞쪽 간격
            for (int i = 0; i < spacing; i++) printf(" ");

            if (node == NULL) {
                printf("."); // NULL 노드 대신 점 출력
                enqueue(q, NULL);
                enqueue(q, NULL);
            } else {
                printf("%d", node->key);
                enqueue(q, node->l);
                enqueue(q, node->r);
            }
            nodesInNextLevel += 2;

            // 노드 간 간격
            for (int i = 0; i < spacing; i++) printf(" ");
        }

        // 한 레벨 모두 출력하면 -> nodesInCurrentLevel == 0
        printf("\n"); // 줄 바꾸고
        nodesInCurrentLevel = nodesInNextLevel; // 다음 레벨 노드 개수 받고
        nodesInNextLevel = 0; 
        level++;// 레벨 하나 올리기
    }

    printf("\n");
}


int main() {
	struct node* head = treeInit();
	int a[SIZE] = { 33, 19, 15, 17, 29, 23, 21, 25, 27, 22 }; 

	for (int i = 0; i < SIZE; i++) {
		treeInsert(head, a[i]);
	}
    printf("\n처음 트리\n");
	treePrint(head);

	printf("\n----------------------\n");
    printf("23 좌우의 값\n");
	printf("\n%d", treeSearch(head, 23)->l->key);
	printf("\n%d", treeSearch(head, 23)->r->key);

	printf("\n----------------------\n");
	treeDelete(head, 19);
    printf("\n19 삭제 후의 트리\n");
	treePrint(head);

	printf("\n----------------------\n");
    printf("19 삭제 후의 23 좌우의 값\n");
	printf("\n%d", treeSearch(head, 23)->l->key);
	printf("\n%d", treeSearch(head, 23)->r->key);

	printf("\n------------------\n");
    printf("최악 경우 트리\n");
    head = treeInit();
	for (int i = 0; i < SIZE; i++) {
		treeInsert(head, i);
	}
	treePrint(head);
}