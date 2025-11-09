#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } color_t;

typedef struct Node {
    int key;
    color_t color;
    struct Node* left, * right, * parent;
} Node;

Node* NIL;
Node* ROOT;

/* 초기화 및 유틸 */
void tree_init() {
    NIL = (Node*)malloc(sizeof(Node));
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = NIL;
    ROOT = NIL;
}

Node* new_node(int key) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->color = RED;
    n->left = n->right = n->parent = NIL;
    return n;
}

/* 회전 */
void left_rotate(Node** Troot, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL)
        *Troot = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void right_rotate(Node** Troot, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != NIL) x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NIL)
        *Troot = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;
    x->right = y;
    y->parent = x;
}

/* 삽입 */
void rb_insert_fixup(Node** Troot, Node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(Troot, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(Troot, z->parent->parent);
            }
        }
        else {
            Node* y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(Troot, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(Troot, z->parent->parent);
            }
        }
    }
    (*Troot)->color = BLACK;
}

void rb_insert(Node** Troot, Node* z) {
    Node* y = NIL;
    Node* x = *Troot;
    while (x != NIL) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if (y == NIL) *Troot = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;
    z->left = z->right = NIL;
    z->color = RED;
    rb_insert_fixup(Troot, z);
}

/* 삭제 보조 */
void rb_transplant(Node** Troot, Node* u, Node* v) {
    if (u->parent == NIL)
        *Troot = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != NIL)                // <-- 중요 수정: v가 NIL이면 parent를 바꾸지 않는다
        v->parent = u->parent;
}

Node* tree_minimum(Node* x) {
    while (x->left != NIL) x = x->left;
    return x;
}

void rb_delete_fixup(Node** Troot, Node* x) {
    while (x != *Troot && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(Troot, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(Troot, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(Troot, x->parent);
                x = *Troot;
            }
        }
        else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(Troot, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(Troot, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(Troot, x->parent);
                x = *Troot;
            }
        }
    }
    x->color = BLACK;
}

/* rb_delete: 삭제 대상 해제는 fixup 이후에 수행 */
void rb_delete(Node** Troot, Node* z) {
    Node* y = z;
    color_t y_original_color = y->color;
    Node* x;
    Node* to_free = z; // 해제할 노드(안전하게 마지막에 free)

    if (z->left == NIL) {
        x = z->right;
        rb_transplant(Troot, z, z->right);
    }
    else if (z->right == NIL) {
        x = z->left;
        rb_transplant(Troot, z, z->left);
    }
    else {
        y = tree_minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
            // y가 z의 직속 오른쪽 자식인 경우 (transplant 필요 없음)
        }
        else {
            rb_transplant(Troot, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rb_transplant(Troot, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
        to_free = z; // z를 해제
    }

    if (y_original_color == BLACK) {
        rb_delete_fixup(Troot, x);
    }

    // 이제 안전하게 메모리 해제
    free(to_free);
}

/* 탐색 */
Node* tree_search(Node* root, int key) {
    Node* x = root;
    while (x != NIL && key != x->key) {
        if (key < x->key) x = x->left;
        else x = x->right;
    }
    return x;
}

/* 간단한 레벨 출력 (배열 큐 사용) */
void print_tree_by_level(Node* root) {
    if (root == NIL) {
        printf("(empty tree)\n");
        return;
    }

    const int MAX_DEPTH = 6;
    const int MAX_NODES = 1 << (MAX_DEPTH + 1); // 여유 사이즈
    Node* queue[MAX_NODES];
    int front = 0, rear = 0;

    queue[rear++] = root;
    int level = 0;

    while (front < rear && level < MAX_DEPTH) {
        int levelCount = rear - front;
        int spacing = (1 << (MAX_DEPTH - level));

        for (int i = 0; i < spacing / 2; ++i) printf(" ");

        for (int i = 0; i < levelCount; ++i) {
            Node* node = queue[front++];
            if (node != NULL && node != NIL) {
                printf("%d(%c)", node->key, (node->color == RED ? 'R' : 'B'));
                queue[rear++] = node->left;
                queue[rear++] = node->right;
            }
            else {
                printf(".");
                queue[rear++] = NULL;
                queue[rear++] = NULL;
            }
            for (int s = 0; s < spacing; ++s) printf(" ");
        }
        printf("\n");
        level++;
    }
}

/* main: 간단한 테스트 */
int main(void) {
    tree_init();

    int keys[] = { 13, 8, 17, 1, 11, 15, 25, 6, 22, 27 };
    int n = sizeof(keys) / sizeof(keys[0]);

    printf("== INSERT ==\n");
    for (int i = 0; i < n; ++i) {
        Node* z = new_node(keys[i]);
        rb_insert(&ROOT, z);
    }

    printf("\nTree after insertions:\n");
    print_tree_by_level(ROOT);

    int dels[] = { 8, 17 };
    int dn = sizeof(dels) / sizeof(dels[0]);

    for (int i = 0; i < dn; ++i) {
        Node* z = tree_search(ROOT, dels[i]);
        if (z != NIL) {
            rb_delete(&ROOT, z);
            printf("\nTree after deleting %d:\n", dels[i]);
            print_tree_by_level(ROOT);
        }
        else {
            printf("\nKey %d not found for deletion.\n", dels[i]);
        }
    }

    return 0;
}
