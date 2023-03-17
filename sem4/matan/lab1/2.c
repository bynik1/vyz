#include <stdio.h>

int main(void) {
    int rows = 3, cols = 4;
    int i, j;
    FILE *fp;

    fp = fopen("1.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    //fscanf(fp, "%d %d", &rows, &cols);

    printf("%d %d\n", rows, cols);

    int matrix[rows][cols];

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fscanf(fp, "%d", &matrix[i][j]);
        }
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    fclose(fp);
    return 0;
}