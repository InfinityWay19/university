#include <stdio.h>
#include <math.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "RUS");
    double a = 2.0, b = 4.0;
    int n = 10;
    double x[n], f1[n], f2[n];
    double step = (b - a) / (n - 1);

    printf("-----------------------------------------\n");
    printf("|    x    |     F1(x)    |     F2(x)    |\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < n; i++) {
        x[i] = a + i * step;
        f1[i] = pow(3, -x[i]) / 50.0;
        f2[i] = x[i] * exp(-x[i]) + log(x[i]);
        printf("| %7.4f | %12.8f | %12.8f |\n", x[i], f1[i], f2[i]);
    }
    printf("-----------------------------------------\n");
    return 0;
}