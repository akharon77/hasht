#ifndef HASHT_STRUCT_H
#define HASHT_STRUCT_H

#include "list.h"

typedef uint32_t (*HashFunction)(const char *str);

struct HashTable
{
    uint32_t      size;

    List         *lists;
    BufferList    free_buf;

    HashFunction  hash_fun;
};

#endif  // HASHT_STRUCT_H

