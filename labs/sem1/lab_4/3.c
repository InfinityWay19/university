#include <stdio.h>
#include <locale.h>
#include <math.h>

int main() {
    setlocale(LC_ALL, "Russian");

    double a;
    double x, z, dx, pi = 3.141592;
    int i;
    
    for (a=0.1; a<=1.3; a+=0.6) {
        printf("\n=== Для а = %.1f ===\n", a);
        dx = a / 4.0;
        for (x = 0.5; x <= 2.0; x += dx) {
            if (x < 1.5) {
                z = exp(cos(x)) - a * pow(sin(pi*x), 2);
            }
            else {
                z = a * pow(x, 2) - cos(a * x);
            }
            printf("x = %.3f\t z = %.5f\n", x, z);
        }
    }
    return 0;
}