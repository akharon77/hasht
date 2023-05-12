#include <stdlib.h>
#include <string.h>

#include "general.h"
#include "hasht/hasht.h"

static const int32_t EXP_ELEMS_BY_LIST = 3;

void HashTableCtor(HashTable *hasht, uint32_t size, HashFunction hash_fun)
{
    ASSERT (hasht    != NULL);
    ASSERT (hash_fun != NULL);

    hasht->size = size;

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
    ASSERT (hasht != NULL);
    ASSERT (str   != NULL);

    uint32_t ind = 0;
    int32_t  res = HashTableFind(hasht, str, &ind);

    if (!res)
        ListPushBack(hasht->lists + ind, str);
}

int32_t HashTableFind(HashTable *hasht, const char *str, uint32_t *ind)
{
    ASSERT (hasht != NULL);
    ASSERT (str   != NULL);
    ASSERT (ind   != NULL);

    uint32_t  hash_val = hasht->hash_fun(str);
             *ind      = hash_val % hasht->size;

    ASSERT(0 <= *ind && *ind < hasht->size);

    List *lst = hasht->lists + *ind;

    int32_t head = ListGetHead(lst);

    for (uint32_t i = 0; i < lst->size; ++i)
    {
        if (strcmp(str, lst->free_buf->buf[head].val) == 0)
            return head;

        head = lst->free_buf->buf[head].next;
    }

    return NULL;
}

void HashTableClear(HashTable *hasht)
{
    BufferListClear(&hasht->free_buf);

    for (uint32_t i = 0; i < hasht->size; ++i)
        ListCtor(hasht->lists + i, &hasht->free_buf);
}

