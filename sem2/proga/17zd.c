//Подсчет количества вхождений в строку символов из набора
#include <stdio.h>

int main()
{
    char a[6];
    char b[6]="acdfg";
    int k=0;
    scanf("%s",a);

    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(b[i]==a[j])
            {
                k++;
            }
            
        }
    }
    printf("%d",k);


    return 0;
}