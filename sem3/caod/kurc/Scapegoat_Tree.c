#include <stdio.h>
#include <stdlib.h>

#define ALPHA 0.7 // balance factor
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Struct for tree nodes
struct node {
    int key;
    struct node *left;
    struct node *right;
    int size;
};

// Function to create new nodes
struct node *newNode(int key) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = key;
    temp->left = temp->right = NULL;
    temp->size = 1;
    return temp;
}

// Функция для получения размера поддерева с корнем в узле
int size(struct node *node) {
    if (node == NULL) return 0;
    return node->size;
}


// Функция для обновления размера поддерева с корнем в узле

void updateSize(struct node *node) {
    node->size = 1 + size(node->left) + size(node->right);
}

// Функция для определения высоты поддерева с корнем в узле
int height(struct node *node) {
    if (node == NULL) return 0;
    return 1 + MAX(height(node->left), height(node->right));
}

// Функция для поиска максимального дочернего поддерева
struct node *findMaxChild(struct node *node) {
    if (size(node->left) > size(node->right)) return node->left;
    return node->right;
}

// Функция isUnbalanced принимает указатель на узел дерева и проверяет, является ли он несбалансированным. 
// Несбалансированный узел - это узел, чей левый или правый поддеревья превышают заданный коэффициент ALPHA узлов.
// Функция size используется внутри isUnbalanced для определения размера левого и правого поддеревьев, а также размера текущего узла. 
// Затем функция сравнивает размеры поддеревьев с размером узла, учитывая коэффициент ALPHA, и возвращает true, если узел несбалансирован, и false в противном случае.
// Обратите внимание, что коэффициент ALPHA определяется в глобальном контексте или передается как параметр в функцию isUnbalanced. 
// В данном примере мы предполагаем, что ALPHA определен глобально.

// Функция для проверки несбалансированности узла
int isUnbalanced(struct node *node) {
    printf("isUnbalanced\n");
    int size_left = size(node->left);
    printf("isUnbalanced\n");

    int size_right = size(node->right);
    printf("isUnbalanced\n");

    int size_node = size_left + size_right + 1;//размер родителя
    printf("isUnbalanced\n");
    printf("%d\n", size_left > size_node * ALPHA || size_right > size_node * ALPHA);


    return (size_left > size_node * ALPHA || size_right > size_node * ALPHA);
}

// Функция storeInorder проходит по поддереву в порядке возрастания и сохраняет указатели на все узлы в массиве. 
// Это позволяет нам сохранить порядок узлов при построении нового дерева.

// Сохраняйте указатели на узлы в дереве при обходе по порядку в массиве
void storeInorder(struct node *node, struct node **arr, int *index) {
    if (node != NULL) {
        storeInorder(node->left, arr, index);
        arr[(*index)++] = node;
        storeInorder(node->right, arr, index);
    }
}

// Функция buildBalancedTree принимает массив узлов, сохраненных в порядке возрастания, 
// а также индексы начала и конца подмассива, который нужно использовать для построения нового сбалансированного дерева. 
// Функция находит середину подмассива и использует ее в качестве корня нового дерева. 
// Затем функция рекурсивно вызывает саму себя для левой половины подмассива и назначает возвращенный узел левым потомком корня, 
// а затем вызывает саму себя для правой половины подмассива и назначает возвращенный узел правым потомком корня.

// Постройте сбалансированное двоичное дерево поиска из массива узлов
struct node *buildBalancedTree(struct node **arr, int start, int end) {
    if (start > end) {
        return NULL;
    }

    int mid = (start + end) / 2;
    struct node *root = arr[mid];

    root->left = buildBalancedTree(arr, start, mid - 1);//нет адреса по root->left
    root->right = buildBalancedTree(arr, mid + 1, end);

    return root;
}

// Функция rebuild принимает указатель на корень поддерева, которое нужно перестроить, 
// а также целое число n, которое указывает количество узлов в поддереве. 
// Функция использует две другие вспомогательные функции, storeInorder и buildBalancedTree, 
// чтобы сохранить ключи всех узлов в поддереве в массиве и построить сбалансированное дерево из этого массива.

// Функция для перестройки поддерева с корнем в узле

struct node *rebuild(struct node *node, int n) {
    struct node **arr = (struct node **)malloc(n * sizeof(struct node *));
    int i = 0;
    storeInorder(node, arr, &i);

    return buildBalancedTree(arr, 0, n - 1);
}


// Эта функция принимает указатель на корень дерева и ключ, который нужно найти. 
// Если дерево пустое, функция возвращает NULL. 
// В противном случае функция рекурсивно ищет узел с заданным ключом, 
// сравнивая ключ с текущим узлом и переходя либо в левое, 
// либо в правое поддерево в зависимости от результата сравнения. 
// Если ключ найден, функция возвращает указатель на найденный узел. 
// В противном случае она возвращает NULL.


//Найдите узел с заданным ключом в дереве Scapegoat Tree

struct node *search(struct node *node, int key) {
    if (node == NULL) return NULL;

    if (key < node->key) {
        return search(node->left, key);
    } else if (key > node->key) {
        return search(node->right, key);
    } else {
        return node;
    }
}


// Функция deleteNode принимает указатель на корень дерева и ключ, который нужно удалить. 
// Она возвращает указатель на корень дерева после удаления узла.

// Функция deleteNode использует рекурсию для удаления узла с заданным ключом. Если дерево пустое, функция возвращает NULL. 
// Если ключ меньше ключа текущего узла, функция рекурсивно вызывает deleteNode для левого поддерева. 
// Если ключ больше ключа текущего узла, функция рекурсивно вызывает deleteNode для правого поддерева. 
// Если ключ равен ключу текущего узла, функция проверяет, сколько детей есть у удаляемого узла.

// В случае 1 узел не имеет детей или только одного ребенка, функция удаляет узел и возвращает указатель на его единственного потомка (или NULL, если узел не имел потомков).
// В случае 2 узел имеет двух потомков, функция находит узел с наименьшим ключом в правом поддереве, копирует его ключ в удаляемый узел и удаляет узел с наименьшим ключом.
// После удаления узла функция проверяет, является ли дерево несбалансированным, и, если это так, вызывает функцию rebuild для его перестройки.

// Обратите внимание, что функция deleteNode использует функцию isUnbalanced для проверки, является ли дерево несбалансированным, и функцию rebuild для его перестройки. 
// Кроме того, функция deleteNode использует вспомогательную функцию countNodes для подсчёта узлов в дереве


struct node* minValueNode(struct node* node) {
    struct node* current = node;

    /* Проходимся влево от текущего узла, пока не дойдем до листа */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

int countNodes(struct node* node) {
    if (node == NULL)
        return 0;
    else
        return 1 + countNodes(node->left) + countNodes(node->right);
}

struct node *deleteNode(struct node *node, int key) {
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
            struct node *temp = node->right;
            free(node);
            return temp;
        } else if (node->right == NULL) {
            struct node *temp = node->left;
            free(node);
            return temp;
        }
        // Случай 2: Двое детей
        struct node *temp = minValueNode(node->right);
        node->key = temp->key;
        node->right = deleteNode(node->right, temp->key);
    }
    // Проверка, не разбалансировано ли дерево и не нуждается ли оно в перестройке
    if (isUnbalanced(node)) {
        return rebuild(node, countNodes(node));
    }
    return node;
}

// Функция printInorder принимает указатель на корень дерева и выводит ключи узлов в дереве в порядке возрастания. 
// Функция использует рекурсию для прохождения по всем узлам дерева.
// Функция printInorder сначала вызывает себя для левого поддерева, чтобы вывести ключи узлов в порядке возрастания, 
// затем выводит ключ текущего узла и, наконец, вызывает себя для правого поддерева, чтобы вывести ключи узлов в порядке возрастания.

// Выведите ключи узлов в дереве по порядку
void printInorder(struct node *node) {
    if (node != NULL) {
        printInorder(node->left);
        printf("%d ", node->key);
        printInorder(node->right);
    }
}

// Эта функция принимает указатель на корень дерева, а также ключ и значение для нового узла, который нужно вставить. 
// Если дерево пустое, она создает новый узел и возвращает его. 
// В противном случае она ищет место для вставки нового узла в соответствии с правилами бинарного дерева поиска. 
// После вставки нового узла, функция обновляет размеры всех узлов в цепочке от корня до нового узла, 
// а затем проверяет, не нарушено ли условие сбалансированности дерева. 
// Если оно нарушено, функция ищет scapegoat (узел, который, возможно, является причиной несбалансированности) 
// и выполняет перестройку поддерева с его помощью. Наконец, функция возвращает указатель на корень дерева.

// Функция для вставки узла в дерево
struct node *insert(struct node *node, int key) {
    printf("key = %d\n", key);
    printf("&&& ");

    if (node == NULL){
        printf("0");
        return newNode(key);
    } 

    if (key < node->key) {
        printf("1");
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        printf("2");
        node->right = insert(node->right, key);
    } else {
        printf("3");
        return NULL;
    }
    printf("update\n");
    updateSize(node);
    printf("key = %d\n", node->key);


    if (isUnbalanced(node)) {
        printf("4edsdad");
        int n = size(node);
        struct node *parent = node;
        struct node *child = findMaxChild(node);
        while (size(child) <= ALPHA * size(parent)) {
            parent = child;
            child = findMaxChild(parent);
        }
        printf("5");

        struct node *temp = rebuild(parent, size(parent));

        if (parent == node) {
            node = temp;
        printf("6");

        } else if (parent->left == child) {
            parent->left = temp;
        } else {
            parent->right = temp;
        }
    }
    printf("***\n");

    return node;
}


void sgt_free(struct node *node) {
    if (node == NULL) return;
    sgt_free(node->left);
    sgt_free(node->right);
    free(node);
}

void printTree(struct node *root, int space) {
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


int main(){
    struct node *root = NULL;
    int mid = (0 -1 ) / 2;
    //printf("%d \n", mid);
    root = insert(root, 5);
    printf("%p\n", root);
    //printTree(root, 0);
    root = insert(root, 4);
    printf("%p\n", root);
    //printTree(root, 0);
    root = insert(root, 3);
    printf("%p\n", root);
    //printTree(root, 0);
    root = insert(root, 2);
    printf("%p\n", root);
    //printTree(root, 0);

    root = insert(root, 7);
    printf("%p\n", root);
    //printTree(root, 0);
    root = insert(root, 6);
    printf("%p\n", root);
    root = insert(root, 8);
    printf("%p\n", root);
    //printTree(root, 0);
    root = deleteNode(root, 6);
    printf("%p\n", root);
    //printTree(root, 0);


    printf("Inorder traversal of the tree: ");
    printInorder(root);
    printf("\n");
    return 0;
}