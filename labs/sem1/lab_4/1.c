#include <stdio.h>
#include <locale.h>
#include <math.h>

int main() {
    setlocale(LC_ALL, "Russian");

    double a[] = {0.1, 0.7, 1.3};
    double x, z, dx, pi = 3.141592;
    int i;
    
    for (i=0; i<3; i++) {
        printf("\n=== Для а = %.1f ===\n", a[i]);
        dx = a[i] / 4.0;
        for (x = 0.5; x <= 2.0; x += dx) {
            if (x < 1.5) {
                z = exp(cos(x)) - a[i] * pow(sin(pi*x), 2);
            }
            else {
                z = a[i] * pow(x, 2) - cos(a[i] * x);
            }
            printf("x = %.3f\t z = %.5f\n", x, z);
        }
    }
    return 0;
}