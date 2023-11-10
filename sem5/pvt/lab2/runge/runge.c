#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

double func(double x) {
    return x / pow(sin(2 * x), 3);
}

int main(int argc, char **argv)
{
    int commsize, rank;
    const int n0 = 10000000;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int n = n0, k;
    double sq[2], delta = 1;
    const double eps = 1E-6;
    double b = 0.5;
    double a = 0.1;
    double tmpi, max_tmpi;
    

    double start_time = MPI_Wtime();

    for (k = 0; delta > eps; n *= 2, k ^= 1) {
        int points_per_proc = n / commsize;// это количество точек, которое обрабатывает каждый процесс.
        int lb = rank * points_per_proc; // нижняя граница
        int ub = (rank == commsize - 1) ? (n - 1) : (lb + points_per_proc - 1);//верхняя граница 
        //Если текущий процесс является последним, ub устанавливается в n - 1, что означает, 
        //что последний процесс берет на себя обработку возможно оставшегося неравномерно распределенного числа точек.
        double h = (b - a) / n;//Эта строка кода определяет ширину каждого прямоугольника в методе средних прямоугольников для численного интегрирования функции.
        double s = 0.0;
        for (int i = lb; i <= ub; i++)
            s += func(a + h * (i + 0.5));
        tmpi -= MPI_Wtime();
        MPI_Allreduce(&s, &sq[k], 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);//MPI_Allreduce – это коллективная операция в MPI,
        //которая собирает данные из всех процессов, применяет указанную операцию (в данном случае суммирование), 
        //и затем распространяет результат этой операции обратно всем участвующим процессам.
        tmpi += MPI_Wtime();
        sq[k] *= h;
        if (n > n0)
            delta = fabs(sq[k] - sq[k ^ 1]) / 3.0;
    } /* for */

    double end_time = MPI_Wtime();

    double elapsed_time = end_time - start_time;
    double max_elapsed_time;

    MPI_Reduce(&elapsed_time, &max_elapsed_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);//собираем данные со всех процессов 
    //и выбираем максимальное время
    //MPI_Reduce(&elapsed_time, &tmpi_end, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);//собираем данные со всех процессов 
    MPI_Reduce(&tmpi, &max_tmpi, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);//собираем данные со всех процессов 
    //tmpi = tmpi_end - tmpi;
    
    if (rank == 0) {
        printf("Result Pi: %.12f; Runge rule: EPS %e, n %d\n", sq[k] * sq[k], eps, n / 2);
        printf("Max elapsed time: %f seconds\n", max_elapsed_time);
        printf("max_tmpi=%f\n", (max_tmpi/max_elapsed_time)*100);
    }

    MPI_Finalize();//используется в конце MPI-программы для корректного завершения работы с MPI.
    return 0;
}