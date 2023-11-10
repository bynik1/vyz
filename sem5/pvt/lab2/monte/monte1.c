#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

const double PI = 3.14159265358979323846;
const int n = 10000000;


/* returns pseudo-random number in the [0, 1] */
double getrand()
{ 
    return (double)rand() / RAND_MAX; 
}

double func(double x, double y) {
    return exp(pow(x + y, 2));
}

int main(int argc, char **argv)
{
    int in = 0;
    double s = 0;
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    for (int i = 0; i < n; i++) {
        double x = getrand() * 1; /* x in [0, pi] */
        double y = getrand() * (1 - x); /* y in [0, sin(x)] */
        if (y <= 1-x) {
            in++;
            s += func(x, y);
        }
    }

    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time used: %f seconds\n", cpu_time_used);
    
    double v = PI * in / n;
    double res = v * s / in;
    printf("Result: %.12f, n %d\n", res, n);
    return 0;
}