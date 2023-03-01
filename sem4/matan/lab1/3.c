#include <stdio.h>

int countLines(char *fileName)
{
    int count = 0;
    char ch;
    FILE *fp;
    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s", fileName);
        return 0;
    }
    while ((ch = fgetc(fp)) != EOF)
    {
        printf("%d ",ch);
        if (ch == '\n')
        {
            count++;
        }
    }
    printf("%d\n", count);
    fclose(fp);
    return count;
}


int main(){
    // FILE *fp;
    // fp = fopen(matrix.txt, "r");

    countLines("matrix.txt");

    return 0;
}