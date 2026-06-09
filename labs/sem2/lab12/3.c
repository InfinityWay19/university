#include <stdio.h>

#define V_ROWS 2
#define V_COLS 3
#define W_ROWS 3
#define W_COLS 2

/* Структура для возврата нескольких значений из функции */
typedef struct {
    int max_i;   /* строка максимального элемента  */
    int max_j;   /* столбец максимального элемента */
    int max_val; /* само максимальное значение     */
} Result;

/* Функция теперь возвращает структуру Result вместо void.
   Массив arr[] по-прежнему заполняется через параметр —
   массивы в C нельзя вернуть по значению. */
Result process_matrix(int rows, int cols, int M[rows][cols], int arr[]) {
    Result res;
    res.max_i   = 0;
    res.max_j   = 0;
    res.max_val = M[0][0];

    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[k++] = M[i][j];
            if (M[i][j] > res.max_val) {
                res.max_val = M[i][j];
                res.max_i   = i;
                res.max_j   = j;
            }
        }
    }
    return res; /* возвращаем структуру целиком */
}

int main() {
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

    /* Результат принимаем в переменную типа Result */
    Result resV = process_matrix(V_ROWS, V_COLS, V, VV);

    printf("Массив VV:\n");
    for (int i = 0; i < V_ROWS * V_COLS; i++)
        printf("%d ", VV[i]);
    printf("\nМаксимум матрицы V: значение %d, индексы (%d, %d)\n",
           resV.max_val, resV.max_i, resV.max_j);

    Result resW = process_matrix(W_ROWS, W_COLS, W, WW);

    printf("\nМассив WW:\n");
    for (int i = 0; i < W_ROWS * W_COLS; i++)
        printf("%d ", WW[i]);
    printf("\nМаксимум матрицы W: значение %d, индексы (%d, %d)\n",
           resW.max_val, resW.max_i, resW.max_j);

    return 0;
}