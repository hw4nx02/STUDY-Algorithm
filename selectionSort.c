#include <stdio.h>

/** 선택 정렬 */
void SelectionSort(int A[], int n) {
    int minIdx; // 최소 인덱스

    for (int i = 0; i < n; i++) {
        minIdx = i; // 현재 포지션을 최소 인덱스로
        for (int j = minIdx + 1; j < n; j++) { // 현재 포지션 이후의 원소들에 대해 최솟값 찾기
            if (A[minIdx] > A[j]) {
                minIdx = j;
            }
        }
        if (minIdx != i) { // 현재 포지션과 최솟값이 다른 것이면 교체 
            int tmp = A[minIdx];
            A[minIdx] = A[i];
            A[i] = tmp;
        }

        /** 단계별 출력 */
        for (int k = 0; k < n; k++) {
            if (k == i) {
                printf("[%d]%c", A[k], (k == n-1)?'\n':'\t');
                continue;
            }
            if (k == minIdx) {
                printf("[%d]%c", A[k], (k == n-1)?'\n':'\t');
                continue;
            }
            printf("%d%c", A[k], (k == n-1)?'\n':'\t');
        }
    }
}

void main() {
    int A[] = {30, 20, 40, 10, 5, 10, 30, 15};
    int n = 8;

    SelectionSort(A, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
}