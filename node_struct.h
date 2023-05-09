#ifndef NODE_STRUCT_H
#define NODE_STRUCT_H

#include <stdint.h>

struct Node
{
    const char *val;

    int32_t next;
    int32_t prev;
};

#endif  // NODE_STRUCT_H
