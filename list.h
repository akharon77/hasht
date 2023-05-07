#ifndef LIST_H
#define LIST_H

#include <stdint.h>

#include "buf_list.h"
#include "list_debug.h"
#include "list_struct.h"

void        ListCtor                (List       *lst,
                                     Node       *dummy_head,
                                     BufferList *free_buf);

void        ListDtor                (List *lst);

Node*       ListInsertBefore        (List *lst, int32_t val, Node *anch);
Node*       ListInsertAfter         (List *lst, int32_t val, Node *anch);
void        ListErase               (List *lst, Node *anch);

Node*       ListPushBack            (List *lst, int32_t val);
Node*       ListPushFront           (List *lst, int32_t val);

void        ListPopBack             (List *lst);
void        ListPopFront            (List *lst);

uint32_t    ListGetSize             (List *lst);

Node*       ListGetHead             (List *lst);
Node*       ListGetTail             (List *lst);
     
#endif  // LIST_H
 
