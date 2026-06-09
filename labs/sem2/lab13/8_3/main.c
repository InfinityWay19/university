#include <stdio.h>
#include "matrix8.h"

// Матрица объявлена здесь — на неё ссылается модуль matrix8.c через extern
int D[ROWS][COLS];

int main()
{
    int minSum;
    int currentSum;

    printf("Введите элементы матрицы %dx%d:\n", ROWS, COLS);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("D[%d][%d] = ", i, j);
            scanf("%d", &D[i][j]);
        }
    }

    // Сумма для первой строки
    minSum = sum_non_negative(D[0], COLS);

    // Обработка остальных строк
    for (int i = 1; i < ROWS; i++) {
        currentSum = sum_non_negative(D[i], COLS);
        if (currentSum < minSum) {
            minSum = currentSum;
        }
    }

    printf("\nНаименьшая сумма неотрицательных элементов строк: %d\n", minSum);

    return 0;
}