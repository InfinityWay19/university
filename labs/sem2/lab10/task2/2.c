#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_text 1000
#define max_words 100

int main() {
    FILE *source, *result;
    char text[max_text];

    source = fopen("source.txt", "r");
    result = fopen("result.txt", "w");

    if (source == NULL || result == NULL) {
        printf("Ошибачка\n");
        return 1;
    }

    fgets(text, max_text, source);

    char *words[max_words];
    int count = 0;

    char *token = strtok(text, " \n");
    while (token != NULL) {
        words[count++] = token;
        token = strtok(NULL, " \n");
    }

    for (int shift = 1; shift < count; shift++) {
        for (int i = 0; i < count; i++) {
            int index = (i + shift) % count;
            fprintf(result, "%s ", words[index]);
        }
        fprintf(result, "\n");
    }

    fclose(source);
    fclose(result);

    return 0;
}