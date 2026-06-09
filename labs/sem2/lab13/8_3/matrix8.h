#ifndef MATRIX8_H
#define MATRIX8_H

#define ROWS 6
#define COLS 5

// Ссылка на матрицу, объявленную в main.c
extern int D[ROWS][COLS];

// Подпрограмма вычисления суммы неотрицательных элементов строки
int sum_non_negative(int row[], int size);

#endif