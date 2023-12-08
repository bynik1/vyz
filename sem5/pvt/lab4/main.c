#include <math.h>    // Подключение математической библиотеки
#include <mpi.h>     // Подключение библиотеки MPI для параллельных вычислений
#include <stdio.h>   // Подключение стандартной библиотеки ввода/вывода
#include <stdlib.h>  // Подключение библиотеки стандартных утилит
#include <string.h>  // Подключение библиотеки строковых функций

#define EPS 0.001           // Определение константы для точности вычислений
#define PI 3.14159265358979323846  // Определение числа Пи
#define NELEMS(x) (sizeof((x)) / sizeof((x)[0])) // Макрос для вычисления количества элементов в массиве
#define IND(i, j) ((i) * (nx + 2) + (j))  // Макрос для индексации в двумерном массиве

// Функция для расчета размера блока данных для каждого процесса
int get_block_size(int n, int rank, int nprocs) {
    int s = n / nprocs;
    if (n % nprocs > rank) s++;
    return s;
}

// Функция для расчета смещения в данных для каждого процесса
int get_sum_of_prev_blocks(int n, int rank, int nprocs) {
    int rem = n % nprocs;
    return n / nprocs * rank + ((rank >= rem) ? rem : rank);
}

// Главная функция программы
int main(int argc, char *argv[]) {
    int commsize, rank;   // Объявление переменных для размера коммуникатора и ранга процесса
    MPI_Init(&argc, &argv); // Инициализация MPI
    double ttotal = -MPI_Wtime(); // Начало отсчета времени для общего времени выполнения
    MPI_Comm_size(MPI_COMM_WORLD, &commsize); // Получение общего количества процессов
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Получение ранга текущего процесса

    // Создание 2D сетки процессов: commsize = px * py
    MPI_Comm cartcomm; // Объявление коммуникатора для 2D сетки
    int dims[2] = {0, 0}, periodic[2] = {0, 0}; // Массивы для размеров сетки и периодичности
    MPI_Dims_create(commsize, 2, dims); // Создание размеров сетки 2 X 6
    int px = dims[0];  // Количество процессов по оси x
    int py = dims[1];  // Количество процессов по оси y
    // Проверка корректности количества процессов
    if (px < 2 || py < 2) {
        fprintf(stderr,
                "Invalid number of processes %d: px %d and py %d must be "
                "greater than 1\n",
                commsize, px, py);
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
    // Создание картезианской топологии
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periodic, 0, &cartcomm); // cоздания нового коммуникатора, который организует 
    // процессы в двумерную топологию сетки (картографическую топологию) декартову сетку. 
    int coords[2];  // Массив для хранения координат процесса в сетке
    MPI_Cart_coords(cartcomm, rank, 2, coords); // Получение координат текущего процесса
    int rankx = coords[0]; // Координата x текущего процесса
    int ranky = coords[1]; // Координата y текущего процесса

    int rows, cols; // Объявление переменных для строк и столбцов сетки
    // Рассылка аргументов командной строки
    if (rank == 0) {
        rows = (argc > 1) ? atoi(argv[1]) : py * 100;  // Чтение количества строк из аргументов или вычисление по умолчанию
        cols = (argc > 2) ? atoi(argv[2]) : px * 100;  // Чтение количества столбцов из аргументов или вычисление по умолчанию
        // Проверка на достаточность размера сетки
           if (rows < py) {
            fprintf(stderr,
                    "Number of rows %d less then number of py processes %d\n",
                    rows, py);
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);// используется для аварийного завершения работы всех процессов в определенном коммуникаторе. 
        }
        if (cols < px) {
            fprintf(stderr,
                    "Number of cols %d less then number of px processes %d\n",
                    cols, px);
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);// используется для аварийного завершения работы всех процессов в определенном коммуникаторе. 
        }
        int args[2] = {rows, cols}; // Массив для передачи аргументов
        MPI_Bcast(&args, NELEMS(args), MPI_INT, 0, MPI_COMM_WORLD); // Рассылка аргументов всем процессам
    } else {
        int args[2];  // Массив для приема аргументов
        MPI_Bcast(&args, NELEMS(args), MPI_INT, 0, MPI_COMM_WORLD); // Прием аргументов
        rows = args[0]; // Установка количества строк
        cols = args[1]; // Установка количества столбцов
    }

    // Выделение памяти для локальных подсеток с дополнительными ячейками (гало)
    int ny = get_block_size(rows, ranky, py);  // Расчет размера блока по y
    int nx = get_block_size(cols, rankx, px);  // Расчет размера блока по x
    double *local_grid = calloc((ny + 2) * (nx + 2), sizeof(*local_grid)); // Выделение памяти для текущего состояния сетки
    double *local_newgrid = calloc((ny + 2) * (nx + 2), sizeof(*local_newgrid)); // Выделение памяти для нового состояния сетки

    // Заполнение граничных точек:
    // - левая и правая границы заполняются нулями
    // - верхняя граница: u(x, 0) = sin(pi * x)
    // - нижняя граница: u(x, 1) = sin(pi * x) * exp(-pi)
    double dx = 1.0 / (cols - 1.0); // Шаг по x
    int sj = get_sum_of_prev_blocks(cols, rankx, px); // Расчет смещения по x для текущего блока
    if (ranky == 0) {
        // Инициализация верхней границы
        for (int j = 1; j <= nx; j++) {
            double x = dx * (sj + j - 1); // Перевод индекса столбца в координату x в пределах [0, 1]
            int ind = IND(0, j);  // Вычисление индекса в массиве
            local_newgrid[ind] = local_grid[ind] = sin(PI * x); // Заполнение значений верхней границы
        }
    }

    if (ranky == py - 1) {
        // Инициализация нижней границы
        for (int j = 1; j <= nx; j++) {
            double x = dx * (sj + j - 1); // Перевод индекса столбца в координату x в пределах [0, 1]
            int ind = IND(ny + 1, j);  // Вычисление индекса в массиве
            local_newgrid[ind] = local_grid[ind] = sin(PI * x) * exp(-PI); // Заполнение значений нижней границы
        }
    }

    // Определение соседей для обмена граничными данными
    int left, right, top, bottom;
    // Определение соседей для текущего процесса в решетке
    MPI_Cart_shift(cartcomm, 0, 1, &left, &right); // Определение соседей слева и справа
    MPI_Cart_shift(cartcomm, 1, 1, &top, &bottom); // Определение соседей сверху и снизу

    // Создание MPI типов данных для передачи граничных строк и столбцов
    MPI_Datatype col; // MPI тип для столбца
    MPI_Type_vector(ny, 1, nx + 2, MPI_DOUBLE, &col); // Создание векторного типа для столбца
    MPI_Type_commit(&col); // Фиксация типа данных столбца

    MPI_Datatype row; // MPI тип для строки
    MPI_Type_contiguous(nx, MPI_DOUBLE, &row); // Создание непрерывного типа для строки
    MPI_Type_commit(&row); // Фиксация типа данных строки

    MPI_Request reqs[8]; // Массив запросов для неблокирующих операций
    double thalo = 0; // Время на обмен гало (граничными данными)
    double treduce = 0; // Время на операцию MPI_Allreduce
    int niters = 0; // Счетчик итераций

    for (;;) { // Начало бесконечного цикла
        niters++; // Увеличение счетчика итераций

        // Обновление внутренних точек сетки
        for (int i = 1; i <= ny; i++) {
            for (int j = 1; j <= nx; j++) {
                local_newgrid[IND(i, j)] =
                    (local_grid[IND(i - 1, j)] + local_grid[IND(i + 1, j)] +
                    local_grid[IND(i, j - 1)] + local_grid[IND(i, j + 1)]) * 0.25;
            }
        }

        // Проверка условия остановки (сходимость)
        double maxdiff = 0;
        for (int i = 1; i <= ny; i++) {
            for (int j = 1; j <= nx; j++) {
                int ind = IND(i, j);
                maxdiff = fmax(maxdiff, fabs(local_grid[ind] - local_newgrid[ind]));
            }
        }

        // Обмен данными сеток
        double *p = local_grid;
        local_grid = local_newgrid;
        local_newgrid = p;

        // Синхронизация и определение максимальной разницы среди всех процессов
        treduce -= MPI_Wtime();
        MPI_Allreduce(MPI_IN_PLACE, &maxdiff, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);// Объединяет значения всех процессов и распределяет результат обратно по всем процессам
        treduce += MPI_Wtime();
        if (maxdiff < EPS) break; // Выход из цикла, если достигнута сходимость

        // Обмен граничными данными с соседними процессами обмен теневыми ячейками
        thalo -= MPI_Wtime();
        MPI_Irecv(&local_grid[IND(0, 1)], 1, row, top, 0, cartcomm, &reqs[0]);  // Получение данных от верхнего соседа
        MPI_Irecv(&local_grid[IND(ny + 1, 1)], 1, row, bottom, 0, cartcomm, &reqs[1]);  // Получение данных от нижнего соседа
        MPI_Irecv(&local_grid[IND(1, 0)], 1, col, left, 0, cartcomm, &reqs[2]);  // Получение данных от левого соседа
        MPI_Irecv(&local_grid[IND(1, nx + 1)], 1, col, right, 0, cartcomm, &reqs[3]);  // Получение данных от правого соседа
        MPI_Isend(&local_grid[IND(1, 1)], 1, row, top, 0, cartcomm, &reqs[4]);  // Отправка данных верхнему соседу
        MPI_Isend(&local_grid[IND(ny, 1)], 1, row, bottom, 0, cartcomm, &reqs[5]);  // Отправка данных нижнему соседу
        MPI_Isend(&local_grid[IND(1, 1)], 1, col, left, 0, cartcomm, &reqs[6]);  // Отправка данных левому соседу
        MPI_Isend(&local_grid[IND(1, nx)], 1, col, right, 0, cartcomm, &reqs[7]);  // Отправка данных правому соседу
        MPI_Waitall(8, reqs, MPI_STATUS_IGNORE); // Ожидание завершения всех неблокирующих операций
        thalo += MPI_Wtime();
    }  // Конец итераций

    // Освобождение созданных MPI типов данных
    MPI_Type_free(&row);
    MPI_Type_free(&col);

    // Освобождение выделенной памяти
    free(local_newgrid);
    free(local_grid);

    // Завершение измерения общего времени выполнения
    ttotal += MPI_Wtime();

    // Вывод информации о выполнении на нулевом процессе
    if (rank == 0)
        printf("# Heat 2D (mpi): grid: rows %d, cols %d, procs %d (px %d, py %d)\n", rows, cols, commsize, px, py);

    // Получение и вывод информации о процессоре
    int namelen;
    char procname[MPI_MAX_PROCESSOR_NAME];
    MPI_Get_processor_name(procname, &namelen);
    printf("# P %4d (%2d, %2d) on %s: grid ny %d nx %d, total %.6f, mpi %.6f (%.2f) = allred %.6f (%.2f) + halo %.6f (%.2f)\n", rank, rankx, ranky, procname, ny, nx, ttotal, treduce + thalo, (treduce + thalo) / ttotal, treduce, treduce / (treduce + thalo), thalo, thalo / (treduce + thalo));

    // Сбор и агрегирование профилировочных данных на нулевом процессе
    double prof[3] = {ttotal, treduce, thalo};
    if (rank == 0) {
        MPI_Reduce(MPI_IN_PLACE, prof, NELEMS(prof), MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
        printf("# procs %d : grid %d %d : niters %d : total time %.6f : mpi time %.6f : allred %.6f : halo %.6f\n", commsize, rows, cols, niters, prof[0], prof[1] + prof[2], prof[1], prof[2]);
    } else {
        MPI_Reduce(prof, NULL, NELEMS(prof), MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    }

    // Завершение работы с MPI
    MPI_Finalize();
    
    return 0;
}

// mpirun -np 16 ./a.out 10000 10000
