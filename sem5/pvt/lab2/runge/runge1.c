#include <stdio.h>
#include <math.h>
#include <time.h>

const double eps = 1E-6;
const int n0 = 10000000;

double func(double x) {
    return x / pow(sin(2 * x), 3);
}

int main()
{
    clock_t start, end;
    double cpu_time_used;

    int n;
    double b = 0.5;
    double a = 0.1;
    double h = (b - a) / n;
    double s = 0.0;

    start = clock();
    for (int i = 0; i < n; i++)
        s += func(a + h * (i + 0.5));
    s *= h;
    end = clock();
    printf("Result Pi: %.12f\n", s * s);
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time used: %f seconds\n", cpu_time_used);
    return 0;
}