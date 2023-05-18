#ifndef BUF_LIST_H
#define BUF_LIST_H

#include <unistd.h>

#include "list/buf_list_struct.h"

void    BufferListCtor    (BufferList *lst, uint32_t cap);
void    BufferListDtor    (BufferList *lst);

void    BufferListAdd     (BufferList *lst, int32_t  anch);
int32_t BufferListPop     (BufferList *lst);

Node*   BufferListGet     (BufferList *lst, int32_t anch);

void    BufferListRealloc (BufferList *lst, uint32_t new_cap);

void    BufferListClear   (BufferList *lst);

#endif  // BUF_LIST_H

