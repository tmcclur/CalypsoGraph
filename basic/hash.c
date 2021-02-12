#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hashString(char *s) {
    int key = atoi(s);

    /* Robert Jenkins' 32 bit Mix Function */
    key += (key << 12);
    key ^= (key >> 22);
    key += (key << 4);
    key ^= (key >> 9);
    key += (key << 10);
    key ^= (key >> 2);
    key += (key << 7);
    key ^= (key >> 12);

    /* Knuth's Multiplicative Method */
    key = (key >> 3) * 2654435761;

    return key % TABLE_SIZE;
}

int hashPut(char *s, void *object) {
    int key = hashString(s);

    Entry *cur = hashTable[key]->head;
    Entry *prev = 0;

    while (cur) {
        if (!strcmp(s, cur->name)) {
            return -1;
        }
        prev = cur;
        cur = cur->next;
    }

    if (!(cur = calloc(sizeof(Entry), 1))) {
        // TODO: handle error
    }

    if (!prev) {
        hashTable[key]->head = cur;
    } else {
        prev->next = cur;
    }

    cur->name = s;
    cur->val = object;

    return 0;
}

void initializeHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (!(hashTable[i] = calloc(sizeof(Bucket), 1))) {
            // TODO: handle error
        }
    }
}

void *hashGet(char *s) {
    int key = hashString(s);

    Entry *cur = hashTable[key]->head;

    while (cur) {
        if (!strcmp(s, cur->name)) {
            return cur->val;
        }
        cur = cur->next;
    }

    return 0;
}
