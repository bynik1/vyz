#include <stdio.h>
#include <math.h>

void solveQuadratic(double a, double b, double c) {
    double discriminant = b*b - 4*a*c;
    double root1, root2;

    // Проверка наличия реальных корней
    if (discriminant > 0) {
        root1 = (-b + sqrt(discriminant)) / (2*a);
        root2 = (-b - sqrt(discriminant)) / (2*a);
        printf("Roots are: %.2f and %.2f\n", root1, root2);
    } else if (discriminant == 0) {
        root1 = root2 = -b / (2*a);
        printf("Roots are: %.2f and %.2f\n", root1, root2);
    } else {
        printf("No real roots.\n");
    }
}

int main() {
    // Коэффициенты для первого уравнения (n^2)/18 + 2n = 1024*1024
    double a1 = 1.0/18.0, b1 = 2.0, c1 = -1024*1024*1024*18*8;

    // Коэффициенты для второго уравнения n^2 + 2n = 1024*1024
    double a2 = 1.0, b2 = 2.0, c2 = -1024*1024*1024*8;

    printf("Solving the first equation:\n");
    solveQuadratic(a1, b1, c1);

    printf("Solving the second equation:\n");
    solveQuadratic(a2, b2, c2);

    return 0;
}
