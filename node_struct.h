#ifndef NODE_STRUCT_H
#define NODE_STRUCT_H

#include <stdint.h>

struct Node
{
    const char *val;

    Node *next;
    Node *prev;
};

#endif  // NODE_STRUCT_H
