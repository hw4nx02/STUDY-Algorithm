#include <stdio.h>

/**
 * 삽입 정렬
 * @param a 입력 배열
 * @param n 입력 배열의 원소 개수
 * @param return 정렬에 사용된 비교 횟수
 */
int solution(int a[], int n) {
    int result = 0;

    // n번째를 비교할 때 a[1:n-1]은 이미 정렬되었으므로, 
    // n번째 원소가 들어갈 자리를 우측에서부터 찾아나가는 방식

    int i, j, value = 0;
    for (i=2; i<= n; i++) { // 앞의 원소부터 차례로 검사
        value = a[i]; // 현재 자리를 찾을 값
        j = i; // 비교할 원소의 인덱스
        while (a[j-1] > value) { // 자리를 찾을 값과 바로 앞에 있는 원소부터 비교해서 더 작으면
            a[j] = a[j - 1]; // 비교 값의 위치르 우측으로 한 칸 당김
            j--; // 비교 인덱스는 하나 내림
        }
        a[j] = value; // 자리 찾는 값보다 작은 값을 발견했을 때, 그 뒷자리에 value 배정

        for (int k=1; k<=n; k++) {
            printf("%d%c", a[k], (k==n) ? '\n' : ' ');
        }
    }

    return result;
}

void main() {
    int a[] = {-1, 30, 20, 40, 10, 5, 10, 30, 15};
    int n = 8;

    for (int i=1; i<=n; i++) {
        printf("%d%c", a[i], (i==n)?'\n':' ');
    }
    int sol = solution(a, n);
}