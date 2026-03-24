#include <stdio.h>

#define V_ROWS 2
#define V_COLS 3
#define W_ROWS 3
#define W_COLS 2

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

int main()
{
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

    int max_i, max_j;

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
