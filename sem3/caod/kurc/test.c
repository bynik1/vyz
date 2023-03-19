void sgt_insert_value(struct sgt_tree *tree, int value) {
    sgt_insert(&tree->root, value);
    tree->size++;
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