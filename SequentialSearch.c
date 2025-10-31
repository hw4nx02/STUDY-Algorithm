#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNNING
#define SIZE 10

struct Node {
    int key;
    struct Node* link;
};

void insert(struct Node* head, int key) {
    struct Node* pos = head;
    struct Node* pre;
    while (pos != NULL) {
        pre = pos;
        pos = pre->link;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(*newNode));
    newNode->key = key;
    pre->link = newNode;
    newNode->link = NULL;
}

/**
 * 배열 순차 탐색
 * @param a 배열
 * @param key 찾을 키
 * return 찾은 키의 인덱스. 못 찾으면 0 반환
 */
int arrSeqSearch(int a[], int key){
    int i = 0;
    while ((i < SIZE) && a[i] != key) i++;
    return i;
}

/**
 * 연결 리스트 순차 탐색
 * @param head 연결 리스트의 첫 노드
 * @param key 찾을 키
 * return 찾은 키를 갖는 노드의 포인터. 없으면 NULL 반환(끝까지 가니까)
 */
struct Node* llSeqSearch(struct Node* head, int key) {
    struct Node* pos = head->link;
    while ((pos != NULL) && (pos->key != key)) pos = pos->link;

    return pos;
}

int main() {
    int a[SIZE];
    struct Node* head = (struct Node*)malloc(sizeof(*head));
    head->key = 0;
    head->link = NULL;

    srand(time(0));
    for (int i = 0; i < SIZE; i++) {
        int num = rand() % 10 + 1;
        a[i] = num;
        insert(head, num);
    }

    printf("random number in array: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d%c", a[i], (i == SIZE-1)?'\n':' ');
    }
    printf("random number in linked list: ");
    struct Node* pos = head->link;
    while (pos != NULL) {
        printf("%d ", pos->key);
        pos = pos->link;
    }
    printf("\n");

    int num;
    printf("input number for search: ");
    scanf("%d", &num);

    printf("sequential search used by array: %d\n", arrSeqSearch(a, num));
    printf("sequential Search used by linked list: %d\n", llSeqSearch(head, num)->key);
}