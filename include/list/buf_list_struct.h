#ifndef BUF_LIST_STRUCT_H
#define BUF_LIST_STRUCT_H

#include <stdint.h>

#include "node_struct.h"

struct BufferList
{
    uint32_t size;
    uint32_t cap;

    int32_t  head;
    Node    *buf;
};

#endif  // BUF_LIST_STRUCT_H
