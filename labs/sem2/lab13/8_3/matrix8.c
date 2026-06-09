#include "matrix8.h"

// Определение ссылки на внешнюю переменную D из main.c
extern int D[ROWS][COLS];

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