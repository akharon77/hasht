#ifndef LIST_STRUCT_H
#define LIST_STRUCT_H

#include <stdint.h>

#include "buf_list_struct.h"

struct List
{
    uint32_t   size;

    Node       *dummy_head;
    BufferList *free_buf;
};

#endif  // LIST_STRUCT_H
