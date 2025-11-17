#include <stdio.h>
#define T_SIZE 8
#define P_SIZE 4

int SP[P_SIZE] = {0};

void ComputeSP(char p[], int sp[]) {
    sp[0] = -1;
    int k = -1;
    for (int j = 1; j <= P_SIZE-1; j++) {
        printf("\nk+1: %d, j: %d", k+1, j);
        printf("\np[k+1]:%d vs p[j]:%d", p[k+1], p[j]);
        while (k >= 0 && (p[k+1]!=p[j])) {
            k = sp[k];
            printf("\nk: %d, j: %d, sp[k]: %d", k, j, sp[k]);
        }
        if (p[k+1] == p[j]) {
            k++;
            printf("\nk: %d", k);
        }
        sp[j] = k;
        printf("\nj: %d, sp[j]: %d", j, sp[j]);
    }
}

void KMP(char p[], char t[]) {
    ComputeSP(p, SP);
    int j = -1;
    for (int i=0; i <= T_SIZE-1; i++) {
        while (j >= 0 && p[j+1] != t[i]) j = SP[j];
        if (p[j+1] == t[i]) j++;
        if (j == P_SIZE-1) {
            printf("\n패턴이 T[%d]~T[%d]에서 일치함", i-P_SIZE+1, i);
            j = SP[j];
        }
    }
}

int main() {
    char T[] = {'a','b','a','b','a','b','a','b'};
    char P[] = {'a','b','a','b'};

    KMP(P, T);
    printf("\n");
    for (int i = 0; i < P_SIZE; i++) {
        printf("%d ", SP[i]);
    }
}