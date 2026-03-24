#include <stdio.h>

#define N 15

int main() {
    int primes[N];

    printf("Введите %d простых чисел:\n", N);

    for (int i = 0; i < N; i++) {
        printf("primes[%d] = ", i);
        scanf("%d", &primes[i]);
    }

    printf("\nОдномерный массив:\n");

    for (int i = 0; i < N; i++) {
        printf("%d ", primes[i]);
    }

    printf("\n");

    return 0;
}
