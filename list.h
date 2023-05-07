#ifndef LIST_H
#define LIST_H

#include <stdint.h>

#include "buf_list.h"
#include "list_debug.h"
#include "list_struct.h"

void        ListCtor                (List *lst, BufferList *free_buf);
void        ListDtor                (List *lst);

Node*       ListInsertBefore        (List *lst, const char *val, Node *anch);
Node*       ListInsertAfter         (List *lst, const char *val, Node *anch);
void        ListErase               (List *lst, Node *anch);

Node*       ListPushBack            (List *lst, const char *val);
Node*       ListPushFront           (List *lst, const char *val);

void        ListPopBack             (List *lst);
void        ListPopFront            (List *lst);

uint32_t    ListGetSize             (List *lst);

Node*       ListGetHead             (List *lst);
Node*       ListGetTail             (List *lst);
     
#endif  // LIST_H
 
