#include <stdio.h>
#include <math.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "RUS");

    double a = 2.0, b = 4.0;
    int n = 10;
    double arr[3][n];  
    double step = (b - a) / (n - 1);

    printf("-----------------------------------------\n");
    printf("|    x    |     F1(x)    |     F2(x)    |\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < n; i++) {
        arr[0][i] = a + i * step;                      
        arr[1][i] = pow(3, -arr[0][i]) / 50.0;         
        arr[2][i] = arr[0][i] * exp(-arr[0][i]) + log(arr[0][i]); 

        printf("| %7.4f | %12.8f | %12.8f |\n",
               arr[0][i], arr[1][i], arr[2][i]);
    }

    printf("-----------------------------------------\n");
    return 0;
}
