#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define N 5
#define S 15

int main()
{
    char a[N]; //префикс
    char b[S];//строка
    int flag=0;
    
    scanf("%s", a);
    scanf("%s", b); //строка

    for(int i=0;i<strlen(a);i++)
    {  
        for(int j=0;j<strlen(a);j++)  
        {
            if(b[i]==a[j])
            {
                flag+=1;
            }
        }
    }
    if(flag==strlen(a))
    {
        printf("походит\n");
    }
    else
    {
        printf("не подходит\n");
    }

    return 0;

    //printf("%d %s", a, "fbfttnf");
}