#include <stdio.h>

#define NUM_OF_KEYS 10

/**
 * 합병
 */
void Merge(int a[], int left, int mid, int right) {
    int b[NUM_OF_KEYS] = {0}; // 정렬한 값을 차례로 넣어주기 위해 정렬 대상 배열과 동일한 크기의 배열 생성
    int i, leftPtr, rightPtr, bufferPtr = 0; // Ptr은 실제로 움직이는 인덱스

    leftPtr = left; // 좌측 배열 포인터
    rightPtr = mid + 1; // 우측 배열 포인터
    bufferPtr = left;

    // 정렬
    while (leftPtr <= mid && rightPtr <= right) {
        // 비교 후 작은 값을 버퍼에 저장
        if (a[leftPtr] < a[rightPtr]) {
            b[bufferPtr++] = a[leftPtr++];
        } else {
            b[bufferPtr++] = a[rightPtr++];
        }
    }
    // Ptr가 배열의 끝까지 읽어서 한 쪽 배열의 정렬이 끝났을 때, 나머지 다른 배열을 버퍼 배열에 그대로 붙여줌
    if (leftPtr > mid) { // 좌측 배열의 정렬이 먼저 끝났다면
        for (i = rightPtr; i <= right; i++) { // 우측 배열에서 남은 원소를 차례로 버퍼 배열에 붙임
            b[bufferPtr++] = a[i];
        }
    } else { // 우측 배열의 정렬이 먼저 끝났다면
        for (i = leftPtr; i <= mid; i++) { // 좌측 배열에서 남은 원소를 차례로 버퍼 배열에 붙임
            b[bufferPtr++] = a[i];
        }
    }

    // 정렬 결과를 담은 버퍼 배열의 값을 원래 배열로 복사
    for (i = left; i <= right; i++) {
        a[i] = b[i];
    }
}

/**
 * 합병 정렬 - 쪼개기 및 합병
 */
void MergeSort(int a[], int left, int right) {
    int mid = 0;

    if (left < right) { // 원소 두 개 이상이면
        mid = (left + right) / 2;
        MergeSort(a, left, mid);
        MergeSort(a, mid+1, right);
        Merge(a, left, mid, right);

        for (int i = 0; i < NUM_OF_KEYS; i++) {
            if (i == left) {
                printf("%c%d ", '|', a[i]);
            } else if (i == mid) {
                printf("%d%c", a[i], '/');
            } else if (i == right) {
                printf("%d%c", a[i], '|');
            } else {
                printf("%d%c", a[i], ' ');
            }
        }
        printf("\n");
    }
}

void main() {
    int a[NUM_OF_KEYS] = {30, 20, 40, 35, 5, 50, 45, 10, 25, 15};
    int left = 0;
    int right = 9;

    MergeSort(a, left, right);
}