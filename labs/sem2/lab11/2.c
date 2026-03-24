#include <stdio.h>
#include <string.h>

int main() {
    char input[100];
    char words[10][6]; // максимум 10 слов по 5 букв + \0
    int count = 0;

    printf("Введите последовательность: ");
    fgets(input, sizeof(input), stdin);

    // удаляем точку
    char *dot = strchr(input, '.');
    if (dot != NULL)
        *dot = '\0';

    // разбиваем строку на слова
    char *token = strtok(input, ",");

    while (token != NULL && count < 10) {
        strcpy(words[count], token);
        count++;
        token = strtok(NULL, ",");
    }

    // вывод в обратном порядке
    printf("Результат:\n");

    for (int i = count - 1; i >= 0; i--) {
        printf("%s", words[i]);

        if (i > 0)
            printf(",");
        else
            printf(".");
    }

    printf("\n");

    return 0;
}