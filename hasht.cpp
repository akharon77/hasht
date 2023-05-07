#include <stdlib.h>
#include <string.h>

#include "hasht.h"
#include "general.h"

const int32_t EXP_ELEMS_BY_LIST = 3;

void HashTableCtor(HashTable *hasht, uint32_t size, HashFunction hash_fun)
{
    ASSERT(hasht    != NULL);
    ASSERT(hash_fun != NULL);

    BufferListCtor(&hasht->free_buf, EXP_ELEMS_BY_LIST * size);

    hasht->lists = (List*) calloc(size, sizeof(List));
    ASSERT(hasht->lists != NULL);

    for (uint32_t i = 0; i < size; ++i)
        ListCtor(hasht->lists + i, &hasht->free_buf);

    hasht->hash_fun = hash_fun;
}

void HashTableDtor(HashTable *hasht)
{
    ASSERT(hasht != NULL);

    for (uint32_t i = 0; i < hasht->size; ++i)
        ListDtor(hasht->lists + i);

    free(hasht->lists);
    hasht->lists = NULL;

    BufferListDtor(&hasht->free_buf);

    hasht->hash_fun = NULL;
}

void HashTableInsert(HashTable *hasht, const char *str)
{
    ASSERT(hasht != NULL);
    ASSERT(str   != NULL);

    uint32_t  ind = 0;
    Node     *res = HashTableFind(hasht, str, &ind);

    if (!res)
        ListPushBack(hasht->lists + ind, str);
}

Node* HashTableFind(const HashTable *hasht, const char *str, uint32_t *ind)
{
    ASSERT(hasht != NULL);
    ASSERT(str   != NULL);

    uint32_t  hash_val = hasht->hash_fun(str);
             *ind      = hash_val % hasht->size;

    Node *head = ListGetHead(hasht->lists + *ind);

    for (int32_t i = 0; i < hasht->lists[*ind].size; ++i)
    {
        if (strcmp(str, head->val) == 0)
            return head;

        head = head->next;
    }

    return NULL;
}

