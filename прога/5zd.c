#include <stdio.h>
#include <string.h>

#define N 5
#define S 10

int main()
{
    char a[S]={'a','b','c','d','e','f','g','h','i','j'};
    char b[N];
    int flag=0;
    int t=0, index;
    int n=0;
    
    

    scanf("%s",b);

    for(int i=0;i<strlen(b);i++)
    {
        for(int j=n;j<S;j++)
        {
            if(b[i]==a[j])
            {
                t++;
                n=j;
            }
            if(t==strlen(b)){
                flag=1;
                index = j;
                break;
            }
        }
        if(flag==1){
            break;
        }
    }
    if(flag==1){
        printf("строка найдена индекс вхождения = %d\n",index + 1-strlen(b));
    }
    else{
        printf("строка не найдена\n");
    }
    
    return 0;
}