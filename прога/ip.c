#include <stdio.h>  // Для printf
#include <string.h> // Для strtok
#include <stdlib.h>
int main (void)
{    
   // Массив со строкой для поиска
   char str[17];
   gets(str);
   puts(str);

   // Набор символов, которые должны входить в искомый сегмент
   char *sep=".";
   // Переменная, в которую будут заноситься начальные адреса частей
   // строки str
   char *istr;
   // Выделение первой части строки
   istr = strtok (str,sep);

   // Выделение последующих частей
   while (istr != NULL)
   {
      // Вывод очередной выделенной части
      if(atoi(istr) > 255 || atoi(istr)< 0){
        printf ("Вы ввели неправильный ip адрес\n");
        break;
      }
      // Выделение очередной части строки
      istr = strtok (NULL,sep);
   }

   return 0;
}