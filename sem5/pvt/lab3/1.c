#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>

enum { m = 10000, n = 10000 };
/* dgemv: Compute matrix-vector product c[m] = a[m][n] * b[n] */
void dgemv(double *a, double *b, double *c, int m, int n)
{
    for (int i = 0; i < m; i++) {
        c[i] = 0.0;
        for (int j = 0; j < n; j++)
            c[i] += a[i * n + j] * b[j];
    }
}

int main(int argc, char **argv)
{
    int n, m;
    n = m = 25000;

    printf("Memory used: %" PRIu64 " MiB\n", (uint64_t)(((double)m * n + m + n) * sizeof(double)) >> 20);
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    double *a, *b, *c;
    a = malloc(sizeof(*a) * m * n);
    b = malloc(sizeof(*b) * n);
    c = malloc(sizeof(*c) * m);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            a[i * n + j] = i + 1;
    }

    for (int j = 0; j < n; j++)
        b[j] = j + 1;

    dgemv(a, b, c, m, n);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time used: %f seconds\n", cpu_time_used);
    // Validation
    for (int i = 0; i < m; i++) {
        double r = (i + 1) * (n / 2.0 + pow(n, 2) / 2.0);
        if (fabs(c[i] - r) > 1E-6) {
            fprintf(stderr, "Validation failed: elem %d = %f (real value %f)\n", i, c[i], r); break;
        }
    }

    double gflop = 2.0 * m * n * 1E-9;
    printf("Elapsed time (serial): %.6f sec.\n", cpu_time_used);
    printf("Performance: %.2f GFLOPS\n", gflop / cpu_time_used);
    free(a); free(b); free(c);
    return 0;
}