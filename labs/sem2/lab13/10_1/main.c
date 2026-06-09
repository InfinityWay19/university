#include <stdio.h>
#include "arrays.h"

// Массивы объявлены здесь — модуль arrays.c обращается к ним через extern
int A[SIZE];
int B[SIZE];
int C[SIZE];

int main()
{
    // Ввод массивов
    printf("Введите элементы массива A[%d]:\n", SIZE);
    for (int i = 0; i < SIZE; i++) {
        printf("A[%d] = ", i);
        scanf("%d", &A[i]);
    }

    printf("Введите элементы массива B[%d]:\n", SIZE);
    for (int i = 0; i < SIZE; i++) {
        printf("B[%d] = ", i);
        scanf("%d", &B[i]);
    }

    printf("Введите элементы массива C[%d]:\n", SIZE);
    for (int i = 0; i < SIZE; i++) {
        printf("C[%d] = ", i);
        scanf("%d", &C[i]);
    }

    // Печать исходных массивов
    printf("\n--- Исходные массивы ---\n");
    print_array("A", A, SIZE);
    print_array("B", B, SIZE);
    print_array("C", C, SIZE);

    // Преобразование
    rotate_right(A, SIZE);
    rotate_right(B, SIZE);
    rotate_right(C, SIZE);

    // Печать результирующих массивов
    printf("\n--- Результирующие массивы ---\n");
    print_array("A", A, SIZE);
    print_array("B", B, SIZE);
    print_array("C", C, SIZE);

    // Печать последних двух элементов
    printf("\n--- Последние два элемента результирующих массивов ---\n");
    print_last_two("A", A, SIZE);
    print_last_two("B", B, SIZE);
    print_last_two("C", C, SIZE);

    return 0;
}