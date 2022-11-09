//Проверка строк на совпадение без учета регистра.
#include <stdio.h>
#include <ctype.h>


int main()
{
    char a[4] = {'\0'};
    char b[4] = {'\0'};
    int flag = 1;

    scanf("%s",a);
    scanf("%s",b);

    for(int i = 0;i < 4;i++)
    {
        a[i] = tolower(a[i]);
        b[i] = tolower(b[i]);
        
        if(a[i] != b[i])
        {
            flag = 0;
            printf("Не подходит\n");
            break;
        }
    }   

    if(flag == 1)
    {
        printf("Подходит\n");
    }

    return 0;
}