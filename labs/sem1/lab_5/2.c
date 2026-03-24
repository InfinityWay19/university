#include <stdio.h>
#include <math.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");
    double r;
    const double PI = 3.141592;

    printf("Введите радиус (0 для завершения): ");
    scanf("%lf", &r);

    do
    {
        double L = 2 * PI * r;
        double S = PI * r * r;
        double V = (4.0 / 3.0) * PI * r * r * r;

        printf("\nРадиус: %.3f\n", r);
        printf("Длина окружности: %.5f\n", L);
        printf("Площадь круга:     %.5f\n", S);
        printf("Объем шара:        %.5f\n\n", V);

        printf("Введите следующий радиус (0 для завершения): ");
        scanf("%lf", &r);
    }  while (r != 0);

    printf("\nРабота завершена.\n");

    return 0;
}