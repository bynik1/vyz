//хз
#include <stdio.h>
#include <string.h>

void input(int* domen) {
    int i = 0;
    
    while (1) {
        domen[i] = getchar(); 
        if ((('a' <= domen[i]) & (domen[i] <= 'z')) || (('A' <= domen[i]) & (domen[i] <= 'Z')) || ((domen[i] <= 47) & (10 < domen[i]))) {
            domen[i] = '\0';
            continue;
        }
        else if (('0' <= domen[i]) & (domen[i] <= '9')) {
            domen[i] = domen[i] - 48;
        }
        else if (domen[i] == '\n') {
            break;
        }
        i++;
    }
}

int func(int* domen) {
    int i = 0;
    int sum = 0;

    while (1) {
        if (domen[i] != '\n') {
            sum += domen[i];
        }
        else {
            return sum;
        }
    }
}


int main()
{
    int domen[200] = { '\0' };

    input(domen);

    printf("%d", func(domen));

    return 0;
}