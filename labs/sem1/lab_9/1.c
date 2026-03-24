#include <stdio.h>
#include <locale.h>

#define ROWS 4
#define COLS 8

void sort_rows_by_sum(double A[ROWS][COLS], int rows, int cols)
{
    double sum1, sum2, temp;

    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < rows - i - 1; j++) {

            sum1 = 0;
            sum2 = 0;

            for (int k = 0; k < cols; k++) {
                sum1 += A[j][k];
                sum2 += A[j + 1][k];
            }

            if (sum1 > sum2) {
                for (int k = 0; k < cols; k++) {
                    temp = A[j][k];
                    A[j][k] = A[j + 1][k];
                    A[j + 1][k] = temp;
                }
            }
        }
    }
}

void print_matrix(double A[ROWS][COLS], int rows, int cols)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%6.2f ", A[i][j]);
        printf("\n");
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    double A1[ROWS][COLS] = {
        { 1, 2, 3, 4, 5, 6, 7, 8 },
        { 8, 7, 6, 5, 4, 3, 2, 1 },
        { 2, 2, 2, 2, 2, 2, 2, 2 },
        { 9, 1, 1, 1, 1, 1, 1, 1 }
    };

    double A2[ROWS][COLS] = {
        { 5, 5, 5, 5, 5, 5, 5, 5 },
        { 1, 1, 1, 1, 1, 1, 1, 1 },
        { 3, 3, 3, 3, 3, 3, 3, 3 },
        { 2, 2, 2, 2, 2, 2, 2, 2 }
    };

    printf("Матрица A1 до сортировки:\n");
    print_matrix(A1, ROWS, COLS);

    sort_rows_by_sum(A1, ROWS, COLS);

    printf("\nМатрица A1 после сортировки:\n");
    print_matrix(A1, ROWS, COLS);

    printf("\nМатрица A2 до сортировки:\n");
    print_matrix(A2, ROWS, COLS);

    sort_rows_by_sum(A2, ROWS, COLS);

    printf("\nМатрица A2 после сортировки:\n");
    print_matrix(A2, ROWS, COLS);

    return 0;
}
