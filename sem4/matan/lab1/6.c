#include <stdio.h>
#include <math.h>

#define N 4

void gauss(double a[N][N+1], double x[N])
{
    int i, j, k, m;
    double factor, temp;

    for (k = 0; k < N; k++)
    {
        m = k;
        for (i = k + 1; i < N; i++)
        {
            if (fabs(a[i][k]) > fabs(a[m][k]))
            {
                m = i;
            }
        }

        if (m != k)
        {
            for (i = 0; i <= N; i++)
            {
                temp = a[k][i];
                a[k][i] = a[m][i];
                a[m][i] = temp;
            }
        }

        for (i = k + 1; i < N; i++)
        {
            factor = a[i][k] / a[k][k];
            for (j = k; j <= N; j++)
            {
                a[i][j] -= factor * a[k][j];
            }
        }
    }

    for (i = N - 1; i >= 0; i--)
    {
        x[i] = a[i][N];
        for (j = i + 1; j < N; j++)
        {
            x[i] -= a[i][j] * x[j];
        }
        x[i] /= a[i][i];
    }
}

int main(void)
{
    double a[N][N+1] = { { 1, -2, 1, 0 },
                         { 2, 2, -1, 3 },
                         { 3, -1, 1, 5 }
                       };
    double b[N][N+1] = { { 3, 4, 10},
                         { 5, -7, 3}
                       };
    double c[N][N+1] = { { 1, 2, -3, -4 },
                         { 2, 5, -4, 0 },
                         { -3, 1, 3, 5 }
                       };
    double d[N][N+1] = { { 1, 2, 3, -2, 6 },
                         { 2, 4, -2, -3, 18 },
                         { 3, 2, -1, 2, 4 },
                         { 2, -3, 2, 1, 8 }
                       };
    double x[N];
    int i, j;

    gauss(d, x);

    printf("The solution is: \n");
    for (i = 0; i < N; i++)
    {
        printf("x%d = %f\n", i, x[i]);
    }
    return 0;
}