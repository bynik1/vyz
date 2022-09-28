//Перевод числа в строковое представление
#include <stdio.h>
#define N 10

int main()
{
    int a;
    char b[N]={'\0'};
    int k = 0;

    scanf("%d",&a);//32323

    for(int i = 0; a != 0;i++)
    {
        b[i] = a % 10+'0';
        a = a/10;
        k++;
        printf("%c",b[i]);
        printf("%d\n",a);
        if(a == 0)
        {
            break;
        } 
    }
    // while(a != 0){
    //     b[i]=a%N+48;
    //     a=a/N;
    //     k++;
    //     printf("%d",b[i]);
    //     printf("%d\n",a);
    // }

    for(int i = N; i >= 0;i--)
    {
        printf("%c",b[i]);
    }

    printf("\n");
    return 0;
}