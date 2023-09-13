#include <stdio.h>

int main() {
    FILE *fp;
    fp = fopen("output.txt", "w"); // открываем файл для записи
    if (fp == NULL) {
        printf("Ошибка открытия файла\n");
        return 1;
    }

    int i;
    for (i = 88; i <= 308; i++) {
        int j;
        for (j = 9; j >= 0; j--) {
            int bit = (i >> j) & 1; // получаем j-й бит числа i
            fprintf(fp, "%d", bit); // записываем бит в файл
        }
        fprintf(fp,"%d",0);
        fprintf(fp, "\n"); // переходим на новую строку
    }

    fclose(fp); // закрываем файл
    return 0;
}