#include <stdio.h>
#include <string.h>
#define SIZE 1024

/** 복소수 구조체 */
typedef struct _complex {
    int real; // 실수부
    int imagin; // 허수부
} complex;

/** 거듭제곱 계산 */
long long power(int base, int exp) {
    // 계산
    long long result = 1;
    while (exp > 0) {
        if (exp%2 == 1) result *= base;
        base *= base;
        exp /= 2;
    }

    return result;
}

int main() {
    // 사용자 입력
    printf("input your complex number: "); // a + bi 형태 입력
    char input[SIZE] = "0";
    fgets(input, sizeof(input), stdin);

    // 복소수 구조체로 정리
    int plusIdx = -1, iIdx = -1;
    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        if (input[i] == '+') plusIdx = i;
        else if (input[i] == 'i') {
            iIdx = i;
            break;
        }
    }

    complex c = { 0, 0};
    for (int i = 0; i < plusIdx - 1; i++) {
        c.real = 10 * c.real + (input[i] - '0');
    }
    for (int i = plusIdx + 2; i < iIdx; i++) {
        c.imagin = 10 * c.imagin + (input[i] - '0');
    }

    // 유효성 검사
    if (c.real <= 0 || c.imagin <= 0) { // 범위를 벗어나면 -1 출력
        printf("\nresult: -1");        
        return 0;
    }
    // 계산
    long long result = power(c.imagin, 2 * c.real);
    int sign = (c.real % 2 == 0)? 1: -1;
    result *= sign;

    // 출력
    printf("\nreal: %d / imagin: %d", c.real, c.imagin);
    printf("\nresult: %lld", result);
}