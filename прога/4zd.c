//Вставка/удаление фрагмента строки.
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define N 5
#define S 10

int main()
{
    char a[S] = { 'a','b','c','d','e','f','g','h','i','j' }; //длина строки
    char b[N]; //вставка или удаление
    int k = 0;
    int t = 0;
    int c = 0;//индекс первого вхождения подстроки
    bool flag = 0;

    scanf("%s", b);
    for (int i = 0; i < S; i++) //прохлдим по массиву
    {
        if (a[i] == b[k])
        {
            flag = 1;
            if (k == 0)
            {
                c = i;
            }
            k++;
        }
        else if (k == strlen(b))
        {
            break;
        }
        else if (a[i] != b[k - 1] && k > 0) {
            k = 0;
            i = i - 1;
        }
    }
    printf("c = %d\n", c);

    for (int i = c; i < S; i++)
    {
        if (i < S-strlen(b)) {
            a[i] = a[i + strlen(b)];
            a[i + strlen(b)] = '\0';
        }
        else {
            a[i] = '\0';
        }
    }

    for (int i = 0; i < S; i++)
    {
        printf("%c", a[i]);
    }
    printf("\n");

    return 0;
}
