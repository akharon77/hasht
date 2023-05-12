#ifndef LIST_STRUCT_H
#define LIST_STRUCT_H

#include <stdint.h>

#include "list/buf_list_struct.h"

struct List
{
    uint32_t    size;

    int32_t     dummy_head;
    BufferList *free_buf;
};

#endif  // LIST_STRUCT_H
