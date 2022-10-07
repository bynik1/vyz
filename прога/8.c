//Разбиение строки по полям
#include <stdio.h>
#include <string.h>


char **str_tok(char *s, char del, char *arr[])
{
    int i = 0;
    int c = 0;
    for (int x = 0; x < strlen(s); x++)
    {
        arr[i][c] = *(s + x);
        printf("ch - %c\n", *(s + x));
        if (*(s + x + 1) == del)
        {
            i++;
            x++;
            c = 0;
            continue;
        }
        c++;
    }
    return arr;
}


int main(){
    char *s;
    char *arr[25];
    scanf("%s", s);
    char del = '.';
    char *pch = str_tok(s, del, arr);
    
    while (pch != NULL)                         
    {
      printf("%s\n", pch);
      pch = str_tok (NULL, del, arr);
    }
    printf("\n");

    return 0;
}


