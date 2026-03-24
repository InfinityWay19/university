#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS
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
    FILE *source, *result;

    source=fopen("source.txt", "r");
    result=fopen("result.txt", "w");

    int V[V_ROWS][V_COLS];
    int W[W_ROWS][W_COLS];

    for (int i=0; i<V_ROWS; i++) {
        for (int j=0; j<V_COLS; j++) {
            fscanf(source, "%d", &V[i][j]);
        }
    }

    for (int i=0; i<W_ROWS; i++) {
        for (int j=0; j<W_COLS; j++) {
            fscanf(source, "%d", &W[i][j]);
        }
    }

    int VV[V_ROWS * V_COLS];
    int WW[W_ROWS * W_COLS];
    int max_i, max_j;

    process_matrix(V_ROWS, V_COLS, V, VV, &max_i, &max_j);

    fprintf(result, "Массив VV:\n");
    for (int i=0; i<V_ROWS * V_COLS; i++) {
        fprintf(result, "%2d", VV[i]);
    }

    fprintf(result, "\nМакс элемент матрицы V: (%d, %d)\n\n", max_i, max_j);

    process_matrix(W_ROWS, W_COLS, W, WW, &max_i, &max_j);

    fprintf(result, "Массив WW:\n");
    for (int i=0; i<W_ROWS * W_COLS; i++) {
        fprintf(result, "%2d", WW[i]);
    }

    fprintf(result, "\nМакс элемент матрицы W: (%d, %d)\n\n", max_i, max_j);

    fclose(result);
    fclose(source);

    return 0;
}
