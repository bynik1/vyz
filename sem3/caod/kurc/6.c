#include <stdio.h>
#include <stdlib.h>

#define ALPHA 0.7

struct node {
    int size;
    int value;
    struct node* left;
    struct node* right;
};

struct node* createNode(int value) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->size = 1;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int size(struct node* root) {
    return root == NULL ? 0 : size(root->left) + 1 + size(root->right);
}

void updateSize(struct node *node) {
    node->size = 1 + size(node->left) + size(node->right);
}

int isUnbalanced(struct node *node) {
    int size_left = size(node->left);
    int size_right = size(node->right);

    int size_node = size_left + size_right + 1;//размер родителя

    return (size_left > size_node * ALPHA || size_right > size_node * ALPHA);
}

struct node* insert(struct node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->value) {
        root->left = insert(root->left, value);
    } else if(value > root->value) {
        root->right = insert(root->right, value);
    }else{
        printf("такое число есть в структуре");
        return NULL;
    }

    int leftSize = size(root->left);
    int rightSize = size(root->right);
    updateSize(root);

    // if (isUnbalanced(root)) {
    //     int arr[leftSize];
    //     int index = 0;
    //     void storeNodes(struct node* node) {
    //         if (node == NULL) {
    //             return;
    //         }
    //         storeNodes(node->left);
    //         arr[index++] = node->data;
    //         storeNodes(node->right);
    //     }
    //     storeNodes(root);
    //     return buildTree(arr, 0, leftSize - 1);
    // }
    
    return root;
}


// void inOrderTraversal(struct node* root) {
//     if (root != NULL) {
//         inOrderTraversal(root->left);
//         printf("%d \n", root->value);
//         inOrderTraversal(root->right);
//     }
// }

// struct node* buildTree(int arr[], int start, int end) {
//     if (start > end) {
//         return NULL;
//     }
//     int mid = (start + end) / 2;
//     struct node* root = createNode(arr[mid]);
//     root->left = buildTree(arr, start, mid - 1);
//     root->right = buildTree(arr, mid + 1, end);
//     return root;
// }

// struct node* insert(struct node* root, int data) {
//     if (root == NULL) {
//         printf("5\n");
//         return createNode(data);
//     }

//     if (data < root->data) {
//         root->left = insert(root->left, data);
//     } else {
//         root->right = insert(root->right, data);
//     }
//     int leftSize = size(root->left);
//     int rightSize = size(root->right);
//     if (leftSize > ALPHA * (leftSize + rightSize)) {
//         int arr[leftSize];
//         int index = 0;
//         void storeNodes(struct node* node) {
//             if (node == NULL) {
//                 return;
//             }
//             storeNodes(node->left);
//             arr[index++] = node->data;
//             storeNodes(node->right);
//         }
//         storeNodes(root);
//         return buildTree(arr, 0, leftSize - 1);
//     }
//     if (rightSize > ALPHA * (leftSize + rightSize)) {
//         int arr[rightSize];
//         int index = 0;
//         void storeNodes(struct node* node) {
//             if (node == NULL) {
//                 return;
//             }
//             storeNodes(node->left);
//             arr[index++] = node->data;
//             storeNodes(node->right);
//         }
//         storeNodes(root);
//         return buildTree(arr, 0, rightSize - 1);
//     }
//     return root;
// }


int main() {
    struct node* root = NULL;
    root = createNode(5);
    // printf("%d\n", root->value);
    // printf("%d\n", size(root));
    // printf("%d\n", root->value);
    // printf("%d\n", size(root));

    root = insert(root, 4);
    printf("value = %d\n", root->left->value);
    printf("size = %d\n", size(root));
    //printf("value = %d\n", root->right->value);

    root = insert(root, 3);
    printf("value = %d\n", root->left->left->value);
    printf("size = %d\n", size(root));

    root = insert(root, 2);
    printf("value = %d\n", root->left->left->left->value);
    printf("size = %d\n", size(root));

    root = insert(root, 7);
    printf("value = %d\n", root->right->value);
    printf("size = %d\n", size(root));





    // root = insert(root, 5);
    // printf("%p", root);
    // root = insert(root, 4);
    // printf("%p", root);

    // root = insert(root, 3);
    // printf("%p", root);

    // root = insert(root, 2);
    // printf("%p", root);

    // root = insert(root, 7);
    // root = insert(root, 6);
    // root = insert(root, 8);
    // sgt_print(root, 0);

    // inOrderTraversal(root);

    // sgt_print(root, 0);
    return 0;
}
