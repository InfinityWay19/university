#include <stdio.h>
#include <locale.h>
#include <math.h>

int main() {
    setlocale(LC_ALL, "Russian");

    double x, z, dx, pi = 3.141592;
    float a = 0.1;

    do {
        printf("\n===     Для a = %.1f     ===\n", a);

        dx = a / 4.0;
        x = 0.5;

        do {
            if (x <= 1.5)
                z = exp(cos(x)) - a * pow(sin(pi * x), 2);
            else
                z = a * x * x - cos(a * x);

            printf("x = %.3f\t z = %.5f\n", x, z);

            x += dx;
        } while (x <= 2.01);

        a += 0.6;

    } while (a <= 1.31);

    return 0;
}
