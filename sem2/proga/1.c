#include <stdio.h>
#include <stdbool.h>

int main()
{
    char a[16];
    int sum=0;
    int k=0;
    int flag=1;

    scanf("%s",a);

    for(int i=0;i<16;i++)
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
            }
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
    return 0;
}