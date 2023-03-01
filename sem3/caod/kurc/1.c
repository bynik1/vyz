#include <stdio.h>
int buildBalancedTree(int start, int end) {
    if (start > end) {
        printf("d\n");
        return 0;
    }
    printf("%d  %d  ", start, end);


    int mid = (start + end) / 2;
    // struct node *root = arr[mid];
    printf("%d\n",mid);

    buildBalancedTree(start, mid - 1);
    buildBalancedTree(mid + 1, end);

    return 0;
}

int main(){

    buildBalancedTree(0, 12);
    return 0;
}