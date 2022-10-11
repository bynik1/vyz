//Вставка/удаление фрагмента строки.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char *n(char *a,int p, char*b){

    for(int i=0;i < p;i++){
        b[i]=a[i];
    }

    for(int i=p;i < p;i++){
        b[i]
    }
}

int main(){
    char a[30];
    scanf("%s", a);
    char b[20];
    char m;
    scanf("%s", b);
    int p;
    scanf("%d", &p);
    m = n(a,p,b);
    
    for(int i = 0;i<strlen(a)+strlen(b)-1;i++){
        printf("%c", *m);
    }
    return 0;
}