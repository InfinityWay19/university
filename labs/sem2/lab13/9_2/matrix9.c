#include "matrix9.h"

// Ссылки на переменные, объявленные в main.c
extern int V[V_ROWS][V_COLS];
extern int W[W_ROWS][W_COLS];
extern int VV[V_ROWS * V_COLS];
extern int WW[W_ROWS * W_COLS];

// Подпрограмма: разворачивает матрицу в массив и находит максимум
void process_matrix(int rows, int cols, int M[rows][cols],
                    int arr[], int *max_i, int *max_j)
{
    int k = 0;
    int max = M[0][0];

    *max_i = 0;
    *max_j = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            arr[k++] = M[i][j];

            if (M[i][j] > max) {
                max = M[i][j];
                *max_i = i;
                *max_j = j;
            }
        }
    }
}