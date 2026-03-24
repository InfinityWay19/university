#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");
    const int primes[15] = {
        2, 3, 5, 7, 11,
        13, 17, 19, 23, 29,
        31, 37, 41, 43, 47
    };

    printf("Одномерный массив из 15 простых чисел:\n");

    for (int i = 0; i < 15; i++) {
        printf("%d ", primes[i]);
    }

    printf("\n");
    return 0;
}