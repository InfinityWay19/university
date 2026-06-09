#include <stdio.h>
#include "arrays.h"

// Ссылки на переменные, объявленные в main.c
extern int A[SIZE];
extern int B[SIZE];
extern int C[SIZE];

// Циклический сдвиг вправо: каждому элементу присваивается значение соседнего справа,
// последнему — значение первого
void rotate_right(int arr[], int size)
{
    int first = arr[0];

    for (int i = 0; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }

    arr[size - 1] = first;
}

// Печать массива
void print_array(const char *name, int arr[], int size)
{
    printf("%s: ", name);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Печать последних двух элементов
void print_last_two(const char *name, int arr[], int size)
{
    printf("%s: %d %d\n", name, arr[size - 2], arr[size - 1]);
}