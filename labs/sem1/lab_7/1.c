#include <stdio.h>
#include <locale.h>

#define ROWS 4
#define COLS 8

int main() {
    setlocale(LC_ALL, "Russian");

    double A[ROWS][COLS];
    double sum1, sum2, temp;

    printf("Введите матрицу 4×8:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    printf("\nИсходная матрица:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++)
            printf("%6.2f ", A[i][j]);
        printf("\n");
    }

    for (int i = 0; i < ROWS - 1; i++) {
        for (int j = 0; j < ROWS - i - 1; j++) {

            sum1 = 0;
            for (int k = 0; k < COLS; k++)
                sum1 += A[j][k];

            sum2 = 0;
            for (int k = 0; k < COLS; k++)
                sum2 += A[j + 1][k];

            if (sum1 > sum2) {
                for (int k = 0; k < COLS; k++) {
                    temp = A[j][k];
                    A[j][k] = A[j + 1][k];
                    A[j + 1][k] = temp;
                }
            }
        }
    }

    printf("\nМатрица после сортировки строк по возрастанию сумм:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++)
            printf("%6.2f ", A[i][j]);
        printf("\n");
    }

    return 0;
}
