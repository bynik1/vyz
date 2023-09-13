#include <stdio.h>
#include <math.h>

double f(double x, int fun_num) { // функция для решения
    if(fun_num == 0)
        return x * x * x + 4 * x - 3;
    else if(fun_num == 1)
        return exp(x) - x - 2;
    else if(fun_num == 2)
        return pow(x, 3) + 3 * x + 2.2;
}


double f_derivative(double x, int fun_num) { // функция для производной
    if(fun_num == 0)
        return 3 * x * x + 4;
    else if(fun_num == 1)
        return exp(x) - 1;
    else if(fun_num == 2)
        return 2 * pow(x, 2) + 3;
}

double newton_method(double x0, double eps, int max_iter,int fun_num) {
    double x1, fx0, fpx0;
    int iter = 0;

    do {
        fx0 = f(x0, fun_num);
        fpx0 = f_derivative(x0,fun_num);
        x1 = x0 - fx0 / fpx0;
        x0 = x1;
        iter++;
    } while (fabs(fx0) > eps && iter < max_iter);

    return x1;
}

int main() {
    double x0 = 1, eps = 0.001;
    int max_iter = 1000;
    double root = newton_method(x0, eps, max_iter, 0);

    printf("Корень: %.6f\n", root);

    x0 = -1, eps = 0.0001;
    root = newton_method(x0, eps, max_iter, 1);

    printf("Корень: %.6f\n", root);
    x0 = 0, eps = 0.001;
    root = newton_method(x0, eps, max_iter, 2);

    printf("Корень: %.6f\n", root);

    return 0;
}
