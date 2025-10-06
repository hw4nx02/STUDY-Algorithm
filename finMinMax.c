#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

/**
 * 최솟값 찾기
 * @param a n개의 숫자가 저장되어 있는 배열
 * @param n 배열 a에 저장되어 있는 숫자의 갯수
 * @return 배열 a에서의 최솟값
 */
int Minimum(int a[], int n) {
    int i, temp; // 각각 인덱스, 비교 후 최솟값으로 최신화될 값
    temp = a[0]; // 초기화

    // 비교 후 최솟값을 최신화
    for (i = 1; i < n; i++) {
        if (temp > a[i]) {
            temp = a[i];
        }
    }

    // 최솟값 반환
    return temp;
}

/**
 * 최댓값 찾기
 * @param a n개의 숫자가 저장되어 있는 배열
 * @param n 배열 a에 저장되어 있는 숫자의 갯수
 * @return 배열 a에서의 최댓값
 */
int Maximum(int a[], int n) {
    int i, temp; // 각각 인덱스, 비교 후 최댓값으로 최신화될 값
    temp = a[0]; // 초기화

    // 비교 후 최댓값을 최신화
    for (i = 1; i < n; i++) {
        if (temp < a[i]) {
            temp = a[i];
        }
    }

    // 최댓값 반환
    return temp;
}

/**
 * 최댓값, 최솟값 동시 찾기
 * @param a n개의 숫자가 저장되어 있는 배열
 * @param n 배열 a에 저장되어 있는 숫자의 갯수
 * @param min 최솟값 변수 포인터
 * @param max 최댓값 변수 포인터
 */
void FindMinMax(int a[], int n, int* min, int* max) {
    int i, small, large; // 각각 인덱스, 배열의 원소를 두 개 뽑아 서로 비교했을 때 작은 값과 큰 값
    *min = a[0]; // 초기화
    *max = a[0]; // 초기화

    // 원소를 두 개씩 서로 비교하여
    // 큰 값은 최댓값과, 작은 값은 최솟값과 비교해서 최댓값, 최솟값을 갱신
    for (i = 1; i < n-1; i += 2) { // 원소를 두 개씩 뽑기 때문에 n-1까지, 2씩 올려 반복문을 수행
        if (a[i] < a[i+1]) { // i번째와 그 옆자리 원소를 비교해서 작은 값이 small, 큰 값이 large
            small = a[i];
            large = a[i+1];
        } else {
            small = a[i+1];
            large = a[i];
        }

        // small이 최솟값보다 작은 경우, large가 큰 값보다 큰 경우에 대해 값을 갱신
        if (small < *min) *min = small;
        if (large > *max) *max = large;
    }
}

void main() {
    // 배열 생성
    int n = SIZE;
    int a[SIZE] = {0};

    // 랜덤한 정수로 배열 초기화
    printf("배열 a의 원소: \n");
    srand(time(0));
    for (int i = 0; i < SIZE; i++) {
        a[i] = rand() % 100000 + 1;
        printf("'%d'%c", a[i], (i == SIZE-1)?'\n':' ');
    }

    /** Minimum 함수와 이를 응용한 Maximum 함수를 이용하여 최솟값과 최댓값 찾기 */
    int minByMinimum = Minimum(a, n);
    int maxByMaximum = Maximum(a, n);
    printf("\nMinimum 함수와 Maximum 함수를 이용하여 최솟값과 최댓값 찾기\n최솟값: %d\n최댓값: %d\n", minByMinimum, maxByMaximum);

    /** FindMinMax 함수를 이용하여 최솟값과 최댓값 찾기 */
    int minByFindMinMax, maxByFindMinMax;
    FindMinMax(a, n, &minByFindMinMax, &maxByFindMinMax);
    printf("\nFindMinMax 함수를 이용하여 동시에 최솟값과 최댓값 찾기\n최솟값: %d\n최댓값: %d", minByFindMinMax, maxByFindMinMax);   
}