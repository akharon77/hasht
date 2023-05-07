#ifndef HASHT_H
#define HASHT_H

#include "list.h"

typedef uint32_t (*HashFunction)(const char *str);

struct HashTable
{
    uint32_t      size;

    Node         *dummy_heads;
    List         *lists;
    BufferList    free_buf;

    HashFunction  hash_fun;
};

void  HashTableCtor   (HashTable *hasht, uint32_t size, HashFunction hash_fun);
void  HashTableDtor   (HashTable *hasht);

void  HashTableInsert (HashTable *hasht, const char *str);

Node* HashTableFind   (const HashTable *hasht, const char *str, uint32_t *ind);

#endif  // HASHT_H

