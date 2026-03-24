#include <stdio.h>

#define k 4.0
int main() {
    int a[10][10]; 
    printf("Таблица Пифагора \n");
    for (int i = 1; i <= 10; ++i) {
        for (int j = 1; j <= 10; ++j) {
            a[i - 1][j - 1] = i * j;
            printf(" %3.0d", a[i-1][j-1]);
        }
        printf("\n");
    }
    return 0;
}