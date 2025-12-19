#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_NO_SECURE_WARNNING
#define SIZE 10

int bisearch(int k, int a[]) {
    int low, high, mid;
    low = 1;
    high = SIZE;

    while(low <= high) {
        mid = (low + high) / 2;
        if (k == a[mid]) return mid;
        if (k < a[mid]) high = mid - 1;
        if (k > a[mid]) low = mid + 1;
    }

    return 0;
}

int main() {
    int a[SIZE];
    srand(time(0));
    printf("배열의 원소: ");
    for (int i = 0; i < SIZE; i++) {
        a[i] = rand() % 100 + 1;
        printf("%d\t", a[i]);
    }

    int key;
    printf("\n위치를 찾을 원소를 입력: ");
    scanf("%d", &key);

    int index = bisearch(key, a);
    printf("%d의 위치는 %d", key, index);
}