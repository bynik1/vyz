//Преобразование snake_case в CamelCase
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define N 10

int main()
{
    char a[N];

    scanf("%s",a);

    for(int i=1;i<10;i++)
    {
        if(a[i-1]=='_') //заглавные буквы
        {   
            a[i]=toupper(a[i]);

            for(int j=i-1;j<strlen(a);j++)
            {
                a[j]=a[j+1]; //сдвигаем символ с конца влево
            }      
        }
    }
    printf("%s\n",a);
    return 0;
}
