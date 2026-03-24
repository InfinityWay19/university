#include <stdio.h>

#define ROWS 6
#define COLS 5

// Подпрограмма для вычисления суммы неотрицательных элементов строки
int sum_non_negative(int row[], int size)
{
    int sum = 0;

    for (int i = 0; i < size; i++) {
        if (row[i] >= 0) {
            sum += row[i];
        }
    }

    return sum;
}

int main()
{
    int D[ROWS][COLS];
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
