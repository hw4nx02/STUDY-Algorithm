#include <stdio.h>
#include <stdlib.h>

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
    for (int i = d-1; i >= 0; i--) {
        k[i] = M / c[i];
        printf("k[%d] = %d\n", i, k[i]);
        M = M % c[i];
        printf("M = %d\n", M);
    }

    return k;
}

void main() {
    int M = 37;
    int d = 5;
    int c[] = {1, 5, 10, 20, 25};

    int* result = function(M, d, c);
    for (int i = 0; i < d; i++) {
        printf("result %d\n", result[i]);
    }
}