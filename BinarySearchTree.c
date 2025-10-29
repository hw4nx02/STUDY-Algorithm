#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
    int key;
    struct node* l;
    struct node* r; 
};

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

void treeDelete(struct node* head, int xkey) {
    struct node *p, *c, *t, *x;
    p = head;
    x = head->r;
    x= treeSearch(x, xkey); // 삭제할 키 탐색
    if (x == NULL) return;
    else t = x;
    if (t->r == NULL) x = t->l; // 오른쪽 자식 없는 경우
    // 오른쪽 자식 있는데
    else if (t->r->l == NULL) { // 오른쪽 자식의 왼쪽 자식 없는 경우
        x = t->r;
        x->l = t->l;
    }
    else { // 오른쪽 자식의 왼쪽 자식 있는 경우
        c = x->r;
        while(c->l->l != NULL) c = c->l;
        x = c->l;
        c->l = x->r;
        x->l = t->l;
        x->r = t->r;
    }

    free(t);
    if (xkey < p->key) p->l = x;
    else p->r = x;
}

int main() {
    struct node* head = treeInit();

    int size = 10;
    srand(time(0));
    printf("임의로 생성된 %d개의 숫자들: ", size);
    for (int i = 0; i < size; i++) {
        int num =  rand() % 10 + 1;
        treeInsert(head, num);
        printf("%d ", num);
    }

    int key;
    printf("\n탐색할 키를 입력: ");
    scanf("%d", &key);

    treeSearch(head, key);

}