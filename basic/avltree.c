#include "avltree.h"

static inline int64_t max(int64_t a, int64_t b) { return a > b ? a : b; }

static inline int64_t height(node_t *node) {
    if (node)
        return node->height;
    else
        return -1;
}

static inline void setheight(node_t *node, int64_t balance) {
    node->height = balance;
}

// returns new root of subtree
static inline node_t *lrotate(node_t *root) {
    node_t *rchild = root->right;
    root->right = rchild->left;
    rchild->left = root;
    setheight(root, max(height(root->left), height(root->right)) + 1);
    setheight(rchild, max(height(rchild->left), height(rchild->right)) + 1);
    return rchild;
}

// returns new root of subtree
static inline node_t *rrotate(node_t *root) {
    node_t *lchild = root->left;
    root->left = lchild->right;
    lchild->right = root;
    setheight(root, max(height(root->left), height(root->right)) + 1);
    setheight(lchild, max(height(lchild->left), height(lchild->right)) + 1);
    return lchild;
}

node_t *search(node_t *node, uint64_t key) {
    if (node->key > key) {
        if (node->left) return search(node->left, key);
        return NULL;
    } else if (node->key < key) {
        if (node->right) return search(node->right, key);
        return NULL;
    } else if (node->key == key) {
        return node;
    }
    return NULL;
}

node_t *new_avl_node(uint64_t key, void *val) {
    node_t *node = malloc(sizeof(node_t));
    node->key = key;
    node->val = val;
    node->height = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// returns the new root
// assumes distinct keys
node_t *insert(node_t *node, uint64_t key, void *val) {
    if (node == NULL)
        return new_avl_node(key, val);
    else if (key < node->key)
        node->left = insert(node->left, key, val);
    else if (key > node->key)
        node->right = insert(node->right, key, val);
    else  // equal case
        return node;

    setheight(node, height(node->left) - height(node->right));
    if (height(node) > 1) {
        if (height(node->left->right) > height(node->left->left))
            node->left = lrotate(node->left);
        return rrotate(node);
    } else if (height(node) < -1) {
        if (height(node->right->left) > height(node->right->left))
            node->right = rrotate(node->right);
        return lrotate(node);
    } else {
        return node;
    }
}
// int main() { return 0; }
