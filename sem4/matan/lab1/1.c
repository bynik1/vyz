#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define N 3

void gauss(double a[N][N+1], double x[N])
{
    int i, j, k, m;
    double factor, temp;

    for (k = 0; k < N; k++)
    {
        m = k;
        for (i = k + 1; i < N; i++)//нахождения большего числа в столбце
        {
            if (fabs(a[i][k]) > fabs(a[m][k]))
            {
                m = i;
            }
        }

        if (m != k)//если число не находится на главной диагонале мы менем строчки местами
        {
            for (i = 0; i <= N; i++)
            {
                temp = a[k][i];
                a[k][i] = a[m][i];
                a[m][i] = temp;
            }
        }

        for (i = k + 1; i < N; i++)//зануление текущего столбца
        {
            factor = a[i][k] / a[k][k];
            for (j = k; j <= N; j++)
            {
                a[i][j] -= factor * a[k][j];
            }
        }
    }

    for (i = N - 1; i >= 0; i--)//вычесление x
    {
        x[i] = a[i][N];
        for (j = i + 1; j < N; j++)
        {
            x[i] -= a[i][j] * x[j];
        }
        x[i] /= a[i][i];
    }
}


int count_numbers_in_line(char *line) {
  int count = 0;
  int in_number = 0;

  for (int i = 0; line[i]; i++) {
    if (isdigit(line[i]) && !in_number) {
      count++;
      in_number = 1;
    } else if (!isdigit(line[i])) {
      in_number = 0;
    }
  }

  return count;
}

int main(int argc, char *argv[])
{
    // double a[N][N+1] = { { 10, 2, 1, 27 },
    //                      { 3, 20, 4, 73 },
    //                      { 1, 4, 20, 75 }
    //                    };
    int i, j;
    int rows = 0, cols = 0;
    FILE *file = fopen(argv[1], "r");

  char line[1024];

  while (fgets(line, sizeof line, file)) {
    cols = count_numbers_in_line(line);
    //printf("Line has %d numbers\n", cols);
    rows += 1;
  }
    printf("%d %d\n", cols, rows);
    double a[rows][cols];
    double x[N];

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fscanf(file, "%lf", &a[i][j]);
        }
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%lf ", a[i][j]);
        }
        printf("\n");
    }

    gauss(a, x);

    printf("The solution is: \n");
    for (i = 0; i < rows; i++)
    {
        printf("x%d = %lf\n", i, x[i]);
    }

    fclose(file);

    return 0;
}