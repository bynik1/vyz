#include <stdio.h>


char* strtok(char*s, char*del)
{
    char *firsttok = s;
    char *endtok;
    char* s1 = s;
    if (firsttok == NULL)
        return NULL;
    for(int j=0;*s1 != "\0";j++){
        printf("%d = %c\n", j, *(s1++));
        if(*s1==*del){
            s=s1;
            return firsttok;
        }
    }
    return firsttok;
}


int main(){
    char s[25];
    scanf("%s", s);
    char *pch = strtok(s, ".");
    
    while (pch != NULL)                         
    {
      printf("%s", pch);
      pch = strtok (NULL, ".");
    }
    printf("\n");

    return 0;
}


