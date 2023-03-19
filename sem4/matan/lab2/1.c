#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

int cols, rows = 0;

double max(double a, double b) {
    return (a > b) ? a : b;
}

double e(double x[rows], double y[rows]){
    double max1 = max(x[0], y[0]);

    for(int i = 1;i < rows;i++){
        max1 = (max1, max(x[i], y[i]));
    }

    return max1;
}

double * multiply_matrices(double mat1[], double mat2[rows][cols]) {
    // Проверяем, что можно перемножить матрицы
    printf("%d %d\n", cols, rows);
    double res1[rows];
    int col1 = 1, col2 = cols - 1;
    // if (col1 != rows) {
    //     printf("Невозможно перемножить матрицы!\n");
    //     return NULL;
    // }
    
    // Инициализируем результирующую матрицу нулями
    for (int i = 0; i < rows; i++) {
        res1[i] = 0;
    }

    // for (int i = 0; i < rows; i++) {
    //     printf("res[%d] = %lf ",i, res[i]);
    //     printf("\n");
    // }

    
    // Перемножаем матрицы
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < col2; j++) {
            res1[i] += mat1[j] * mat2[i][j];
            printf("%lf[%d] = %lf[%d] * %lf[%d][%d]\n",mat1[j] * mat2[i][j],i,mat1[j], j, mat2[i][j], i, j);
            printf("res1 = %lf\n\n", res1[i]);
        }
    }
    
    for (int i = 0; i < rows; i++) {
        mat1[i] = res1[i];
        printf("res[%d] = %lf\n", i, mat1[i]);
    }

    return mat1;
}


void g(double res[], double c[rows][cols]) {
    // здесь вставляем вектор-функцию g(x)
    multiply_matrices(res, c);

    for (int i = 0; i < rows; i++) {
        printf("res[%d] = %lf ", i, res[i]);
        printf("\n");
    }
    double result[rows];

    for (int i = 0; i < rows; i++) {
        printf("%lf = %lf - %lf\n\n",c[i][cols-1] - res[i],c[i][cols-1],res[i]);
        result[i] = c[i][cols-1] - res[i];
    }

    for (int i = 0; i < rows; i++) {
        res[i] = result[i];
        printf("res[%d] = %lf\n", i, res[i]);
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

int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");

    char line[1024];

    while (fgets(line, sizeof line, file)) {
        cols = count_numbers_in_line(line);
        //printf("Line has %d numbers\n", cols);
        rows += 1;
    }

    // double x[rows];
    // double x0[rows]; // из чего всегда вычитают
    double eps = 0.001; // заданная точность
    double a[rows][cols];
    double xi[rows]; // текущее приближение
    double xi_prev[rows]; // предыдущее приближение
    int o = 0; // номер итерации
    fclose(file);
    file = fopen(argv[1], "r");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(file, "%lf", &a[i][j]);
        }
    }

    // for (int i = 0; i < rows; i++) {
    //     for (int j = 0; j < cols; j++) {
    //         printf("%lf ", a[i][j]);
    //     }
    //     printf("\n");
    // }


    //printf("cols = %d rows = %d\n", cols, rows);
    //сдеали на главной диагонали еденицы, а затем занулили
    for(int i = 0;i < rows;i++){
        double del = a[i][i];
        //printf("del = %lf\n", del);
        for(int j = 0;j < cols;j++){
            a[i][j] /= del;
        }    
        a[i][i] -= 1;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%lf ", a[i][j]);
        }
        printf("\n");
    }


    for (int i = 0; i < rows; i++) {
        printf("a[%d][%d] = %lf\n", i, cols - 1, a[i][cols-1]);
        xi[i] = a[i][cols-1];
    }

    // for (int i = 0; i < rows; i++) {
    //     printf("%lf ", xi[i]);
    //     printf("\n");
    // }

    

    do {
        for (int j = 0; j < rows; j++) {
            xi_prev[j] = xi[j];
        }

        g(xi, a);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%lf ", a[i][j]);
            }
            printf("\n");
        }
        o++;
    } while (e(xi, xi_prev)> eps); // условие остановки e(xi, xi_prev)> eps  || o < 10

    printf("Решение: (");
    for (int j = 0; j < rows-1; j++) {
        printf("%f, ", xi[j]);
    }
    printf("%f)\n", xi[rows-1]);

    return 0;
}
