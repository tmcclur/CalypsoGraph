#include "avltree.h"

void pass(char *s) {
    printf("%s", s);
    printf(": ");
    printf("\x1b[32mPASSED\x1b[0m\n");
}

void fail(char *s) {
    printf("%s", s);
    printf(": ");
    printf("\x1b[31mFAILED\x1b[0m\n");
}

void test(int (*f)(), char *s) {
    if (f())
        pass(s);
    else
        fail(s);
}

int insertion_search() {
    int a = 23;
    node_t *root = new_avl_node(32, &a);
    insert(root, 32, &a);
    return search(root, 32)->key == 32;
}

int insert_3_things() {
    int a = 23;
    int b = 93;
    int c = 92;
    node_t *root = new_avl_node(32, &a);
    insert(root, 43, &b);
    insert(root, 9432, &c);
    int bool = search(root, 32)->key == 32;
    bool &= search(root, 43)->key == 43;
    bool &= search(root, 9432)->key == 9432;
    bool &= *((int *)search(root, 32)->val) == 23;
    bool &= *((int *)search(root, 43)->val) == 93;
    bool &= *((int *)search(root, 9432)->val) == 92;
    return bool;
}

int main() {
    test(insertion_search, "insertion search");
    test(insert_3_things, "insert 3 things");

    return 0;
}
