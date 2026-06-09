#include <stdio.h>
#include "matrix9.h"

// Все переменные объявлены здесь — модуль matrix9.c обращается к ним через extern
int V[V_ROWS][V_COLS] = {
    { 1, 7, 3 },
    { 4, 2, 6 }
};

int W[W_ROWS][W_COLS] = {
    { 5, 1 },
    { 9, 2 },
    { 4, 8 }
};

int VV[V_ROWS * V_COLS];
int WW[W_ROWS * W_COLS];

int main()
{
    int max_i, max_j;

    // Обработка матрицы V
    process_matrix(V_ROWS, V_COLS, V, VV, &max_i, &max_j);

    printf("Массив VV:\n");
    for (int i = 0; i < V_ROWS * V_COLS; i++)
        printf("%d ", VV[i]);

    printf("\nМаксимальный элемент матрицы V имеет индексы: (%d, %d)\n",
           max_i, max_j);

    // Обработка матрицы W
    process_matrix(W_ROWS, W_COLS, W, WW, &max_i, &max_j);

    printf("\nМассив WW:\n");
    for (int i = 0; i < W_ROWS * W_COLS; i++)
        printf("%d ", WW[i]);

    printf("\nМаксимальный элемент матрицы W имеет индексы: (%d, %d)\n",
           max_i, max_j);

    return 0;
}