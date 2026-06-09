#ifndef ARRAYS_H
#define ARRAYS_H

#define SIZE 6

// Ссылки на массивы, объявленные в main.c
extern int A[SIZE];
extern int B[SIZE];
extern int C[SIZE];

// Подпрограммы
void rotate_right(int arr[], int size);
void print_array(const char *name, int arr[], int size);
void print_last_two(const char *name, int arr[], int size);

#endif