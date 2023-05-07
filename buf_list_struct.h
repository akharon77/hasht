#ifndef BUF_LIST_STRUCT_H
#define BUF_LIST_STRUCT_H

#include <stdint.h>

#include "node_struct.h"

struct BufferList
{
    uint32_t size;
    uint32_t cap;

    Node    *head;
    Node    *tail;
    Node    *buf;
};

#endif  // BUF_LIST_STRUCT_H
