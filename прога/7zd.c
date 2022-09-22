//Перевод символов строки в число.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define N 5

int main()
{
    int a=0;
    char b[N];
    int i = 0;
    scanf("%s",b);

    printf("strlen(b) = %d\n", strlen(b));
    while (i < strlen(b))
    {
        printf("i = %d\n",i);
        a += (b[i] - 48)*(pow(10, strlen(b) - i - 1));
        i++;
    }

    printf("%d\n",a);

    return 0;
}
