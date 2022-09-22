//Преобразование snake_case в CamelCase
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    char a[10];

    scanf("%s",a);

    for(int i=1;i<10;i++)
    {
        if(a[i-1]=='_') //заглавные буквы
        {   
            a[i]=toupper(a[i]);

            for(int j=i-1;j<10;j++)
            {
                a[j]=a[j+1]; //сдвигаем символ с конца вправо
            }      
        }
    }
    printf("%s\n",a);
    return 0;
}
