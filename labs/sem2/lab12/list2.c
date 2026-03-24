#include <stdio.h>
#include <string.h>

#define MAX_CITIZENS 100
#define MAX_STR      50
#define MAX_FILENAME 256

/* Структура гражданина */
typedef struct {
    char last_name[MAX_STR];
    char first_name[MAX_STR];
    char middle_name[MAX_STR];
    char address[MAX_STR];
    char profession[MAX_STR];
} Citizen;

/* Вывод одного гражданина на экран */
void print_citizen(const Citizen *c) {
    printf("  ФИО:       %s %s %s\n", c->last_name, c->first_name, c->middle_name);
    printf("  Адрес:     %s\n", c->address);
    printf("  Профессия: %s\n", c->profession);
    printf("  ----------\n");
}

/* Запись массива граждан в файл.
   Формат: каждое поле на отдельной строке, записи разделены пустой строкой */
void save_to_file(const char *filename, const Citizen citizens[], int count) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Ошибка: не удалось открыть файл \"%s\" для записи.\n", filename);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(f, "%s\n", citizens[i].last_name);
        fprintf(f, "%s\n", citizens[i].first_name);
        fprintf(f, "%s\n", citizens[i].middle_name);
        fprintf(f, "%s\n", citizens[i].address);
        fprintf(f, "%s\n", citizens[i].profession);
        fprintf(f, "\n"); /* пустая строка — разделитель между записями */
    }

    fclose(f);
    printf("Данные сохранены в файл \"%s\" (%d записей).\n\n", filename, count);
}

/* Чтение граждан из файла.
   Возвращает количество прочитанных записей. */
int load_from_file(const char *filename, Citizen citizens[], int max) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Ошибка: не удалось открыть файл \"%s\" для чтения.\n", filename);
        return 0;
    }

    int count = 0;
    char line[MAX_STR];

    while (count < max) {
        /* Читаем 5 полей подряд */
        if (!fgets(line, MAX_STR, f)) break;
        line[strcspn(line, "\n")] = '\0';
        strncpy(citizens[count].last_name, line, MAX_STR);

        if (!fgets(line, MAX_STR, f)) break;
        line[strcspn(line, "\n")] = '\0';
        strncpy(citizens[count].first_name, line, MAX_STR);

        if (!fgets(line, MAX_STR, f)) break;
        line[strcspn(line, "\n")] = '\0';
        strncpy(citizens[count].middle_name, line, MAX_STR);

        if (!fgets(line, MAX_STR, f)) break;
        line[strcspn(line, "\n")] = '\0';
        strncpy(citizens[count].address, line, MAX_STR);

        if (!fgets(line, MAX_STR, f)) break;
        line[strcspn(line, "\n")] = '\0';
        strncpy(citizens[count].profession, line, MAX_STR);

        fgets(line, MAX_STR, f); /* пропускаем пустую строку-разделитель */
        count++;
    }

    fclose(f);
    printf("Загружено %d записей из файла \"%s\".\n\n", count, filename);
    return count;
}

/* Статистика: количество граждан по каждой профессии */
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
            strncpy(professions[unique], citizens[i].profession, MAX_STR);
            counts[unique] = 1;
            unique++;
        }
    }

    printf("=== Статистика по профессиям ===\n");
    for (int i = 0; i < unique; i++) {
        printf("  %-20s: %d чел.\n", professions[i], counts[i]);
    }
    printf("\n");
}

/* Выборка и подсчёт граждан с заданной профессией */
void find_by_profession(const Citizen citizens[], int count, const char *profession) {
    int found = 0;
    printf(">>> Граждане с профессией \"%s\":\n\n", profession);
    for (int i = 0; i < count; i++) {
        if (strcmp(citizens[i].profession, profession) == 0) {
            print_citizen(&citizens[i]);
            found++;
        }
    }
    if (found == 0)
        printf("  Не найдено.\n");
    else
        printf("Итого: %d чел.\n", found);
    printf("\n");
}

int main(void) {
    Citizen citizens[MAX_CITIZENS];
    int count = 0;
    char filename[MAX_FILENAME];
    char search_profession[MAX_STR];

    /* Запрашиваем имя файла для записи */
    printf("Введите имя файла для сохранения данных: ");
    fgets(filename, MAX_FILENAME, stdin);
    filename[strcspn(filename, "\n")] = '\0';

    /* Исходный список граждан */
    Citizen source[] = {
        {"Иванов",   "Иван",    "Иванович",    "ул. Ленина, 1",     "Программист"},
        {"Петрова",  "Мария",   "Сергеевна",   "ул. Мира, 5",       "Учитель"    },
        {"Сидоров",  "Алексей", "Николаевич",  "пр. Победы, 12",    "Программист"},
        {"Козлова",  "Елена",   "Дмитриевна",  "ул. Садовая, 3",    "Врач"       },
        {"Новиков",  "Павел",   "Андреевич",   "ул. Заречная, 7",   "Программист"},
        {"Морозова", "Ольга",   "Владимировна","ул. Лесная, 9",     "Учитель"    },
        {"Волков",   "Денис",   "Олегович",    "ул. Центральная, 2","Врач"       },
        {"Зайцева",  "Наталья", "Петровна",    "пр. Советский, 14", "Бухгалтер"  },
    };
    int source_count = sizeof(source) / sizeof(source[0]);

    /* Сохраняем исходный список в файл */
    save_to_file(filename, source, source_count);

    /* Читаем граждан из файла */
    count = load_from_file(filename, citizens, MAX_CITIZENS);

    /* Выводим всех загруженных граждан */
    printf("========== Список граждан ==========\n\n");
    for (int i = 0; i < count; i++) {
        printf("[%d]\n", i + 1);
        print_citizen(&citizens[i]);
    }
    printf("\n");

    /* Статистика по профессиям */
    count_by_professions(citizens, count);

    /* Запрашиваем профессию для поиска */
    printf("Введите профессию для поиска: ");
    fgets(search_profession, MAX_STR, stdin);
    search_profession[strcspn(search_profession, "\n")] = '\0';

    find_by_profession(citizens, count, search_profession);

    return 0;
}