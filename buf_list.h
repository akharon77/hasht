#ifndef BUF_LIST_H
#define BUF_LIST_H

#include <unistd.h>

#include "buf_list_struct.h"

void  BufferListCtor    (BufferList *lst, uint32_t size);
void  BufferListDtor    (BufferList *lst);

void  BufferListAdd     (BufferList *lst, Node *anch);
Node* BufferListPop     (BufferList *lst);

void  BufferListRealloc (BufferList *lst, uint32_t new_cap);

#endif  // BUF_LIST_H

