//Перевод числа в строковое представление
#include <stdio.h>
#define N 10

int main()
{
    int a;
    char b[N]={'\0'};
    int k = 0;

    scanf("%d",&a);//32323

    for(int i = 0; i < N;i++)
    {
        b[i]=a%N+48;
        a=a/N;
        k++;
        printf("%d",b[i]);
        printf("%d\n",a);
        if(a==0)
        {
            break;
        } 
    }

    for(int i = N; i >= 0;i--)
    {
        printf("%c",b[i]);
    }

    printf("\n");
    return 0;
}