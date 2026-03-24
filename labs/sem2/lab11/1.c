#include <stdio.h>

int main() {
    char name[100];
    printf("Введите ваше имя: ");
    scanf("%99s", name);
    printf("Здарова, %s!\n", name);
}