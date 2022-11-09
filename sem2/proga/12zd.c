//Сравнение строк по алфавиту
#include <stdio.h>

int main()
{
    char a[5];
    char b[5];
    int flag=1; //1 - полное совпадение 2 - первая строчка выше второй 3 - вторая выше первой

    scanf("%s",a);
    scanf("%s",b);

    for(int i=0;i<5;i++)
    {
        if(a[i]==b[i])
        {
            flag=1;
        }
        else if(a[i]<b[i])
        {
            flag=2;
            break;
        }
        else if(a[i]>b[i])
        {
            flag=3;
            break;
        }
    }

    if(flag==1)
    {
        printf("Подходит");
    }
    if(flag==2)
    {
        printf("вторая строка\n");
    }
    if(flag==3)
    {
        printf("Первая строка\n",);
    }

    return 0;
}