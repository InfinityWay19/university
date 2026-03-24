#include <stdio.h>

#define N 15

int count_primes(int arr[], int size)
{
    int count = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] > 1) {
            int isPrime = 1;

            for (int j = 2; j * j <= arr[i]; j++) {
                if (arr[i] % j == 0) {
                    isPrime = 0;
                    break;
                }
            }

            if (isPrime)
                count++;
        }
    }

    return count;
}

int main()
{
    int arr1[N], arr2[N];
    int c1, c2;

    printf("Введите элементы первого массива:\n");
    for (int i = 0; i < N; i++) {
        printf("arr1[%d] = ", i);
        scanf("%d", &arr1[i]);
    }

    printf("\nВведите элементы второго массива:\n");
    for (int i = 0; i < N; i++) {
        printf("arr2[%d] = ", i);
        scanf("%d", &arr2[i]);
    }

    c1 = count_primes(arr1, N);
    c2 = count_primes(arr2, N);

    printf("\nКоличество простых чисел в первом массиве: %d\n", c1);
    printf("Количество простых чисел во втором массиве: %d\n", c2);

    return 0;
}
