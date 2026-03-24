#include <stdio.h>
#include <string.h>

#define MAX_CITIZENS 100
#define MAX_STR 50

/* Структура для хранения данных о гражданине */
typedef struct {
    char last_name[MAX_STR];   /* Фамилия */
    char first_name[MAX_STR];  /* Имя */
    char middle_name[MAX_STR]; /* Отчество */
    char address[MAX_STR];     /* Адрес */
    char profession[MAX_STR];  /* Профессия */
} Citizen;

/* Функция вывода одного гражданина */
void print_citizen(const Citizen *c) {
    printf("  ФИО:      %s %s %s\n", c->last_name, c->first_name, c->middle_name);
    printf("  Адрес:    %s\n", c->address);
    printf("  Профессия:%s\n", c->profession);
    printf("  ----------\n");
}

/* Выборка и подсчёт граждан по профессии */
int find_by_profession(const Citizen citizens[], int count, const char *profession) {
    int found = 0;
    printf("\n>>> Граждане с профессией \"%s\":\n\n", profession);
    for (int i = 0; i < count; i++) {
        if (strcmp(citizens[i].profession, profession) == 0) {
            print_citizen(&citizens[i]);
            found++;
        }
    }
    if (found == 0) {
        printf("  Граждане с такой профессией не найдены.\n");
    } else {
        printf("Итого: %d чел.\n", found);
    }
    return found;
}

/* Вывод всех уникальных профессий и количество граждан каждой */
void count_by_professions(const Citizen citizens[], int count) {
    char professions[MAX_CITIZENS][MAX_STR];
    int  counts[MAX_CITIZENS];
    int  unique = 0;

    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < unique; j++) {
            if (strcmp(professions[j], citizens[i].profession) == 0) {
                counts[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(professions[unique], citizens[i].profession);
            counts[unique] = 1;
            unique++;
        }
    }

    printf("\n=== Статистика по профессиям ===\n");
    for (int i = 0; i < unique; i++) {
        printf("  %-20s: %d чел.\n", professions[i], counts[i]);
    }
}

int main(void) {
    /* Исходный список граждан */
    Citizen citizens[] = {
        {"Иванов",    "Иван",    "Иванович",    "ул. Ленина, 1",    "Программист"},
        {"Петрова",   "Мария",   "Сергеевна",   "ул. Мира, 5",      "Учитель"},
        {"Сидоров",   "Алексей", "Николаевич",  "пр. Победы, 12",   "Программист"},
        {"Козлова",   "Елена",   "Дмитриевна",  "ул. Садовая, 3",   "Врач"},
        {"Новиков",   "Павел",   "Андреевич",   "ул. Заречная, 7",  "Программист"},
        {"Морозова",  "Ольга",   "Владимировна","ул. Лесная, 9",    "Учитель"},
        {"Волков",    "Денис",   "Олегович",    "ул. Центральная, 2","Врач"},
        {"Зайцева",   "Наталья", "Петровна",    "пр. Советский, 14","Бухгалтер"},
    };
    int count = sizeof(citizens) / sizeof(citizens[0]);

    /* Вывод полного списка */
    printf("========== Список граждан ==========\n\n");
    for (int i = 0; i < count; i++) {
        printf("[%d]\n", i + 1);
        print_citizen(&citizens[i]);
    }

    /* Статистика по профессиям */
    count_by_professions(citizens, count);

    /* Выборка по конкретной профессии */
    find_by_profession(citizens, count, "Программист");
    find_by_profession(citizens, count, "Врач");
    find_by_profession(citizens, count, "Учитель");

    return 0;
}