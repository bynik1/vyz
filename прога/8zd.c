//Конкатенация строк
#include <stdio.h>
#include <string.h>
#define N 5
#define S 15

int main()
{
    char a[S];
    char b[N];
    char c[N];

    scanf("%s",b);
    scanf("%s",c);
    
    for(int i=0;i<strlen(b);i++)
    {
        a[i]=b[i];
    }

    for(int j = 0;j <strlen(c);j++){
        printf("%d\n",j+strlen(b));
        a[j+strlen(b)]=c[j];
    }
    
    a[strlen(b)+strlen(c)]= "\0";


    printf("%s\n",a);

    return 0;
}  