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

int solve(double a, double b, double epsilon, int function_number) {
    double c;
    if (f(a, function_number) * f(b, function_number) >= 0) {
        printf("Условие не выполнено\n");
        return 1;
    }

    do {
        c = (a + b) / 2;

        // if (f(c, function_number) == 0.0)
        //     break;

        if (f(c, function_number) * f(a, function_number) < 0)
            b = c;
        else
            a = c;
    } while (fabs(b - a) >= epsilon);

    printf("Корень: %lf\n", c);
    return 0;
}

int main() {
    double a = 0, b = 1, eps = 0.001;
    solve(a, b, eps, 0);
    a = -2, b = -1, eps = 0.001;
    solve(a, b, eps, 1);
    a = -1, b = 0, eps = 0.001;
    solve(a, b, eps, 2);

    

    return 0;
}
