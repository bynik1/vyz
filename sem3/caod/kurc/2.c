#include <stdio.h>
#include <stdlib.h>

#define ALPHA 0.7

struct sgt_node {
    int value;
    int size;
    struct sgt_node *left;
    struct sgt_node *right;
};

struct sgt_tree {
    struct sgt_node *root;
    int size;
};

struct sgt_node *sgt_new_node(int value) {
    struct sgt_node *node = (struct sgt_node*) malloc(sizeof(struct sgt_node));
    node->value = value;
    node->size = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int sgt_size(struct sgt_node *node) {
    return (node == NULL) ? 0 : node->size;
}

void sgt_update_size(struct sgt_node *node) {
    node->size = sgt_size(node->left) + sgt_size(node->right) + 1;
}

void sgt_free(struct sgt_node *node) {
    if (node == NULL) return;
    sgt_free(node->left);
    sgt_free(node->right);
    free(node);
}

struct sgt_node *sgt_build(int *arr, int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;
    struct sgt_node *root = sgt_new_node(arr[mid]);
    root->left = sgt_build(arr, start, mid - 1);
    root->right = sgt_build(arr, mid + 1, end);
    sgt_update_size(root);
    return root;
}

int sgt_to_array(struct sgt_node *node, int *arr, int i) {
    if (node == NULL) return i;
    i = sgt_to_array(node->left, arr, i);
    arr[i++] = node->value;
    i = sgt_to_array(node->right, arr, i);
    return i;
}

struct sgt_node* sgt_rebuild(struct sgt_node **node) {
    int n = sgt_size(*node);
    int *arr = (int*) malloc(n * sizeof(int));
    sgt_to_array(*node, arr, 0);
    *node = sgt_build(arr, 0, n - 1);
    free(arr);
    return *node;
}

void sgt_insert(struct sgt_node **node, int value) {
    if (*node == NULL) {
        *node = sgt_new_node(value);
        return;
    }
    int cmp = value - (*node)->value;
    if (cmp > 0) {
        sgt_insert(&(*node)->left, value);
    } else {
        sgt_insert(&(*node)->right, value);
    }
    sgt_update_size(*node);
    int size_left = sgt_size((*node)->left);
    int size_right = sgt_size((*node)->right);
    int size = sgt_size(*node);
    if (size_left > ALPHA * size || size_right > ALPHA * size) {
        sgt_rebuild(node);
    }
}


void sgt_init(struct sgt_tree *tree) {
    tree->root = NULL;
    tree->size = 0;
}

void sgt_free_tree(struct sgt_tree *tree) {
    sgt_free(tree->root);
    tree->root = NULL;
    tree->size = 0;
}

void sgt_insert_value(struct sgt_tree *tree, int value) {
    sgt_insert(&tree->root, value);
    tree->size++;
}

void sgt_print(struct sgt_node *node, int level) {
    if (node == NULL) {
        return;
    }

    sgt_print(node->left, level + 1);

    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("%d\n", node->value);
    sgt_print(node->right, level + 1);

}

void sgt_print_tree(struct sgt_tree *tree) {
    printf("Scapegoat Tree:\n");
    sgt_print(tree->root, 0);
    printf("Size: %d\n", tree->size);
}

int isUnbalanced(struct sgt_node *node) {
    int size_left = sgt_size(node->left);

    int size_right = sgt_size(node->right);

    int size_node = size_left + size_right + 1;//размер родителя
    printf("%d\n", size_left > size_node * ALPHA || size_right > size_node * ALPHA);


    return (size_left > size_node * ALPHA || size_right > size_node * ALPHA);
}

struct sgt_node* minValueNode(struct sgt_node* node) {
    struct sgt_node* current = node;

    /* Проходимся влево от текущего узла, пока не дойдем до листа */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

int countNodes(struct sgt_node* node) {
    if (node == NULL)
        return 0;
    else
        return 1 + countNodes(node->left) + countNodes(node->right);
}

struct sgt_node *deleteNode(struct sgt_node **node, int key) {
    if (*node == NULL) {
        return NULL;
    }

    if (key < (*node)->value) {
        (*node)->left = deleteNode(&(*node)->left, key);
    } else if (key > (*node)->value) {
        (*node)->right = deleteNode(&(*node)->right, key);
    } else {
        // Случай 1: Нет ребенка или только один ребенок
        if ((*node)->left == NULL) {
            struct sgt_node *temp = (*node)->right;
            free((*node));
            return temp;
        } else if ((*node)->right == NULL) {
            struct sgt_node *temp = (*node)->left;
            free((*node));
            return temp;
        }
        // Случай 2: Двое детей
        struct sgt_node *temp = minValueNode((*node)->right);
        (*node)->value = temp->value;
        (*node)->right = deleteNode(&(*node)->right, temp->value);
    }
    // Проверка, не разбалансировано ли дерево и не нуждается ли оно в перестройке
    if (isUnbalanced(*node)) {
        return sgt_rebuild(&(*node));
    }
    return *node;
}

void sgt_deleteNode(struct sgt_tree *tree, int value){
    deleteNode(&tree->root, value);
    tree->size--;
}



int main() {
    struct sgt_tree tree;
    sgt_init(&tree);
    sgt_insert_value(&tree, 50);
    sgt_print_tree(&tree);
    sgt_insert_value(&tree, 40);
    sgt_print_tree(&tree);
    sgt_insert_value(&tree, 30);
    sgt_print_tree(&tree);

    sgt_insert_value(&tree, 20);
    sgt_print_tree(&tree);

    sgt_insert_value(&tree, 70);
    sgt_print_tree(&tree);

    sgt_insert_value(&tree, 60);
    sgt_print_tree(&tree);

    sgt_insert_value(&tree, 80);
    sgt_print_tree(&tree);
    //sgt_free_tree(&tree);

    sgt_deleteNode(&tree, 20);
    sgt_print_tree(&tree);


    // struct sgt_node *root = NULL;
    // int choice, key;

    // do {
    //     printf("1. Insert\n");
    //     printf("2. Delete\n");
    //     printf("3. Search\n");
    //     printf("4. Print\n");
    //     printf("5. Destroy\n");
    //     printf("6. Exit\n");
    //     printf("Enter your choice: ");
    //     scanf("%d", &choice);

    //     switch (choice) {
    //         case 1:
    //             printf("Enter key to insert: ");
    //             scanf("%d", &key);
    //             sgt_insert(root, key);
    //             printf("Key %d inserted\n", key);
    //             break;
    //         case 2:
    //             printf("Enter key to delete: ");
    //             scanf("%d", &key);
    //             if (sgt_search(root, key) != NULL) {
    //                 root = sgt_delete(root, key);
    //                 printf("Key %d deleted\n", key);
    //             } else {
    //                 printf("Key %d not found\n", key);
    //             }
    //             break;
    //         case 3:
    //             printf("Enter key to search: ");
    //             scanf("%d", &key);
    //             if (sgt_search(root, key) != NULL) {
    //                 printf("Key %d found\n", key);
    //             } else {
    //                 printf("Key %d not found\n", key);
    //             }
    //             break;
    //         case 4:
    //             printf("Scapegoat Tree:\n");
    //             sgt_print(root, 0);
    //             break;
    //         case 5:
    //             sgt_destroy(root);
    //             root = NULL;
    //             printf("Scapegoat Tree destroyed\n");
    //             break;
    //         case 6:
    //             printf("Exiting...\n");
    //             break;
    //         default:
    //             printf("Invalid choice, try again\n");
    //     }

    //     printf("\n");

    // } while (choice != 6);

    return 0;
}

