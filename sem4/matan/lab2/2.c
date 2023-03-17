#include <stdio.h>
#include <math.h>

#define N 3

int main() {
    double A[N][N] = {{1, -2, 1}, {2, 2, -1}, {3, -1, 1}};
    double b[N] = {0, 3, 5};
    double x[N] = {0, 0, 0};
    double x_new[N];
    double eps = 1e-3;
    double norm_r;

    int iter = 0;
    do {
        iter++;
        norm_r = 0.0;

        for (int i = 0; i < N; i++) {
            x_new[i] = b[i] / A[i][i];
            for (int j = 0; j < N; j++) {
                if (i != j) {
                    x_new[i] -= A[i][j] / A[i][i] * x[j];
                }
            }
        }

        for (int i = 0; i < N; i++) {
            norm_r += (x_new[i] - x[i]) * (x_new[i] - x[i]);
            x[i] = x_new[i];
        }
        norm_r = sqrt(norm_r);
    } while (norm_r > eps);

    printf("Solution found in %d iterations:\n", iter);
    for (int i = 0; i < N; i++) {
        printf("x[%d] = %f\n", i, x[i]);
    }

    return 0;
}
