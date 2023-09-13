#include <stdio.h>
#include <math.h>

double f(double x) { // функция для решения
    return x * x * x + 4 * x - 3;
}

double f1(double x) { // функция для решения
    return exp(x) - x - 2;
}

double f2(double x) { // функция для решения
    return pow(x, 3) + 3 * x + 2.2;
}


void metod_hord(double x0, double x1, double epsilon, int max_iterations, int function_number) {
    int iteration = 0;
    double dx, delta_x;

    do {
        iteration++;
        if(function_number == 0)
            delta_x = -(f(x1) * (x1 - x0)) / (f(x1) - f(x0));
        else if(function_number == 1)
            delta_x = -(f1(x1) * (x1 - x0)) / (f1(x1) - f1(x0));
            //delta_x = (f1(x1) * x0 - f1(x0)*x1) / (f1(x1) - f1(x0));
        else if(function_number == 2)
            delta_x = -(f2(x1) * (x1 - x0)) / (f2(x1) - f2(x0));
        x0 = x1;
        x1 += delta_x;
        dx = fabs(delta_x);
    } while (dx > epsilon && iteration < max_iterations);

    if (iteration == max_iterations) {
        printf("Решение не найдено за %d итераций\n", max_iterations);
    } else {
        printf("Решение: x=%lf, найдено за %d итераций\n", x1, iteration);
    }
}

int main() {
    double x0, x1, epsilon;
    int max_iterations = 100;

    // printf("Введите начальное приближение x0, x1: ");
    // scanf("%lf %lf", &x0, &x1);

    // printf("Введите требуемую точность: ");
    // scanf("%lf", &epsilon);

    // printf("Введите максимальное количество итераций: ");
    // scanf("%d", &max_iterations);

    // solve(x0, x1, epsilon, max_iterations);
    epsilon = 0.001;
    x0 = 0;
    x1 = 1;
    metod_hord(x0, x1, epsilon, max_iterations, 0);
    epsilon = 0.0001;
    x0 = -2;
    x1 = -1;
    metod_hord(x0, x1, epsilon, max_iterations, 1);
    epsilon = 0.001;
    x0 = -1;
    x1 = 0;
    metod_hord(x0, x1, epsilon, max_iterations, 2);

    return 0;
}
