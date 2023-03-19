#include <stdio.h>
#include <math.h>

#define N 3 // число уравнений
#define eps 1e-5 // точность

void solve_system(double a[][N], double b[]) {
    double x[N], x_prev[N];
    int i, j, k;
    double norm, sum;
    
    for (i = 0; i < N; i++) {
        x[i] = b[i] / a[i][i];
        x_prev[i] = x[i];
    }
    
    k = 0;
    do {
        k++;
        norm = 0.0;
        for (i = 0; i < N; i++) {
            sum = 0.0;
            for (j = 0; j < N; j++) {
                if (j != i) {
                    sum += a[i][j] * x_prev[j];
                }
            }
            x[i] = (b[i] - sum) / a[i][i];
            norm += fabs(x[i] - x_prev[i]);
            x_prev[i] = x[i];
        }
    } while (norm > eps);
    
    printf("Solution:\n");
    for (i = 0; i < N; i++) {
        printf("x%d = %f\n", i+1, x[i]);
    }
}

int main() {
    double a[N][N] = {{0.0, -2.0, 1.0}, {2.0, 2.0, -1.0}, {3.0, -1.0, 1.0}};
    double b[N] = {0.0, 3.0, 5.0};
    
    solve_system(a, b);
    
    return 0;
}
