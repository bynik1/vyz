//Определение префикса строки, не содержащего недопустимых символов.
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define N 5
#define S 15
int main()
{
    char a[N]; //префикс
    char b[S];//строка
    int flag=1;
    
    scanf("%s", a);
    scanf("%s", b); //строка
    printf("strlen=%d\n", strlen(a));

    for(int i=0;i<strlen(a);i++)
    {  
        for(int j=0;j<strlen(a);j++)  
        {
            if(b[i]==a[j])
            {
                flag=0;
                break; //оптимизация
            }
        }
    }
    if(flag==1)
    {
        printf("походит\n");
    }
    else
    {
        printf("не подходит\n");
    }

    return 0;
}