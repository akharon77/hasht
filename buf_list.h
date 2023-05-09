#ifndef BUF_LIST_H
#define BUF_LIST_H

#include <unistd.h>

#include "buf_list_struct.h"

void    BufferListCtor    (BufferList *lst, uint32_t cap);
void    BufferListDtor    (BufferList *lst);

void    BufferListAdd     (BufferList *lst, int32_t  anch);
int32_t BufferListPop     (BufferList *lst);

void    BufferListRealloc (BufferList *lst, uint32_t new_cap);

#endif  // BUF_LIST_H

