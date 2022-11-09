//Копирование строки
#include <stdio.h>

int main()
{
    char a[5]={'\0'};
    char b[5]={'\0'};
    
    scanf("%s",a);

    for(int i=0;i<5;i++)
    {
        b[i]=a[i];
    }
   
    printf("%s",b);

    return 0;
}