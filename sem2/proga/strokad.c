#include <stdio.h>  // Для printf
#include <string.h> // Для strtok
#include <stdlib.h>
int main (void)
{    
   // Массив со строкой для поиска
   char str[] ="fghfydfhdfd";
   char *pstr;
   gets(pstr);
   //printf("%c", pstr[0]);
   for(int i =0;i<strlen(str)-strlen(pstr);i++){
    int count=0;
    for(int u=0;u < strlen(pstr);u++){
        if(pstr[u]== str[i+count]){
            count++;
            if(count == strlen(pstr)){
                break;
            }
        }

    }
   }
   return 0;
}