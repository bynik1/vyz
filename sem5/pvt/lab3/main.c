#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <inttypes.h>

void get_chunk(int a, int b, int commsize, int rank, int *lb, int *ub)
{
    /* OpenMP 4.0 spec (Sec. 2.7.1, default schedule for loops)
    * For a team of commsize processes and a sequence of n items, let ceil(n ? commsize) be the integer q
    * that satisfies n = commsize * q - r, with 0 <= r < commsize.
    * Assign q iterations to the first commsize - r procs, and q - 1 iterations to the remaining r processes */
    int n = b - a + 1;
    int q = n / commsize;
    if (n % commsize)
        q++;
    int r = commsize * q - n;
    /* Compute chunk size for the process */
    int chunk = q;
    if (rank >= commsize - r) chunk = q - 1;
    *lb = a; /* Determine start item for the process */
    if (rank > 0) { /* Count sum of previous chunks */
        if (rank <= commsize - r)
            *lb += q * rank;
        else
            *lb += q * (commsize - r) + (q - 1) * (rank - (commsize - r));
    }

    *ub = *lb + chunk - 1;
}
/* dgemv: Compute matrix-vector product c[m] = a[m][n] * b[n] */
void dgemv(double *a, double *b, double *c, int m, int n)
{
    int commsize, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int lb, ub;
    get_chunk(0, m - 1, commsize, rank, &lb, &ub);
    int nrows = ub - lb + 1;
    for (int i = 0; i < nrows; i++) {
        c[lb + i] = 0.0;
        for (int j = 0; j < n; j++)
            c[lb + i] += a[i * n + j] * b[j];
    }
}

int main(int argc, char **argv)
{
    int n, m;
    int commsize, rank;
    n = m = 25000;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double t = MPI_Wtime();
    int lb, ub;
    get_chunk(0, m - 1, commsize, rank, &lb, &ub); // Декомпозиция матрицы на горизонтальные полосы
    int nrows = ub - lb + 1;
    double *a = malloc(sizeof(*a) * nrows * n);
    double *b = malloc(sizeof(*b) * n);
    double *c = malloc(sizeof(*c) * m);
    // Each process initialize their arrays
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < n; j++)
            a[i * n + j] = lb + i + 1;
    }

    for (int j = 0; j < n; j++)
        b[j] = j + 1;
    dgemv(a, b, c, m, n);
    t = MPI_Wtime() - t;

    if (rank == 0) {
    // Validation
    for (int i = 0; i < m; i++) {
        double r = (i + 1) * (n / 2.0 + pow(n, 2) / 2.0);
        if (fabs(c[i] - r) > 1E-6) {
        fprintf(stderr, "Validation failed: elem %d = %f (real value %f)\n", i, c[i], r);
        break;
        }
    }

        printf("DGEMV: matrix-vector product (c[m] = a[m, n] * b[n]; m = %d, n = %d)\n", m, n);
        printf("Memory used: %" PRIu64 " MiB\n", (uint64_t)(((double)m * n + m + n) * sizeof(double)) >> 20);
        double gflop = 2.0 * m * n * 1E-9;
        printf("Elapsed time (%d procs): %.6f sec.\n", commsize, t);
        printf("Performance: %.2f GFLOPS\n", gflop / t);
    }

    free(a);
    free(b);
    free(c);
    MPI_Finalize();
    return 0;

}