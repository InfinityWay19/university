#include <stdio.h>
#include <math.h>
#include <locale.h>

#define A 0.5
#define B 3.2

double calc_z(int x, double a, double b)
{
    return exp(2 * x) * log(a + x) - pow(b, 3 * x) * log10(b - x);
}

int main()
{
    setlocale(LC_ALL, "RUS");

    int x1, x2;
    double z1, z2;

    printf("Введите x1: ");
    scanf("%d", &x1);

    printf("Введите x2: ");
    scanf("%d", &x2);

    z1 = calc_z(x1, A, B);
    z2 = calc_z(x2, A, B);

    printf("z(x1) = %.6f\n", z1);
    printf("z(x2) = %.6f\n", z2);

    return 0;
}
