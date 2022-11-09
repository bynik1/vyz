//Разбиение строки по полям
#include <stdio.h>
#include <string.h>


// char str_tok(char *s, char del, char arr[][])
// {
//     int i = 0;
//     int c = 0;
//     printf("*(s+x)=%c\n",*(s+1));
//     for (int x = 0; x < strlen(s); x++)
//     {
//         printf("*(s+x)=%c\n",s[x]);
//         arr[i][c] = s[x];
//         printf("*(s+x)=%c\n",*(s+x));
//         printf("ch - %c\n", *(s + x));
//         if (*(s + x + 1) == del)
//         {
//             i++;
//             x++;
//             c = 0;
//             continue;
//         }
//         c++;
//     }
//     //return arr;
// }


int main(){
    char s[25];
    char arr[10][30];
    scanf("%s", s);
    char del = '.';
    //arr[0][0] = 'c';
    //printf("arr[0][0]= %c",arr);
    //str_tok(s, del, arr);
    int i = 0;
    int c = 0;
    for (int x = 0; x < strlen(s); x++)
    {
        arr[i][c] = s[x];
        //printf("ch - %c\n", *(s + x));
        if (s[x + 1] == del)
        {
            i++;
            x++;
            c = 0;
            continue;
        }
        c++;
    } 
    printf("\n");

    for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 30; j++)
			printf("%c", arr[i][j]);
		printf("\n");
	}

    return 0;
}


