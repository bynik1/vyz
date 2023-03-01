#include <stdio.h>

struct sgt_node {
    int data;
    struct sgt_node *left;
    struct sgt_node *right;
    int size; // размер поддерева с корнем в текущем узле
};

struct sgt_tree {
    struct sgt_node *root;
    int size; // общий размер дерева
    int max_size; // максимально допустимый размер дерева (отношение size к max_size определяет глубину дерева)
    double alpha; // допустимое отношение размера поддерева к размеру родительского узла
};

struct sgt_tree *sgt_create(double alpha, int max_size);
void sgt_destroy(struct sgt_tree *tree);
    void sgt_destroy_node(struct sgt_node *node);
struct sgt_node *sgt_find_node(struct sgt_tree *tree, int data);
struct sgt_node *sgt_insert(struct sgt_tree *tree, int data);
    struct sgt_node *sgt_insert_node(struct sgt_tree *tree, struct sgt_node *node, int data);
    void sgt_rebalance(struct sgt_tree *tree, struct sgt_node **node_ptr);
struct sgt_node *sgt_delete_node(struct sgt_tree *tree, int data);
void sgt_print(struct sgt_node *node, int level);


struct sgt_tree *sgt_create(double alpha, int max_size) {
    struct sgt_tree *tree = malloc(sizeof(struct sgt_tree));
    if (tree == NULL) {
        return NULL; // ошибка выделения памяти
    }
    tree->root = NULL;
    tree->size = 0;
    tree->max_size = max_size;
    tree->alpha = alpha;
    return tree;
}

void sgt_destroy(struct sgt_tree *tree) {
    if (tree != NULL) {
        sgt_destroy_node(tree->root); // удаляем все узлы дерева
        free(tree); // освобождаем память, выделенную под дерево
    }
}
void sgt_destroy_node(struct sgt_node *node) {
    if (node != NULL) {
        sgt_destroy_node(node->left); // удаляем левое поддерево
        sgt_destroy_node(node->right); // удаляем правое поддерево
        free(node); // освобождаем память, выделенную под узел
    }
}

struct sgt_node *sgt_find_node(struct sgt_tree *tree, int data) {
    struct sgt_node *current = tree->root; // начинаем поиск с корня дерева
    while (current != NULL && current->data != data) {
        if (data < current->data) {
            current = current->left; // движемся влево, если искомый ключ меньше значения текущего узла
        } else {
            current = current->right; // движемся вправо, если искомый ключ больше значения текущего узла
        }
    }
    return current; // возвращаем указатель на найденный узел или NULL, если узел не найден
}


struct sgt_node *sgt_insert(struct sgt_tree *tree, int data) {
    struct sgt_node *node = sgt_insert_node(tree, tree->root, data); // вызываем вспомогательную функцию для вставки узла
    if (node != NULL) { // если вставка прошла успешно
        sgt_rebalance(tree, node); // вызываем функцию перебалансировки дерева
    }
    return node; // возвращаем указатель на вставленный узел
}

struct sgt_node *sgt_insert_node(struct sgt_tree *tree, struct sgt_node *node, int data) {
    if (node == NULL) { // если текущий узел пустой, создаем новый узел и вставляем его в дерево
        struct sgt_node *new_node = sgt_create_node(data);
        tree->size++;
        return new_node;
    }
    if (data < node->data) { // если ключ меньше значения текущего узла, спускаемся в левое поддерево
        node->left = sgt_insert_node(tree, node->left, data);
    } else if (data > node->data) { // если ключ больше значения текущего узла, спускаемся в правое поддерево
        node->right = sgt_insert_node(tree, node->right, data);
    } else { // если ключ уже есть в дереве, возвращаем указатель на этот узел
        return node;
    }
    return node; // возвращаем указатель на текущий узел
}

static void sgt_rebalance(struct sgt_tree *tree, struct sgt_node **node_ptr) {
    struct sgt_node *node = *node_ptr;

    // Calculate the size and height of the current subtree
    int size = sgt_size(node);
    int height = sgt_height(node);

    // Check if the subtree is unbalanced
    if (size > 1 && height > ceil(log2(size))) {
        // The subtree is unbalanced, find the scapegoat
        struct sgt_node *scapegoat = sgt_find_scapegoat(node, size);

        // Rebuild the subtree rooted at the scapegoat
        struct sgt_node *new_subtree = sgt_build_tree(scapegoat, size);

        // Replace the old subtree with the new subtree
        *node_ptr = new_subtree;

        // Update the parent pointers of the new subtree
        if (new_subtree != NULL) {
            new_subtree->parent = node->parent;
            sgt_update_child_pointer(tree, new_subtree);
        }

        // Destroy the old subtree
        sgt_destroy_subtree(scapegoat);
    }
}


