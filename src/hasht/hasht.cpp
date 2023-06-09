#include <immintrin.h>
#include <nmmintrin.h>
#include <stdlib.h>
#include <string.h>

#include "general.h"
#include "hasht/hasht.h"
#include "test/config.h"

static const int32_t  EXP_ELEMS_BY_LIST = 3;

#ifdef _MEASURE
static const uint32_t P_COEFF = 13;
#else
static const uint32_t P_COEFF = 4;
#endif  // _MEASURE

static const uint32_t Q_COEFF = 3;

void HashTableCtor(HashTable *hasht, uint32_t size, HashFunction hash_fun)
{
    ASSERT (hasht    != NULL);
    ASSERT (hash_fun != NULL);

    hasht->size      = size;
    hasht->cnt_elems = 0;

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

    hasht->size      = 0;
    hasht->cnt_elems = 0;
}

void HashTableInsert(HashTable *hasht, const char *str)
{
    ASSERT (hasht != NULL);
    ASSERT (str   != NULL);

    uint32_t ind = 0;
    int32_t  res = HashTableFind(hasht, str, &ind);

    if (res == -1)
    {
        ++hasht->cnt_elems;
#ifdef _SPEED_TEST
        if (hasht->cnt_elems * Q_COEFF >= hasht->size * P_COEFF)
        {
            HashTableRehash(hasht, 2 * hasht->size);
            HashTableInsert(hasht, str);
        }
        else
        {
            ListPushBack(hasht->lists + ind, str);
        }
#else
        ListPushBack(hasht->lists + ind, str);
#endif  // _SPEED_TEST
    }
}

void HashTableErase(HashTable *hasht, const char *str)
{
    ASSERT (hasht != NULL);
    ASSERT (str   != NULL);

    uint32_t ind = 0;
    int32_t  res = HashTableFind(hasht, str, &ind);

    if (res != -1)
    {
        --hasht->cnt_elems;
        ListErase(hasht->lists + ind, res);
    }
}

int32_t HashTableFind(HashTable *hasht, const char *str, uint32_t *ind)
{
    ASSERT (hasht != NULL);
    ASSERT (str   != NULL);
    ASSERT (ind   != NULL);

#if OPT_LVL >= 1
    __m256i str_cpy = _mm256_load_si256((const __m256i*) str);
#endif  // OPT_LVL >= 1

    uint32_t  hash_val = hasht->hash_fun(str);
             *ind      = hash_val % hasht->size;

    ASSERT(0 <= *ind && *ind < hasht->size);

    List *lst = hasht->lists + *ind;

    int32_t curr_node = ListGetHead(lst);

    for (uint32_t i = 0; i < lst->size; ++i)
    {
#if OPT_LVL >= 1
        __m256i str_lst = _mm256_load_si256((const __m256i*) ListGet(lst, curr_node)->val);

        uint16_t cmp_res = _mm256_cmpeq_epi8_mask(str_cpy, str_lst);
        if (!(~cmp_res))
            return curr_node;
#else
        if (strcmp(str, ListGet(lst, curr_node)->val) == 0)
            return curr_node;
#endif  // OPT_LVL >= 1

        curr_node = ListGet(lst, curr_node)->next;
    }

    return -1;
}

void HashTableClear(HashTable *hasht)
{
    BufferListClear(&hasht->free_buf);

    for (uint32_t i = 0; i < hasht->size; ++i)
        ListCtor(hasht->lists + i, &hasht->free_buf);
}

void HashTableRehash(HashTable *hasht, uint32_t size)
{
    ASSERT(size > hasht->size);

    uint32_t prev_hasht_size = hasht->size;
    hasht->size = size;

    ASSERT(hasht->lists != NULL);

    if (prev_hasht_size < size)
    {
        hasht->lists = (List*) realloc(hasht->lists, sizeof(List) * size);

        for (uint32_t i = prev_hasht_size; i < size; ++i)
            ListCtor(hasht->lists + i, &hasht->free_buf);
    }

    uint32_t *len_sizes = (uint32_t*) calloc(prev_hasht_size, sizeof(uint32_t));
    ASSERT(len_sizes != NULL);

    for (uint32_t i = 0; i < prev_hasht_size; ++i)
        len_sizes[i] = hasht->lists[i].size;

    for (uint32_t i = 0; i < prev_hasht_size; ++i)
    {
        List     *lst = hasht->lists + i;
        uint32_t  k   = len_sizes[i];

        while (k--)
        {
            const char *val = ListGet(lst, ListGetHead(lst))->val;

            --hasht->cnt_elems;
            ListPopFront(lst);
            HashTableInsert(hasht, val);
        }
    }

    if (prev_hasht_size > size)
    {
        for (uint32_t i = prev_hasht_size; i < size; ++i)
            ListDtor(hasht->lists + i);

        hasht->lists = (List*) realloc(hasht->lists, sizeof(List) * size);
    }
}

