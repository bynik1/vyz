//Преобразование CamelCase в snake_case
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define N 15
int main()
{
    char a[N];

    scanf("%s",a);//dDasDas

    for(int i=0;i<strlen(a);i++)
    {
        if(a[i] == toupper(a[i])) //заглавные буквы
        {   
            a[i]=tolower(a[i]);

            for(int j = strlen(a);j>i;j--)
            {
                a[j]=a[j-1]; //сдвигаем символ с конца вправо
            }

            a[i]='_';
        }
    }
    printf("%s\n",a);
    return 0;
}


