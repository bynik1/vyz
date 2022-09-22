//Копирование строки
#include <stdio.h>

int main()
{
    char a[10]={'\0'}; //qwert.....
    char b[4]={'\0'};
    int j=0;

    scanf("%s",a);
    scanf("%s",b);

    for(int i=0;i<10;i++)
    {
        if(a[i]=='\0')
        {
            a[i]=b[j];
            j++;
        }
    }
    printf("%s\n",a);
    return 0;
}