#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
/**
 * M 금액
 * d 금액 단위 갯수
 * c 금액 단위 종류
 */
int* function(int M, int d, int c[]) {
    int* k = malloc(d * sizeof(int));
    for (int j = 0; j < d; j++) {
        k[j] = 0;
    }

    // 최소 동전 갯수: 처음에는 무한대처럼 설정
    int smallestNumberOfCoins = INT_MAX;

    // 가능한 모든 조합 (k1, k2, k3, k4, k5)를 확인
    // 각 동전 i는 최대 M / c[i]개까지 사용할 수 있음: 총 금액을 해당 단위로 나눈 값
    for (int k1 = 0; k1 <= M/c[0]; k1++) {
        for (int k2 = 0; k2 <= M/c[1]; k2++) {
            for (int k3 = 0; k3 <= M/c[2]; k3++) {
                for (int k4 = 0; k4 <= M/c[3]; k4++) {
                    for (int k5 = 0; k5 <= M/c[4]; k5++) {

                        // 가능한 동전 가치의 합
                        int valueOfCoins = c[0]*k1 + c[1]*k2 + c[2]*k3 + c[3]*k4 + c[4]*k5;

                        // 동전 가치의 합이 목표 금액(M, 나눠 내고자 했던 금액)을 정확히 만들었을 때를 체크
                        if (valueOfCoins == M) {
                            int numberOfCoins = k1 + k2 + k3 + k4 + k5;
                            printf("k1: %d, k2: %d, k3: %d, k4: %d, k5: %d\n", k1, k2, k3, k4, k5);

                            // 최소 동전 갯수 갱신
                            if (numberOfCoins < smallestNumberOfCoins) {
                                smallestNumberOfCoins = numberOfCoins;
                                k[0] = k1;
                                k[1] = k2;
                                k[2] = k3;
                                k[3] = k4;
                                k[4] = k5;
                            }
                        }
                    }
                }
            }
        }
    }

    return k;
}

void main() {
    int M = 37;
    int d = 5;
    int c[] = {1, 5, 10, 20, 25};

    int* result = function(M, d, c);
    for (int i = 0; i < d; i++) {
        printf("result[%d] %d\n", i, result[i]);
    }
}