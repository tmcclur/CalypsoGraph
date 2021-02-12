// implement a hashmap to insert the names of objects into
#define TABLE_SIZE 256

typedef struct HashTableEntry {
    char *name;
    void *val;
    struct HashTableEntry *next;
} Entry;

typedef struct HashTableBucket {
    int size;
    Entry *head;
} Bucket;

Bucket *hashTable[TABLE_SIZE];

void initializeHashTable();

int hashString(char *s);

int hashPut(char *s, void *object);

void *hashGet(char *s);
