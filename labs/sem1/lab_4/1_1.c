#include <stdio.h>
#include <locale.h>
#include <math.h>

int main() {
    setlocale(LC_ALL, "Russian");

//    double a[] = {0.1, 0.7, 1.3};
    double x, z, dx, pi = 3.141592;
    float a=0.1;

    while (a <= 1.31) {
        printf("\n===     Для a = %.1f     ===\n", a);
        dx = a / 4.0;
        x = 0.5;
        while (x <= 2.01) {
            if (x <= 1.5)
                z = exp(cos(x)) - a * pow(sin(pi * x), 2);
            else
                z = a * x * x - cos(a * x);
            printf("x = %.3f\t z = %.5f\n", x, z);
            x += dx;
        }
        a+=0.6;
    }
    return 0;
}