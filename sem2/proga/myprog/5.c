//Поиск подстроки в строке.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int n(char *a,char *b){
    int flag = 0,u;
    int index;
    for(int i=0;i < strlen(a);i++){
        u= 0;
        for(int j=0;j < strlen(b);j++){
            if(flag == strlen(b)){
                index=i-strlen(b);
                break;
            }
            else if(b[j]!=a[i+u]){
                flag = 0;
                break;
            }else if(b[j]==a[i+u]){
                u++;
                flag++;
            }
        }
        if(flag == strlen(b)){
            index=i;
            break;
        }
    }
    return index;
}

int main(){
    char a[30];
    char b[10];
    scanf("%s", a);
    scanf("%s", b);
    int m;
    m = n(a, b);
    printf("%d\n", m);
    return 0;
}