#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_HEIGHT 32000

struct sgt_node {
    int value;
    int size;
    struct sgt_node *left;
    struct sgt_node *right;
};

// Реализация стека для итеративных операций
struct stack_node {
    struct sgt_node *node;
    struct stack_node *next;
};

struct stack {
    struct stack_node *top;
};

void stack_push(struct stack *s, struct sgt_node *node) {
    struct stack_node *new_node = (struct stack_node*) malloc(sizeof(struct stack_node));
    new_node->node = node;
    new_node->next = s->top;
    s->top = new_node;
}

struct sgt_node* stack_pop(struct stack *s) {
    if (s->top == NULL) {
        return NULL;
    }
    struct sgt_node *node = s->top->node;
    struct stack_node *temp = s->top;
    s->top = s->top->next;
    free(temp);
    return node;
}

struct sgt_node* create_node(int value) {
    struct sgt_node *new_node = (struct sgt_node*) malloc(sizeof(struct sgt_node));
    new_node->value = value;
    new_node->size = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

int size(struct sgt_node *root) {
    if (root == NULL) {
        return 0;
    }
    return root->size;
}

int is_balanced(struct sgt_node *node, int alpha) {
    if (node == NULL) {
        return 1;
    }
    int lh = size(node->left);
    int rh = size(node->right);
    int balanced = (lh <= alpha * rh) && (rh <= alpha * lh);
    return balanced && is_balanced(node->left, alpha) && is_balanced(node->right, alpha);
}

struct sgt_node* rebuild(struct sgt_node **root, int size) {
    struct sgt_node *node = *root;
    struct sgt_node **array = (struct sgt_node**) malloc(sizeof(struct sgt_node*) * size);
    int i = 0;
    // заполнение массива элементами дерева в порядке обхода в глубину (DFS)
    struct stack *s = (struct stack*) malloc(sizeof(struct stack));
    s->top = NULL;
    while (node != NULL || s->top != NULL) {
        if (node != NULL) {
            stack_push(s, node);
            node = node->left;
        } else {
            node = stack_pop(s);
            array[i++] = node;
            node = node->right;
        }
    }
    // создание нового сбалансированного дерева
    int mid = size / 2;
    struct sgt_node *new_root = array[mid];
    new_root->size = size;
    struct sgt_node **left_array = array;
    int left_size = mid;
    struct sgt_node **right_array = array + mid + 1;
    int right_size = size - mid - 1;
    new_root->left = rebuild(left_array, left_size);
    new_root->right = rebuild(right_array, right_size);
    // освобождение
    free(array);
    free(s);
    *root = new_root;
    return new_root;
}


struct sgt_node **stack_top(struct stack *s) {
    return &(s->top->node);
}

void free_stack(struct stack *s) {
    while (s->top != NULL) {
        struct stack_node *temp = s->top;
        s->top = s->top->next;
        free(temp);
    }
    free(s);
}
struct sgt_node* add(struct sgt_node **root, int value, int alpha) {
    // поиск места для нового элемента
    struct sgt_node **p = root;
    struct stack *s = malloc(sizeof(struct stack));
    s->top = NULL;
    while (*p != NULL) {
        stack_push(s, *p);
        if ((*p)->value == value) {
            free_stack(s);
            return *p; // элемент уже существует в дереве
        } else if ((*p)->value > value) {
            p = &((*p)->left);
        } else {
            p = &((*p)->right);
        }
    }
    // добавление нового элемента
    *p = create_node(value);
    // обновление размера всех узлов на пути от корня до нового элемента
    while (s->top != NULL) {
        struct sgt_node *node = stack_pop(s);
        node->size++;
        if (!is_balanced(node, alpha)) {
            rebuild(p, node->size);
            break;
        }
    }
    free_stack(s);
    return *p;
}





    struct sgt_node* search(struct sgt_node *root, int value) {
    struct sgt_node *node = root;
    while (node != NULL) {
        if (node->value == value) {
        return node;
        } else if (node->value > value) {
        node = node->left;
        } else {
        node = node->right;
        }
    }
    return NULL;
}

struct sgt_node* find_max_node(struct sgt_node **root) {
    struct sgt_node **p = root;
    while ((*p)->right != NULL) {
        p = &((*p)->right);
    }
    return *p;
}

struct sgt_node* delete(struct sgt_node **root, int value, int alpha) {
    // поиск узла для удаления
    struct sgt_node **p = root;
    struct stack *s = malloc(sizeof(struct stack));
    s->top = NULL;
    while (*p != NULL) {
        stack_push(s, *p);
        if ((*p)->value == value) {
            break;
        } else if ((*p)->value > value) {
            p = &((*p)->left);
        } else {
            p = &((*p)->right);
        }
    }

    if (*p == NULL) {
        free(s);
        return NULL; // элемент не найден в дереве
    }
    // удаление узла
    struct sgt_node *node = *p;
    if (node->left == NULL && node->right == NULL) {
        *p = NULL;
    } else if (node->left == NULL) {
        *p = node->right;
    } else if (node->right == NULL) {
        *p = node->left;
    } else {
        struct sgt_node *max_node = find_max_node(&(node->left));
        node->value = max_node->value;
        p = &(node->left);
        while (*p != max_node) {
            (*p)->size--;
            p = &((*p)->right);
            }
            *p = max_node->left;
    }
    free(node);
    // обновление размера всех узлов на пути от корня до удаленного элемента
    while (s->top != NULL) {
        struct sgt_node *node = stack_pop(s);
        node->size--;
        if (!is_balanced(node, alpha)) {
            rebuild(p, node->size);
        }
        p = &(node->right);
    }
    free(s);
    return *root;
}

void print_tree(struct sgt_node *root) {
    struct sgt_node *stack[MAX_TREE_HEIGHT];
    int top = 0;
    struct sgt_node *node = root;
    while (node != NULL || top > 0) {
        while (node != NULL) {
            stack[top++] = node;
            node = node->left;
        }
        node = stack[--top];
        printf("%d ", node->value);
        node = node->right;
    }
    printf("\n");
}


int main() {
    struct sgt_node *root = NULL;
    int alpha = 1;
    int values[] = {5, 3, 8, 1, 4, 7, 9, 2, 6};
    int n = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < n; i++) {
        add(&root, values[i], alpha);
        printf("Added %d: ", values[i]);
        print_tree(root);
    }
    delete(&root, 4, alpha);
    printf("Deleted 4: ");
    print_tree(root);
    delete(&root, 5, alpha);
    printf("Deleted 5: ");
    print_tree(root);
    delete(&root, 8, alpha);
    printf("Deleted 8: ");
    print_tree(root);
    return 0;
}



