#include <stdio.h>
#define SIZE 10

int partition(int a[], int left, int right) {
    int partElem, value = 0;

    partElem = left; // 분할 원소 인덱스
    value = a[partElem]; // 분할 원소

    do {
        do {} while(a[++left] < value); // 좌측 배열에서 분할 원소보다 작으면 좌측 인덱스 계속 증가  
        do {} while(a[--right] > value); // 우측 배열에서 분할 원소보다 크면 우측 인덱스 계속 감소
        if (left < right) { // 분할 원소 기준 큰 원소가 좌측, 작은 원소가 우측에 있고, 둘이 만나기 전이면, 서로 교환
            int tmp = a[left];
            a[left] = a[right];
            a[right] = tmp;
        } else break;
    } while (1); // 좌우측이 만날 때까지 시행 반복

    // 분할 원소가 정렬을 통해 들어갈 자리에 있던 원소와 분할 원소를 서로 교환
    a[partElem] = a[right]; // 원래 있던 원소를 분할 원소로 설정
    a[right] = value; // 분할 원소가 정렬을 통해 자리를 찾음

    return right; // 분할점(분할 원소였던 것의 인덱스)
}

void QuickSort(int a[], int left, int right) {
    int k = 0;
    if (right > left) { // 우측 인덱스와 좌측 인덱스가 교차하지 않음
        k = partition(a, left, right + 1); // 분할 원소 인덱스(분할점)
        for (int i = 0; i < SIZE; i++) {
            if (i == k) {
                printf("[%d] ", a[i]);
            } else {
                printf("%d ", a[i]);
            }
        } printf("\n");

        QuickSort(a, left, k-1); // 분할 원소 기준 좌측 배열 퀵 정렬
        QuickSort(a, k+1, right); // 분할 원소 기준 우측 배열 퀵 정렬
    }
}

void main() {
    int a[] = {30, 20, 40, 35, 5, 10, 45, 50, 25, 15};
    int left = 0;
    int right = 9;

    for (int i=0; i<SIZE; i++) {
        printf("%d%c", a[i], (i==SIZE-1)?'\n':' ');
    }

    QuickSort(a, left, right);
}