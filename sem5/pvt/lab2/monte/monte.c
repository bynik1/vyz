#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>





double getrand()
{ 
    return (double)rand() / RAND_MAX; 
}

double func(double x, double y) {
    return exp(pow(x + y, 2));
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, commsize;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);

    const double PI = 3.14159265358979323846;
    const int n = 10000000;

    double start_time = MPI_Wtime();

    srand(rank);//Инициализируем генератор целочисленным значением, уникальным для каждого процесса – его номером иначе сумма вычесленая каждым процессором будет одинакова
    int in = 0;
    double s = 0;

    for (int i = rank; i < n; i += commsize) {
        double x = getrand() * 1; /* x in [0, 1] */
        double y = getrand() * (1 - x); /* y in [0, 1-x] */
        if (y <= (1-x)) {
            in++;
            s += func(x, y);
        }
    }

    int gin = 0;
    MPI_Reduce(&in, &gin, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);//С помощью MPI_Reduce собираются результаты: общее количество точек внутри области gin и сумма значений функции gsum.
    double gsum = 0.0;
    MPI_Reduce(&s, &gsum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    //После выполнения этих операций, на процессе с рангом 0 будет доступно 
    //общее количество точек gin, попавших в область, 
    //и сумма значений функции gsum по этим точкам, что позволит вычислить итоговое значение интеграла.
    double end_time = MPI_Wtime();

    double elapsed_time = end_time - start_time;
    double max_elapsed_time;

    MPI_Reduce(&elapsed_time, &max_elapsed_time, 1, MPI_DOUBLE, MPI_MAX, 0,
               MPI_COMM_WORLD);

    if (rank == 0) {
        double v = PI * gin / n;
        double res = v * gsum / gin;
        printf("Result: %.12f, n %d\n", res, n);
        printf("Max elapsed time: %f seconds\n", max_elapsed_time);
    }

    MPI_Finalize();

    return 0;
}