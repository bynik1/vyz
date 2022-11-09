#include <stdio.h>
#include <string.h>
#define N 5
#define S 15

char *str_insert(char str_s[], char str_p[], unsigned int pos, char str_o[])
{
    unsigned int len1 = strlen(str_s);
    unsigned int len2 = strlen(str_p);
    unsigned int len = len1 + len2;
    int c = 0, i = 0;
    while (c < len)
    {
        if (c == pos)//дошли до позиции куда надо вставлять
        {
            i = c;
            printf("i1 = %d\n", i);
            for (int x = 0; x < strlen(str_p); x++)
            {
               str_o[c] = *(str_p + x);
               c++;
               printf("c1 = %d\n", c);
            }
        }
        *(str_o + c) = *(str_s + i);
        c++;
        printf("c = %d\n", c);
        i++;
        printf("i = %d\n", i);
    }
    str_o[strlen(str_o)] = '\0';
    return str_o;
}
 
int main() {
   char a[S];
   char b[N];
   scanf("%s",a);
   scanf("%s",b);
   char c[strlen(a)+strlen(b)];
   char *o;
   o = str_insert(a,b,4,c);
   for(int i = 0;i<strlen(a)+strlen(b);i++){
      printf("c[%d] = %c\n", i, o[i]);
   }
   
   return 0;
}