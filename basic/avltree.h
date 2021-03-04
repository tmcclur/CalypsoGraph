#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    void *val;
    uint64_t key;
    int64_t height;
    struct node *left;
    struct node *right;
} node_t;

node_t *search(node_t *, uint64_t);
node_t *new_avl_node(uint64_t, void *);
node_t *insert(node_t *, uint64_t, void *);
