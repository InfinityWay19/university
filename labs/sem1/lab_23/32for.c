#include <stdio.h>
#include <math.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");
    double a=2.0, b=4.0, f1, f2;
    int n=10;

    double dx = fabs((b - a) / (n - 1));

    printf("\n+-------------------------------+\n");
    printf("|    X    |    F1    |    F2    |\n");
    printf("+-------------------------------+\n");

    double x;

    for (x = a; x < b + dx / 2; x += dx) {
        f1 = x*cos(x/2);
        f2 = pow(x, 1/3)+sqrt(x)*exp(-x);
        printf("| %7.4f | %8.4f | %8.4f |\n", (x - a) / dx + 1, x, f1, f2);
    }

    printf("+-------------------------------+\n");

    return 0;
    
}
