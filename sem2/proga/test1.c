#include <stdio.h>
#include <string.h>
#define N 5
#define S 15

char *delete_str(char *s, char *s_del, char *buf)
{
    int c = 0;
    int i = 0;
    for (int x = 0; *(s + x) != '\0'; x++)
    {
        while (c < strlen(s_del))
        {
            if (*(s + x) != *(s_del + c)){
                break;
            }
            c++;
            x++;
        }
        *(buf + i) = *(s + x);
        i++;
    }
    buf[strlen(buf)] = '\0';
    return buf;
}
int main() {
   char a[S];
   char b[N];
   scanf("%s",a);
   scanf("%s",b);
   char c[strlen(a)-strlen(b)];
   char *o;
   o = delete_str(a,b,c);
   for(int i = 0;i<strlen(a);i++){
      printf("c[%d] = %c\n", i, o[i]);
   }


   return 0;
}