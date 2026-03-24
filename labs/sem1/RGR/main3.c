#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <math.h>
#include <string.h>

// ===== Настройки экрана =====
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 700

#define GRAPH_WIDTH  100
#define GRAPH_HEIGHT 30

#define MENU_WIDTH 40
#define MENU_ITEMS 7

#define M_PI 3.14159265358979323846

#define RED   "\033[31m"
#define GREEN "\033[33m"
#define RESET "\033[0m"

#define COLOR_F1 "\033[31m"
#define COLOR_F2 "\033[34m"
#define COLOR_AX "\033[90m"
#define RESET    "\033[0m"


// ===== Функции =====
double f(double x) {
    return 2 * cbrt(x * x + 1) - 3 * sin(x) - 5;
}

double F1(double x) {
    return x * cos(x / 2.0);
}

double F2(double x) {
    return cbrt(x) + sqrt(2.0) * exp(-x);
}

// ===== Получение ширины и высоты терминала =====
int getTerminalWidth() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

int getTerminalHeight() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
}

// ===== Очистка экрана =====
void clearScreen() {
    printf("\033[2J\033[H");
}

void getTerminalSize(int *rows, int *cols) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *rows = w.ws_row;
    *cols = w.ws_col;
}

// ===== Вычисление уравнения =====
void solve_equation() {
    double a, b;
    double eps = 0.001;
    double c;
    int iter;

    clearScreen();

    printf("Введите левую границу a: ");
    scanf("%lf", &a);

    printf("Введите правую границу b: ");
    scanf("%lf", &b);

    while (getchar() != '\n'); // очистка буфера

    if (a >= b) {
        printf("\nОшибка: a должно быть меньше b\n");
        printf("Нажмите ENTER для возврата...");
        getchar();
        return;
    }

    if (f(a) * f(b) > 0) {
        printf("\nНа интервале [%.3f, %.3f] нет корня.\n", a, b);
        printf("Нажмите ENTER для возврата...");
        getchar();
        return;
    }

    // =====Метод половинного деления (бисекции) =====

    double a1 = a, b1 = b;
    iter = 0;

    printf("\nМЕТОД ПОЛОВИННОГО ДЕЛЕНИЯ\n");
    printf("-------------------------------------------------------------------------------------\n");
    printf("|  i |     a     |     b     |     c     |    f(a)    |    f(b)    |    f(c)    |\n");
    printf("-------------------------------------------------------------------------------------\n");

    while (fabs(b1 - a1) > eps) {
        c = (a1 + b1) / 2;

        printf("| %2d | %9.4f | %9.4f | %9.4f | %10.5f | %10.5f | %10.5f |\n",
               iter, a1, b1, c, f(a1), f(b1), f(c));

        if (f(a1) * f(c) <= 0)
            b1 = c;
        else
            a1 = c;

        iter++;
    }

    double root_bisect = (a1 + b1) / 2;

    printf("-------------------------------------------------------------------------------------\n");
    printf("Корень (бисекция): x ≈ %.6f\n", root_bisect);
    printf("Итераций: %d\n", iter);

    // ===== Метод хорд (секущих) =====

    double a2 = a, b2 = b;
    double x;
    iter = 0;

    printf("\nМЕТОД ХОРД\n");
    printf("---------------------------------------------------------------\n");
    printf("|  i |     a     |     b     |     x     |    f(x)    |\n");
    printf("---------------------------------------------------------------\n");

    do {
        x = a2 - f(a2) * (b2 - a2) / (f(b2) - f(a2));

        printf("| %2d | %9.4f | %9.4f | %9.4f | %10.5f |\n",
               iter, a2, b2, x, f(x));

        if (f(a2) * f(x) < 0)
            b2 = x;
        else
            a2 = x;

        iter++;

    } while (fabs(f(x)) > eps);

    printf("---------------------------------------------------------------\n");
    printf("Корень (хорды): x ≈ %.6f\n", x);
    printf("Итераций: %d\n", iter);

    printf("\nНажмите ENTER для возврата...");
    getchar();
}

int kbhit() {
    struct timeval tv = {0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

// ===== График ===== 
void drawGraphs() {
    double x_min = 0.0;
    double x_max = 6.0;

    char canvas[GRAPH_HEIGHT][GRAPH_WIDTH];
    int color[GRAPH_HEIGHT][GRAPH_WIDTH];

    // Очистка
    for (int i = 0; i < GRAPH_HEIGHT; i++)
        for (int j = 0; j < GRAPH_WIDTH; j++) {
            canvas[i][j] = ' ';
            color[i][j] = 0;
        }

    // Поиск min/max
    double y_min = 1e9, y_max = -1e9;
    for (int i = 0; i < GRAPH_WIDTH; i++) {
        double x = x_min + (x_max - x_min) * i / (GRAPH_WIDTH - 1);
        double y1 = F1(x);
        double y2 = F2(x);

        if (y1 < y_min) y_min = y1;
        if (y1 > y_max) y_max = y1;
        if (y2 < y_min) y_min = y2;
        if (y2 > y_max) y_max = y2;
    }

    double pad = 0.1 * (y_max - y_min);
    y_min -= pad;
    y_max += pad;

    // Оси
    int x_axis = (int)((y_max) / (y_max - y_min) * (GRAPH_HEIGHT - 1));
    int y_axis = (int)((0 - x_min) / (x_max - x_min) * (GRAPH_WIDTH - 1));

    // Сетка и оси
    for (int i = 0; i < GRAPH_HEIGHT; i++) {
        for (int j = 0; j < GRAPH_WIDTH; j++) {
            if (i == x_axis) canvas[i][j] = '-';
            if (j == y_axis) canvas[i][j] = '|';
            if (i == x_axis && j == y_axis) canvas[i][j] = '+';
        }
    }

    // Деления
    for (int i = 0; i < GRAPH_WIDTH; i += 10)
        if (x_axis >= 0 && x_axis < GRAPH_HEIGHT)
            canvas[x_axis][i] = '+';

    for (int i = 0; i < GRAPH_HEIGHT; i += 5)
        if (y_axis >= 0 && y_axis < GRAPH_WIDTH)
            canvas[i][y_axis] = '+';

    // F1
    for (int i = 0; i < GRAPH_WIDTH; i++) {
        double x = x_min + (x_max - x_min) * i / (GRAPH_WIDTH - 1);
        double y = F1(x);

        int row = (int)((y_max - y) / (y_max - y_min) * (GRAPH_HEIGHT - 1));
        if (row >= 0 && row < GRAPH_HEIGHT) {
            canvas[row][i] = 'o';
            color[row][i] = 1;
        }
    }

    // F2
    for (int i = 0; i < GRAPH_WIDTH; i++) {
        double x = x_min + (x_max - x_min) * i / (GRAPH_WIDTH - 1);
        double y = F2(x);

        int row = (int)((y_max - y) / (y_max - y_min) * (GRAPH_HEIGHT - 1));
        if (row >= 0 && row < GRAPH_HEIGHT) {
            canvas[row][i] = 'o';
            color[row][i] = 2;
        }
    }

    // Вывод
    printf("\033[2J\033[H");
    for (int i = 0; i < GRAPH_HEIGHT; i++) {
        for (int j = 0; j < GRAPH_WIDTH; j++) {
            if (color[i][j] == 1)
                printf(COLOR_F1 "%c" RESET, canvas[i][j]);
            else if (color[i][j] == 2)
                printf(COLOR_F2 "%c" RESET, canvas[i][j]);
            else
                printf(COLOR_AX "%c" RESET, canvas[i][j]);
        }

        // Подписи Y
        if (i % 5 == 0) {
            double y = y_max - (y_max - y_min) * i / (GRAPH_HEIGHT - 1);
            printf("  %.2f", y);
        }

        putchar('\n');
    }

    // Подписи X
    printf("\n");
    for (int i = 0; i < GRAPH_WIDTH; i += 10) {
        double x = x_min + (x_max - x_min) * i / (GRAPH_WIDTH - 1);
        printf("%-10.2f", x);
    }

    printf("\n\n");
    printf(COLOR_F1 "●  y = x·cos(x/2)\n" RESET);
    printf(COLOR_F2 "●  y = ∛x + √2·e^(-x)\n" RESET);
    printf("\nНажмите ENTER...");
    getchar();
}

// ===== Таблица значений функции =====
void table_functions() {
    const int N = 20;
    double a = 0, b = 6.28;
    double x[N], y1[N], y2[N];
    double dx = (b - a) / (N - 1);

    double min1, max1, min2, max2;

    for (int i = 0; i < N; i++) {
        x[i] = a + i * dx;
        y1[i] = sin(x[i]);   // <-- Функция 1
        y2[i] = cos(x[i]);   // <-- Функция 2

        if (i == 0) {
            min1 = max1 = y1[i];
            min2 = max2 = y2[i];
        } else {
            if (y1[i] < min1) min1 = y1[i];
            if (y1[i] > max1) max1 = y1[i];
            if (y2[i] < min2) min2 = y2[i];
            if (y2[i] > max2) max2 = y2[i];
        }
    }

    printf("   x      y1        y2\n");
    for (int i = 0; i < N; i++)
        printf("%6.2f  %8.4f  %8.4f\n", x[i], y1[i], y2[i]);

    printf("\nФункция 1: min = %.4f, max = %.4f\n", min1, max1);
    printf("Функция 2: min = %.4f, max = %.4f\n", min2, max2);

    printf("\nНажмите ENTER для возврата в меню...");
}

// ===== Вычисление интеграла =====
double integrand(double x) {
    return cos(x) / (sin(x) + cos(x));
}

void integrate() {
    double a, b;
    int n = 1000;   // число разбиений (для наглядной таблицы)
    double h;

    clearScreen();

    printf("Введите нижний предел интегрирования a: ");
    scanf("%lf", &a);

    printf("Введите верхний предел интегрирования b: ");
    scanf("%lf", &b);

    while (getchar() != '\n'); // очистка буфера

    if (a >= b) {
        printf("\nОшибка: a должно быть меньше b\n");
        printf("Нажмите ENTER для возврата...");
        getchar();
        return;
    }

    h = (b - a) / n;

    double sum_triangle = 0.0;
    double sum_trap = 0.0;

    // ====== Метод треугольников =====

    printf("\nМЕТОД ТРЕУГОЛЬНИКОВ\n");
    printf("-----------------------------------------\n");
    printf("|  i |    x_i   |   f(x_i)  |    S_i    |\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < n; i++) {
        double x = a + i * h;
        double fx = integrand(x);
        double Si = 0.5 * h * fx;
        sum_triangle += Si;
    }

    printf("Интеграл (метод треугольников) = %.6f\n\n", sum_triangle);

    // ===== Метод трапеций =====

    printf("МЕТОД ТРАПЕЦИЙ\n");

    for (int i = 0; i < n; i++) {
        double x1 = a + i * h;
        double x2 = x1 + h;
        double f1 = integrand(x1);
        double f2 = integrand(x2);
        double Si = h * (f1 + f2) / 2.0;
        sum_trap += Si;
    }

    printf("Интеграл (метод трапеций) = %.6f\n", sum_trap);

    printf("\nНажмите ENTER для возврата в меню...");
    getchar();
}

void six_three() {
    double a = 2.0, b = 4.0;
    int n = 10;

    double x[n], f1[n], f2[n];
    double step = (b - a) / (n - 1);

    double minF1, maxF1, minF2, maxF2;

    printf("-----------------------------------------\n");
    printf("|    x    |     F1(x)    |     F2(x)    |\n");
    printf("-----------------------------------------\n");

    // ===== Первый проход — считаем значения и min/max =====
    for (int i = 0; i < n; i++) {
        x[i] = a + i * step;
        f1[i] = pow(3, -x[i]) / 50.0;
        f2[i] = x[i] * exp(-x[i]) + log(x[i]);

        if (i == 0) {
            minF1 = maxF1 = f1[i];
            minF2 = maxF2 = f2[i];
        } else {
            if (f1[i] < minF1) minF1 = f1[i];
            if (f1[i] > maxF1) maxF1 = f1[i];
            if (f2[i] < minF2) minF2 = f2[i];
            if (f2[i] > maxF2) maxF2 = f2[i];
        }
    }

    // ===== Второй проход — вывод таблицы с цветами =====
    for (int i = 0; i < n; i++) {
        printf("| %7.4f | ", x[i]);

        // F1
        if (f1[i] == minF1)
            printf(RED "%12.8f" RESET " | ", f1[i]);
        else if (f1[i] == maxF1)
            printf(GREEN "%12.8f" RESET " | ", f1[i]);
        else
            printf("%12.8f | ", f1[i]);

        // F2
        if (f2[i] == minF2)
            printf(RED "%12.8f" RESET " |\n", f2[i]);
        else if (f2[i] == maxF2)
            printf(GREEN "%12.8f" RESET " |\n", f2[i]);
        else
            printf("%12.8f |\n", f2[i]);
    }

    printf("-----------------------------------------\n");

    printf("\nПояснение:\n");
    printf(GREEN "Зелёный" RESET " — максимум функции\n");
    printf(RED   "Красный" RESET " — минимум функции\n");
    printf("\nНажмите ENTER для возврата в меню...");
} 

// ===== Анимация спутника =====
void satelliteAnimation() {
    const int W = 60;
    const int H = 30;
    const int cx = W / 2;
    const int cy = H / 2;
    const int R = 10;

    double angle = 0.0;

    while (1) {
        clearScreen();

        char field[H][W];
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                field[i][j] = ' ';

        // Планета
        field[cy][cx] = 'O';

        // Спутник
        int sx = cx + (int)(R * cos(angle));
        int sy = cy + (int)(R * sin(angle));

        if (sx >= 0 && sx < W && sy >= 0 && sy < H)
            field[sy][sx] = '*';

        // Вывод
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++)
                putchar(field[i][j]);
            putchar('\n');
        }

        printf("\nСпутник вращается вокруг планеты");
        printf("\nНажмите ENTER для выхода");

        usleep(60000);
        angle += 0.2;

        // Выход по клавише
        if (kbhit()) {
            char c = getchar();
            if (c == '\n')
                break;
        }
    }
}

// ===== Терминал в raw mode =====
struct termios old_termios;

void enableRawMode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &old_termios);
    raw = old_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

// ===== Перемещение курсора =====
void moveCursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

// ===== Отображение меню =====
void drawMenu(int selected) {
    const char *menu[MENU_ITEMS] = {
        "Об авторе",
        "График функции",
        "Решение уравнения",
        "Вычисление интеграла",
        "Анимация",
        "Таблица значений",
        "Выход"
    };

    int startRow = (SCREEN_HEIGHT / 30);
    int startCol = (SCREEN_WIDTH / 2) / 8 - MENU_WIDTH / 2;

    clearScreen();

    moveCursor(startRow - 2, startCol);
    printf("   ==== ГЛАВНОЕ МЕНЮ ====");

    for (int i = 0; i < MENU_ITEMS; i++) {
        moveCursor(startRow + i * 2, startCol);

        if (i == selected) {
            printf("\033[44;97m > %-30s < \033[0m", menu[i]);
        } else {
            printf("   %-30s   ", menu[i]);
        }
    }

    fflush(stdout);
}

void showContent(const char *title, const char *content) {
    clearScreen();

    int termWidth = getTerminalWidth();
    int blockWidth = 54;   // Фиксированная ширина блока
    int startCol = (termWidth - blockWidth) / 1.9;
    int row = 24;

    // Заголовок
    moveCursor(row++, startCol);
    printf("%*s", (blockWidth + strlen(title)) / 2, title);

    moveCursor(row++, startCol);
    for (int i = 0; i < blockWidth; i++) printf("-");

    row++;

    // Текст
    const char *p = content;
    char line[256];

    while (*p) {
        int len = 0;
        while (p[len] && p[len] != '\n') len++;

        strncpy(line, p, len);
        line[len] = '\0';

        moveCursor(row++, startCol);
        printf("%*s", (blockWidth + len) / 2, line);

        p += len;
        if (*p == '\n') p++;
    }

    row += 3;

    const char *hint = "Нажмите ENTER чтобы вернуться в меню";
    moveCursor(row, startCol);
    printf("%*s", (blockWidth + strlen(hint)) / 2, hint);

    fflush(stdout);
    while (getchar() != '\n');
}

// ===== Main =====
int main() {
    enableRawMode();
    atexit(disableRawMode);

    int selected = 0;
    char ch;

    while (1) {
        drawMenu(selected);
        ch = getchar();

        if (ch == 27) { // ESC 
            getchar();
            ch = getchar();

            if (ch == 'A' && selected > 0) selected--;       // Вверх
            if (ch == 'B' && selected < MENU_ITEMS - 1) selected++; // Вниз
        }

        else if (ch == '\n') { // ENTER
            if (selected == 0) {
                // ===== Содержимое пункта 0 =====
                showContent(
                    "Об авторе",
                    "Эта программа была создана студентом из группы ИВТ-252\n"
                    "Дубовиком Артёмом Олеговичем."
                );
            }
            else if (selected == 1) {
                // ===== Содержимое пункта 1 =====
                clearScreen();
                drawGraphs();
                while (getchar() != '\n');
            }
            else if (selected == 2) {
                // ===== Содержимое пункта 2 =====
                clearScreen();
                solve_equation();
                while (getchar() != '\n');
            }
            else if (selected == 3) {
                // ===== Содержимое пункта 3 =====
                clearScreen();
                integrate();
                while (getchar() != '\n');
            }
            else if (selected == 4) {
                // ===== Содержимое пункта 4 =====
                clearScreen();
                satelliteAnimation();
                while (getchar() != '\n');
            }
            else if (selected == 5) {
                // ===== Содержимое пункта 5 =====
                clearScreen();
                six_three();
                while (getchar() != '\n');
            }
            else if (selected == 6) {
                clearScreen();
                break;
            }
        }
    }

    printf("Goodbye!\n");
    return 0;
}
