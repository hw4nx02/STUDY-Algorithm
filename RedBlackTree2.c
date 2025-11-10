#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
#define MAX_HEIGHT 10
#define MAX_WIDTH 120

struct Node {
    int key;
    char color;
    struct Node* l;
    struct Node* r;
    struct Node* p;
};

struct rbTree {
    struct Node* tRoot;
    struct Node* tNil;
};

/**
 * Red Black Tree 초기화
 */
struct rbTree* initTree() {
    struct rbTree* tree = (struct rbTree*)malloc(sizeof(*tree));

    struct Node* nil = (struct Node*)malloc(sizeof(*nil));
    nil->color = 'b';

    nil->l = nil->r = nil->p = nil;
    tree->tNil = tree->tRoot = nil;

    return tree;
}

/**
 * 좌로 회전
 */
void leftRotate(struct rbTree* tree, struct Node* x) {
    struct Node* y = x->r;
    x->r = y->l;
    if (y->l != tree->tNil) {
        y->l->p = x;
    }
    y->p = x->p;

    if (x->p == tree->tNil) {
        tree->tRoot = y;
    }
    else if (x == x->p->l) {
        x->p->l = y;
    }
    else {
        x->p->r = y;
    }
    y->l = x;
    x->p = y;
}

/**
 * 우측으로 회전
 */
void rightRotate(struct rbTree* tree, struct Node* x) {
    struct Node* y = x->l;
    x->l = y->r;
    if (y->r != tree->tNil) {
        y->r->p = x;
    }
    y->p = x->p;
    if (x->p == tree->tNil) {
        tree->tRoot = y;
    }
    else if (x == x->p->r) {
        x->p->r = y;
    }
    else {
        x->p->l = y;
    }

    y->r = x;
    x->p = y;
}

/**
 * 수정
 */
void fixUp(struct rbTree* tree, struct Node* z) {
    struct Node* y;
    while (z->p->color == 'r') {
        if (z->p == z->p->p->l) {
            y = z->p->p->r;
            if (y->color == 'r') {
                z->p->color = 'b';
                y->color = 'b';
                z->p->p->color = 'r';
                z = z->p->p;
            }
            else {
                if (z == z->p->r) {
                    z = z->p;
                    leftRotate(tree, z);
                }
                z->p->color = 'b';
                z->p->p->color = 'r';
                rightRotate(tree, z->p->p);
            }
        }
        else {
            y = z->p->p->l;
            if (y->color == 'r') {
                z->p->color = 'b';
                y->color = 'b';
                z->p->p->color = 'r';
                z = z->p->p;
            }
            else {
                if (z == z->p->l) {
                    z = z->p;
                    rightRotate(tree, z);
                }
                z->p->color = 'b';
                z->p->p->color = 'r';
                leftRotate(tree, z->p->p);
            }
        }
    }
    tree->tRoot->color = 'b';
}

/**
 * 삽입
 */
void Insert(struct rbTree* tree, struct Node* z) {
    struct Node* y = tree->tNil;
    struct Node* x = tree->tRoot;

    while (x != tree->tNil) {
        y = x;
        if (z->key < x->key) {
            x = x->l;
        }
        else {
            x = x->r;
        }
    }
    z->p = y;
    if (y == tree->tNil) {
        tree->tRoot = z;
    }
    else if (z->key < y->key) {
        y->l = z;
    }
    else {
        y->r = z;
    }
    z->l = tree->tNil;
    z->r = tree->tNil;

    z->color = 'r';
    fixUp(tree, z);
    tree->tRoot->p = tree->tNil;
}

// 트리 깊이 계산
int getDepth(struct rbTree* tree, struct Node* node) {
    if (node == tree->tNil) return 0;
    int lDepth = getDepth(tree, node->l);
    int rDepth = getDepth(tree, node->r);
    return (lDepth > rDepth ? lDepth : rDepth) + 1;
}

// 트리 출력용 배열 초기화
void initCanvas(char canvas[MAX_HEIGHT][MAX_WIDTH][8]) {
    for (int i = 0; i < MAX_HEIGHT; i++)
        for (int j = 0; j < MAX_WIDTH; j++)
            canvas[i][j][0] = '\0';
}

// 재귀적으로 노드 배치
void fillCanvas(struct rbTree* tree, struct Node* node, char canvas[MAX_HEIGHT][MAX_WIDTH][8], int row, int left, int right) {
    if (node == tree->tNil || row >= MAX_HEIGHT || left > right) return;
    //if (row >= MAX_HEIGHT || left > right) return;

    int mid = (left + right) / 2;

    //if (node == tree->tNil) {
    //    // NIL 표시
    //    snprintf(canvas[row][mid], 8, "NIL(B)");
    //    return;
    //}

    // 노드 문자열 생성
    int n = snprintf(canvas[row][mid], 8, "%d(%c)", node->key, node->color);

    // 좌우 자식 배치
    fillCanvas(tree, node->l, canvas, row + 1, left, mid - 1);
    fillCanvas(tree, node->r, canvas, row + 1, mid + 1, right);
}

// canvas를 한 줄씩 출력
void printCanvas(char canvas[MAX_HEIGHT][MAX_WIDTH][8], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        int empty = 1;
        for (int j = 0; j < cols; j++) {
            if (canvas[i][j][0] != '\0') {
                printf("%s", canvas[i][j]);
				j += 6; // 노드 문자열 길이만큼 건너뜀
                empty = 0;
            }
            else {
                printf(" ");
            }
        }
        if (!empty) printf("\n");
    }
}

// 최종 트리 출력 함수
void printTree(struct rbTree* tree) {
    if (tree->tRoot == tree->tNil) {
        printf("(empty tree)\n");
        return;
    }

    char canvas[MAX_HEIGHT][MAX_WIDTH][8];
    initCanvas(canvas);

    int depth = getDepth(tree, tree->tRoot);
    fillCanvas(tree, tree->tRoot, canvas, 0, 0, MAX_WIDTH - 1);

    printCanvas(canvas, MAX_HEIGHT, MAX_WIDTH);
}

int main() {
    struct rbTree* tree = initTree();
    int keys[] = { 13, 8, 17, 1, 11, 15, 25, 6, 22, 27 };

    printf("===================  Insert =================== \n");
    for (int i = 0; i < SIZE; i++) {
        struct Node* n = (struct Node*)malloc(sizeof(struct Node));
        n->key = keys[i];
        Insert(tree, n);
    }
    printTree(tree);

	printf("\n=================== Insert 19 =================== \n");
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
	n->key = 19;
	Insert(tree, n);
    printTree(tree);

	return 0;
}