#include <stdio.h>
#include <limits.h>

int DynamicProgramming(int M, int d, int c[], int track[]) {
    int dp[M+1]; // 인덱스: 남은 금액, 값: 해당 금액을 만드는 최소 경우의 수
    for (int i = 0; i < M+1; i++) {
        dp[i] = INT_MAX;
        track[i] = 0;
    }
    dp[0] = 0;

    for (int i = 1; i < M+1; i++) { // 1원부터 M원까지
        for (int j = 0; j < d; j++) {
            if ((i - c[j] >= 0) && (dp[i - c[j]]) != INT_MAX && (dp[i] > dp[i - c[j]] + 1)) { // i원을 만들 때, i-c원에서 c를 더할 때 그 경우의 수가 가장 작은 것으로 최신화
                dp[i] = dp[i - c[j]] +1;
                track[i] = j;
            } 
        }
    }

    return dp[M];
}

void main() {
    int M = 37;
    int d = 5;
    int c[] = {1, 5, 10, 20, 25};
    int track[M+1]; // 백트래킹을 위함. 인덱스를 남은 금액, item은 해당 금액 전의 금액

    int min = DynamicProgramming(M, d, c, track);
 
    printf("최소 동전 개수: %d\n", min);

    int idx = M;
    while (idx > 0) {
        int cIdx = track[idx];
        if (cIdx < 0) break;

        printf("-> %d ", c[cIdx]);
        idx -= c[cIdx];
    }
}