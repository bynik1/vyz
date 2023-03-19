
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#define ALPHA 0.7
#define BETA 1


/* Структура узла дерева */
typedef struct node {
    int key;
    struct node* left;
    struct node* right;
    int size;   // размер поддерева
} Node;

int get_height(Node* root) {
    if (root == NULL) {
        return -1;
    }
    int left_height = get_height(root->left);
    int right_height = get_height(root->right);
    return 1 + ((left_height > right_height) ? left_height : right_height);
}



Node* create_node(int key) {
    Node* node = (Node*) malloc(sizeof(Node));

    if (node == NULL) {
        printf("Failed to allocate memory for a new node\n");
        return NULL;
    }

    node->key = key;
    node->size = 1;
    node->left = NULL;
    node->right = NULL;

    return node;
}

int get_size(Node* node) {
    if (node == NULL) {
        return 0;
    }

    return node->size;
}

Node* rebuild(Node** root_copy, int size) {
    if (size == 0) {
        *root_copy = NULL;
        return NULL;
    }

    // Создаем сбалансированное дерево из отсортированного массива узлов
    int mid = size / 2;
    Node* root = *(root_copy + mid);
    root->left = NULL;
    root->right = NULL;
    rebuild(root_copy, mid);
    rebuild(root_copy + mid + 1, size - mid - 1);
    *root_copy = root;

    return *root_copy;
}



bool insert_node(Node** root, Node* new_node, int* depth) {
    if (*root == NULL) {
        *root = new_node;
        *depth = 1;
        return true;
    }

    if (new_node->key == (*root)->key) {
        return false;
    }

    bool inserted;
    if (new_node->key < (*root)->key) {
        inserted = insert_node(&(*root)->left, new_node, depth);
    } else {
        inserted = insert_node(&(*root)->right, new_node, depth);
    }

    if (inserted) {
        // Обновление размера поддерева
        (*root)->size++;

        // Проверка, нужно ли увеличить глубину нового узла
        int left_size = get_size((*root)->left);
        int right_size = get_size((*root)->right);
        int max_size = left_size > right_size ? left_size : right_size;
        if (max_size > ALPHA * (*root)->size) {
            *depth += 1;
        }
    }

    return inserted;
}


bool insert(Node** root, int key) {
    // Создание нового узла
    Node* new_node = create_node(key);
    if (new_node == NULL) {
        return false;
    }

    // Вставка нового узла в дерево
    int depth = 0;
    bool inserted = insert_node(root, new_node, &depth);
    if (!inserted) {
        free(new_node);
        return false;
    }

    // Проверка, нужно ли выполнить операцию rebuild
    if (depth > log(1.0 / ALPHA) / log(1.0 / BETA)) {
        Node* root_copy = *root;
        int size = get_size(root_copy);
        Node* new_root = rebuild(&root_copy, size);
        *root = new_root;
    }

    return true;
}


bool search(Node* root, int key) {
    if (root == NULL) {
        return false;
    }

    if (key == root->key) {
        return true;
    } else if (key < root->key) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

bool delete(Node** root, int key) {
    Node* parent = NULL;
    Node* current = *root;

    // Find the node to delete and its parent
    while (current != NULL && current->key != key) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        // The node to delete was not found
        return false;
    }

    if (current->left == NULL && current->right == NULL) {
        // Case 1: The node to delete has no children
        if (parent == NULL) {
            // The node to delete is the root
            *root = NULL;
        } else if (current == parent->left) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(current);
    } else if (current->left == NULL || current->right == NULL) {
        // Case 2: The node to delete has one child
        Node* child = (current->left != NULL) ? current->left : current->right;
        if (parent == NULL) {
            // The node to delete is the root
            *root = child;
        } else if (current == parent->left) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        free(current);
    } else {
        // Case 3: The node to delete has two children
        Node* successor = current->right;
        while (successor->left != NULL) {
            successor = successor->left;
        }
        int successor_key = successor->key;
        delete(root, successor_key);
        current->key = successor_key;
    }

    return true;
}

void print_tree_visual(Node* root, int depth) {
    if (root == NULL) {
        return;
    }
    print_tree_visual(root->right, depth + 1);
    for (int i = 0; i < depth; i++) {
        printf("   ");
    }
    printf("|-- %d\n", root->key);
    print_tree_visual(root->left, depth + 1);
}



int main() {
    Node* root = NULL;
    int keys[] = {5, 3, 2, 10, 8, 11, 12, 9, 7};

    // Вставляем ключи в дерево
    for (int i = 0; i < 9; i++) {
        insert(&root, keys[i]);
    }
    print_tree_visual(root, 1);

    // Печатаем размер дерева и высоту
    printf("Size: %d\n", get_size(root));
    printf("Height: %d\n", get_height(root));

    // Проверяем наличие ключа
    int key_to_search = 7;
    if (search(root, key_to_search)) {
        printf("Key %d found in the tree.\n", key_to_search);
    } else {
        printf("Key %d not found in the tree.\n", key_to_search);
    }

    // Удаляем ключ
    int key_to_delete = 3;
    delete(&root, key_to_delete);
    key_to_delete = 2;
    if (delete(&root, key_to_delete)) {
        printf("Key %d deleted from the tree.\n", key_to_delete);
    } else {
        printf("Key %d not found in the tree.\n", key_to_delete);
    }
    print_tree_visual(root, 1);


    // Печатаем размер дерева и высоту после удаления ключа
    printf("Size: %d\n", get_size(root));
    printf("Height: %d\n", get_height(root));

    return 0;
}

