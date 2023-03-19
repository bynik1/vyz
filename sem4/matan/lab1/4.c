#include <stdio.h>
#define ROWS 3
#define COLS 4

int main(void) {
    int matrix[ROWS][COLS];
    int i, j;
    FILE *fp;

    fp = fopen("5.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            fscanf(fp, "%d", &matrix[i][j]);
        }
    }

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    fclose(fp);
    return 0;
}