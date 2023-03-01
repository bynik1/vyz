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

void sgt_init(struct sgt_tree *tree) {
    tree->root = NULL;
    tree->size = 0;
}

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

void sgt_free_tree(struct sgt_tree *tree) {
    sgt_free(tree->root);
    tree->root = NULL;
    tree->size = 0;
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

struct sgt_node * sgt_rebuild(struct sgt_node **node) {
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

struct sgt_node *sgt_delete_node(struct sgt_node *node, int value) {
    if (!node)
        return NULL;
    if (value < node->value)
        node->left = sgt_delete_node(node->left, value);
    else if (value > node->value)
        node->right = sgt_delete_node(node->right, value);
    else {
        if (!node->right) {
            struct sgt_node *tmp = node->left;
            free(node);
            return tmp;
        }
        if (!node->left) {
            struct sgt_node *tmp = node->right;
            free(node);
            return tmp;
        }
        struct sgt_node *tmp = sgt_min_value_node(node->right);
        node->value = tmp->value;
        node->right = sgt_delete_node(node->right, tmp->value);
    }
    sgt_update_size(node);
    if (sgt_size(node->left) > sgt_size(node) * ALPHA || sgt_size(node->right) > sgt_size(node) * ALPHA)
        return sgt_rebuild(&node);
    return node;
}


struct sgt_node* sgt_find_node(struct sgt_node *node, int key) {
    if (node == NULL || node->value == key) {
        return node;
    }
    if (key < node->value) {
        return sgt_find_node(node->left, key);
    } else {
        return sgt_find_node(node->right, key);
    }
}


int sgt_delete(struct sgt_tree *tree, int key) {
    struct sgt_node *node = sgt_find_node(tree->root, key);
    if (!node)
        return 0;
    sgt_delete_node(tree, node);
    return 1;
}

int main() {
    struct sgt_tree *tree;
    sgt_init(tree);
    sgt_insert_value(tree, 50);
    sgt_print_tree(tree);
    sgt_insert_value(tree, 40);
    sgt_print_tree(tree);
    sgt_insert_value(tree, 30);
    sgt_print_tree(tree);

    sgt_insert_value(tree, 20);
    sgt_print_tree(tree);

    sgt_insert_value(tree, 70);
    sgt_print_tree(tree);

    sgt_insert_value(tree, 60);
    sgt_print_tree(tree);

    sgt_insert_value(tree, 80);
    sgt_print_tree(tree);

    sgt_insert_value(tree, 10);
    sgt_print_tree(tree);
    sgt_insert_value(tree, 90);
    sgt_print_tree(tree);

    sgt_insert_value(tree, 100);
    sgt_print_tree(tree);
    sgt_free_tree(tree);

    sgt_delete(tree, 60);
    sgt_delete(tree, 20);
    sgt_delete(tree, 88);
    sgt_delete(tree, 10);
    sgt_delete(tree, 40);
    sgt_delete(tree, 70);
    sgt_delete(tree, 100);
    sgt_delete(tree, 30);
    sgt_delete(tree, 50);
    sgt_delete(tree, 90);















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

