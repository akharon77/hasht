#ifndef LIST_H
#define LIST_H

#include <stdint.h>

#include "general.h"
#include "list/buf_list.h"
#include "list/list_debug.h"
#include "list/list_struct.h"

void        ListCtor         (List *lst, BufferList *free_buf);
void        ListDtor         (List *lst);

int32_t     ListInsertBefore (List *lst, const char *val, int32_t anch);
int32_t     ListInsertAfter  (List *lst, const char *val, int32_t anch);
void        ListErase        (List *lst,                  int32_t anch);

int32_t     ListPushBack     (List *lst, const char *val);
int32_t     ListPushFront    (List *lst, const char *val);

void        ListPopBack      (List *lst);
void        ListPopFront     (List *lst);

uint32_t    ListGetSize      (List *lst);

inline int32_t ListGetHead(List *lst)
{
    ASSERT(lst != NULL);
    return lst->free_buf->buf[lst->dummy_head].next;
}

int32_t     ListGetTail      (List *lst);

Node*       ListGet          (List *lst, int32_t anch);
     
#endif  // LIST_H
 
