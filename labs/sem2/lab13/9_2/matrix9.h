#ifndef MATRIX9_H
#define MATRIX9_H

#define V_ROWS 2
#define V_COLS 3
#define W_ROWS 3
#define W_COLS 2

// Ссылки на переменные, объявленные в main.c
extern int V[V_ROWS][V_COLS];
extern int W[W_ROWS][W_COLS];
extern int VV[V_ROWS * V_COLS];
extern int WW[W_ROWS * W_COLS];

// Подпрограмма обработки матрицы
void process_matrix(int rows, int cols, int M[rows][cols],
                    int arr[], int *max_i, int *max_j);

#endif