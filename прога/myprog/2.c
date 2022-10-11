//Определение префикса строки, состоящего только из допустимых символов.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void n(char *a, char *b){
    int k = 0;
    for(int i=0; i < strlen(b); i++){
        for(int j=0;j < strlen(a);j++){
            if(b[i] == a[i]){
                k++;
                break;
            }
        }  
    }
    if(k == strlen(b)){
        printf("Подходит\n");
    }
    else{
        printf("не подходит\n");
    }
}

int main(){
    char a[5];
    char b[32];
    scanf("%s", a);
    scanf("%s", b);
    n(a, b);
    return 0;
}