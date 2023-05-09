#ifndef HASHT_STRUCT_H
#define HASHT_STRUCT_H

#include "hash_functions.h"
#include "list.h"

struct HashTable
{
    uint32_t      size;

    List         *lists;
    BufferList    free_buf;

    HashFunction  hash_fun;
};

#endif  // HASHT_STRUCT_H

