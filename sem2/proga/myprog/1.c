//Задача проверки корректности IP адреса узла.
#include <stdio.h>
#include <stdbool.h>

void ip(char *a){
    int k = 0, sum = 0, flag = 1;
    for(int i=0;i<strlen(a);i++)
    {
        k++;
        if(a[i]=='.' || a[i]=='\0')
        {
            k--; // кол-во чисел перед точкой
            switch(k)
            {
                case 1:
                    sum=(a[i-1]-48);
                    break;
                case 2:
                    sum=(a[i-2]-48)*10 +(a[i-1]-48);
                    break;
                case 3:
                    sum=(a[i-3]-48)*100 +(a[i-2]-48)*10 +(a[i-1]-48);
                    break;
                default:
                    flag=0;
                    break;
            }//smeshlexa
            if(sum>255)
            {
                flag=0;
                break;
            }
            k=0;
        }

    }
    if(flag==1)
    {
        printf("подходит\n");
    }
    else
    {
        printf("не подходит\n");
    }
}

int main()
{
    char a[16];

    scanf("%s",a);

    ip(a);


    return 0;
}
//как ректровать вывод для выовда цвета как изменять цвет в cout
