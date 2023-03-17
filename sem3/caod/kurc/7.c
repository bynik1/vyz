#include <stdio.h>
#include <stdlib.h>

#define ALPHA 0.75 // balancing factor

// Node struct
typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

// Tree struct
typedef struct {
    Node *root;
    int size;
} Tree;

// Функция для создания нового узла
Node *new_node(int key) {
    Node *node = malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// Функция для вычисления размера поддерева
int size(Node *node) {
    if (node == NULL) {
        return 0;
    } else {
        return 1 + size(node->left) + size(node->right);
    }
}

// Функция для формирования сбалансированного дерева из отсортированного массива
Node *build_bst(int *arr, int start, int end) {
    if (start > end) {
        return NULL;
    }

    int mid = (start + end) / 2;
    Node *node = new_node(arr[mid]);
    node->left = build_bst(arr, start, mid - 1);
    node->right = build_bst(arr, mid + 1, end);

    return node;
}

// Сохраняет ключи узлов дерева при обходе по порядку в массиве
void addArr(Node *node, int *arr, int *i){
        if (node != NULL) {
            addArr(node->left, arr, i);
            arr[(*i)++] = node->key;
            addArr(node->right, arr, i);
        }
}


// Функция для перестройки дерева с корнем в данном узле
Node * rebuild(Node **node) {
    int n = size(*node);
    int *arr = (int*) malloc(n * sizeof(int));
    int i = 0;
    
    addArr(*node, arr, &i);
    *node = build_bst(arr, 0, n - 1);
    free(arr);

    return *node;
}

// Функция для вставки ключа в дерево с корнем в данном узле
Node *insert(Node **node, int key) {
    if (*node == NULL) {
        *node = new_node(key);
        return *node;
    }

    if (key < (*node)->key) {
        (*node)->left = insert(&(*node)->left, key);
    } else if(key > (*node)->key) {
        (*node)->right = insert(&(*node)->right, key);
    }else{
        return NULL;
    }

    int left_size = size((*node)->left);
    int right_size = size((*node)->right);

    if (left_size > ALPHA * (left_size + right_size + 1) ||
        right_size > ALPHA * (left_size + right_size + 1)) {

        rebuild(node);
    }

    return *node;
}

// Функция для поиска ключа в дереве с корнем в данном узле
Node *search(Node *node, int key) {
    if (node == NULL) return NULL;

    if (key < node->key) {
        return search(node->left, key);
    } else if (key > node->key) {
        return search(node->right, key);
    } else {
        return node;
    }
}

// Функция для печати ключей в дереве с корнями в данном узле
void inorder(Node *node) {
    if (node != NULL) {
        inorder(node->left);
        printf("%d ", node->key);
        inorder(node->right);
    }
}

// Функция для создания нового дерева
Tree *new_tree() {
    Tree *tree = malloc(sizeof(Tree));
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

void printTree(struct Node *root, int space) {
    if (root == NULL)
        return;
    space += 5;
    printTree(root->right, space);
    printf("\n");
    for (int i = 5; i < space; i++)
    printf(" ");
    printf("%d\n", root->key);
    printTree(root->left, space);
}



struct Node* minKeyNode(struct Node* node) {
    struct Node* current = node;

    /* Проходимся влево от текущего узла, пока не дойдем до листа */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

Node *deleteNode(Node *node, int key) {
    if (node == NULL) {
        return NULL;
    }

    if (key < node->key) {
        node->left = deleteNode(node->left, key);
    } else if (key > node->key) {
        node->right = deleteNode(node->right, key);
    } else {
        // Случай 1: Нет ребенка или только один ребенок
        if (node->left == NULL) {
            struct Node *temp = node->right;
            free(node);
            return temp;
        } else if (node->right == NULL) {
            struct Node *temp = node->left;
            free(node);
            return temp;
        }
        // Случай 2: Двое детей
        struct Node *temp = minKeyNode(node->right);
        node->key = temp->key;
        node->right = deleteNode(node->right, temp->key);
    }
    int left_size = size(node->left);
    int right_size = size(node->right);
    // Проверка, не разбалансировано ли дерево и не нуждается ли оно в перестройке
    if (left_size > ALPHA * (left_size + right_size + 1) ||
        right_size > ALPHA * (left_size + right_size + 1)) {
        return rebuild(&node);
    }
    return node;
}


int main() {
    Tree *tree = new_tree();

    insert(&tree->root, 5);
    printTree(tree->root, 5);
    printf("\n==========\n");

    insert(&tree->root, 4);
    printTree(tree->root, 5);
    printf("\n==========\n");


    insert(&tree->root, 3);
    printTree(tree->root, 5);
    printf("\n==========\n");

    insert(&tree->root, 2);
    printTree(tree->root, 5);
    printf("\n==========\n");

    insert(&tree->root, 7);
    printTree(tree->root, 5);
    printf("\n==========\n");

    insert(&tree->root, 6);
    printTree(tree->root, 5);
    printf("\n==========\n");

    insert(&tree->root, 8);
    printTree(tree->root, 5);
    printf("\n==========\n");

    insert(&tree->root, 1);
    printTree(tree->root, 5);
    printf("\n==========\n");

    insert(&tree->root, 9);
    printTree(tree->root, 5);
    printf("\n==========\n");
    inorder(tree->root);

    tree->root = deleteNode(tree->root, 1);
    printTree(tree->root, 5);
    printf("\n==========\n");
    tree->root = deleteNode(tree->root, 2);
    printTree(tree->root, 5);
    printf("\n==========\n");
    tree->root = deleteNode(tree->root, 3);
    printTree(tree->root, 5);
    printf("\n==========\n");
    tree->root = deleteNode(tree->root, 4);
    printTree(tree->root, 5);
    printf("\n==========\n");
    tree->root = deleteNode(tree->root, 5);
    printTree(tree->root, 5);
    printf("\n==========\n");
    tree->root = deleteNode(tree->root, 6);
    printTree(tree->root, 10);
    printf("\n==========\n");
    tree->root = deleteNode(tree->root, 7);
    inorder(tree->root);
    printTree(tree->root, 5);
    printf("\n");
    
    return 0;
}