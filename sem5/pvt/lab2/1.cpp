#include <iostream>
#include <cmath>
#include <mpi.h>

double f(double x) {
    return x / pow(sin(2 * x), 3);
}

double integrate(int num_intervals, double a, double b) {
    double h = (b - a) / num_intervals;
    double sum = 0.0;
    for (int i = 0; i < num_intervals; ++i) {
        double x = a + (i + 0.5) * h;
        sum += f(x);
    }
    return sum * h;
}

int main(int argc, char *argv[]) {
    int rank, size, n = 1;
    double a = 0.1, b = 0.5;
    double local_sum, total_sum;
    double epsilon = 1e-6, integral, prev_integral;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    start_time = MPI_Wtime();

    do {
        prev_integral = integral;
        n *= 2;
        double h = (b - a) / (n * size);
        double local_a = a + rank * n * h;
        double local_b = local_a + n * h;
        local_sum = integrate(n, local_a, local_b);

        MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        if (rank == 0) {
            integral = total_sum;
            if (n > 1) {
                if (std::abs(integral - prev_integral) < epsilon) break;
            }
        }

        MPI_Bcast(&integral, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    } while (true);

    if (rank == 0) {
        std::cout << "Integral: " << integral << std::endl;
    }

    MPI_Finalize();
    return 0;
}
