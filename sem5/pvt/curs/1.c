#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

// Функция для определения размера части данных для каждого процесса
int get_chunk(int total, int commsize, int rank) {
    int n = total;
    int q = n / commsize;
    if (n % commsize) q++;
    int r = commsize * q - n;
    int chunk = q;
    if (rank >= commsize - r) chunk = q - 1;
    return chunk;
}

int main(int argc, char *argv[]) {
    int n = 3000; // Размер матрицы
    int rank, commsize;

    // Инициализация MPI
    MPI_Init(&argc, &argv);
    double t = MPI_Wtime();
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);

    // Вычисление размера части данных для текущего процесса
    int nrows = get_chunk(n, commsize, rank);
    int *rows = malloc(sizeof(*rows) * nrows); // Номера локальных строк

    // Матрица дополнена столбцом для вектора b
    double *a = malloc(sizeof(*a) * nrows * (n + 1));
    double *x = malloc(sizeof(*x) * n);
    double *tmp = malloc(sizeof(*tmp) * (n + 1));

    // Инициализация как в последовательной версии
    for (int i = 0; i < nrows; i++) {
        rows[i] = rank + commsize * i;
        srand(rows[i] * (n + 1));
        for (int j = 0; j < n; j++)
            a[i * (n + 1) + j] = rand() % 100 + 1;
        // b[i]
        a[i * (n + 1) + n] = rand() % 100 + 1;
    }

    // Прямой ход Гаусса
    int row = 0;
    for (int i = 0; i < n - 1; i++) {
        if (i == rows[row]) {
            MPI_Bcast(&a[row * (n + 1)], n + 1, MPI_DOUBLE, rank, MPI_COMM_WORLD);
            for (int j = 0; j <= n; j++)
                tmp[j] = a[row * (n + 1) + j];
            row++;
        } else {
            MPI_Bcast(tmp, n + 1, MPI_DOUBLE, i % commsize, MPI_COMM_WORLD);
        }

        // Вычитаем принятую строку из уравнений, хранящихся в текущем процессе
        for (int j = row; j < nrows; j++) {
            double scaling = a[j * (n + 1) + i] / tmp[i];
            for (int k = i; k < n + 1; k++)
                a[j * (n + 1) + k] -= scaling * tmp[k];
        }
    }

    // Инициализация неизвестных
    row = 0;
    for (int i = 0; i < n; i++) {
        x[i] = 0;
        if (i == rows[row]) {
            x[i] = a[row * (n + 1) + n];
            row++;
        }
    }

    // Обратный ход Гаусса
    row = nrows - 1;
    for (int i = n - 1; i > 0; i--) {
        if (row >= 0) {
            if (i == rows[row]) {
                x[i] /= a[row * (n + 1) + i];
                MPI_Bcast(&x[i], 1, MPI_DOUBLE, rank, MPI_COMM_WORLD);
                row--;
            } else {
                MPI_Bcast(&x[i], 1, MPI_DOUBLE, i % commsize, MPI_COMM_WORLD);
            }
        } else {
            MPI_Bcast(&x[i], 1, MPI_DOUBLE, i % commsize, MPI_COMM_WORLD);
        }

        for (int j = 0; j <= row; j++)
            x[rows[j]] -= a[j * (n + 1) + i] * x[i];
    }

    // Корректировка x_0 в корневом процессе
    if (rank == 0)
        x[0] /= a[row * (n + 1)];
    MPI_Bcast(x, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Освобождение ресурсов
    free(tmp);
    free(rows);
    free(a);

    // Вывод времени выполнения
    t = MPI_Wtime() - t;
    if (rank == 0) {
        printf("Gaussian Elimination (MPI): n %d, procs %d, time (sec) %.6f\n", n, commsize, t);
    }

    free(x);
    MPI_Finalize();
    return 0;
}
