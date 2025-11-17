#include <stdio.h>
#define T_SIZE 8
#define P_SIZE 4

/**
 * d = 진법수
 * q = hash 함수에서 나누는 수 역할
 */
void RabinKarp(char T[], char P[], int d, int q) {
    int D = 1;
    for (int i = 0; i < P_SIZE-1; i++) {
        D *= d;
    }
    D = D % q;


    int h = 0;
    int t = 0;

    for (int i = 0; i <= P_SIZE-1; i++) {
        h = (d*h + P[i]) % q;
        t = (d*t + T[i]) % q;
    }
    for (int s = 0; s < T_SIZE-P_SIZE+1; s++) {
        if (h == t) {
            for (int i = 0; i < P_SIZE; i++) {
                if (P[i] != T[s+i]) break;
                if (i == P_SIZE-1) {
                    printf("\n패턴이 위치 %d에서 발생", s);
                }
            }
        }
        if (s < T_SIZE-P_SIZE) {
            t = (d*(t-T[s]*D) + T[s+P_SIZE]) % q;
        }
    }
}

int main() {
    char T[] = {'a','b','a','b','a','b','a','b'};
    char P[] = {'a','b','a','b'};

    RabinKarp(T, P, 26, 13);
}