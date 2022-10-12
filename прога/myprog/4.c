//Вставка/удаление фрагмента строки.
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


char *insert(char *a,int p, char*b, char* c){
    int i;
    for(i=0;i < p;i++){
        c[i]=a[i];
    }

    for(i = 0;i < strlen(b);i++){
        c[p+i]=b[i];
    }

    for(i = 0;i < strlen(a)- p;i++){
        c[p+strlen(b)+i]=a[p+i];
    }
    c[p+strlen(b)+i]='\0';
 
    return c;
}

char *delete(char *a,char*b, char* c){
    int i, index;
    index = n(a, b);
    //printf("index = %d\n", index);
    for(i = 0;i <index;i++){
        c[i]=a[i];
        // printf("c[%d] = %c \n",i, a[i]);
        // printf("c[%d] = %c \n",i+index, a[i+index+strlen(b)]);
    }
    
    for(i = 0;i <strlen(a)-index;i++){
        c[i+index]=a[i+index+strlen(b)];
    }
    c[i+index] = '\0';
 
    return c;
}

int main(){
    char a[30];
    scanf("%s", a);
    char b[20];
    char *m;
    scanf("%s", b);
    // int p;
    // scanf("%d", &p);
    // char c[strlen(b)+strlen(a)-1];
    // m = insert(a,p,b,c);
    //puts(m);
    char t[strlen(a)-strlen(b)];
    m = delete(a,b,t);
    puts(m);
    
    // for(int i = 0;i<strlen(a)+strlen(b)-1;i++){
    //     printf("%c", m[i]);
    // }
    return 0;
}