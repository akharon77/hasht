#include <stdlib.h>

#include "hasht.h"

const int32_t EXP_ELEMS_BY_LIST = 3;

void HashTableCtor(HashTable *hasht, uint32_t size, HashFunction hash_fun)
{
    ASSERT(hasht    != NULL);
    ASSERT(hash_fun != NULL);

    BufferListCtor(&hasht->free_buf, EXP_ELEMS_BY_LIST * size);

    hasht->dummy_heads = (Node*) calloc(size, sizeof(Node));
    ASSERT(hasht->dummy_heads != NULL);

    hasht->lists = (List*) calloc(size, sizeof(List));
    ASSERT(hasht->lists != NULL);

    for (uint32_t i = 0; i < size; ++i)
        ListCtor(hasht->lists + i, hasht->dummy_heads + i, &hasht->free_buf);

    hasht->hash_fun = hash_fun;
}

void HashTableDtor(HashTable *hasht)
{
    ASSERT(hasht != NULL);

    free(hasht->dummy_heads);

    for (uint32_t i = 0; i < hasht->size; ++i)
        ListDtor(hasht->lists + i);

    free(hasht->lists);

    hasht->dummy_heads = NULL;
    hasht->lists       = NULL;

    BufferListDtor(&hasht->free_buf);

    hasht->hash_fun = NULL;
}

