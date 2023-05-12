#ifndef HASHT_STRUCT_H
#define HASHT_STRUCT_H

#include "hasht/hash_functions.h"
#include "list/list.h"

struct HashTable
{
    uint32_t      size;

    List         *lists;
    BufferList    free_buf;

    HashFunction  hash_fun;
};

#endif  // HASHT_STRUCT_H

