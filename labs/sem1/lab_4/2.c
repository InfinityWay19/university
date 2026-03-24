#include <stdio.h>
#include <locale.h>
#include <math.h>

int main() {
    setlocale(LC_ALL, "Russian");

    double a = 2.0, b = 4.0;
    int  n = 10;
    double x, f1, f2;
    double step = (b - a) / (n - 1);

    printf("-----------------------------------------\n");
    printf("|    x    |     F1(x)    |     F2(x)    |\n");
    printf("-----------------------------------------\n");
    
    int i = 0;
    x = a;
    while (i < n) {
        f1 = pow(3, -x) / 50.0;
        f2 = x * exp(-x) + log(x);
        printf("| %7.4f | %12.8f | %12.8f |\n", x, f1, f2);
        i++;
        x = a + i * step;
    }
    printf("-----------------------------------------\n");
    return 0;
}