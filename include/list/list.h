#ifndef LIST_H
#define LIST_H

#include <stdint.h>

#include "buf_list.h"
#include "list_debug.h"
#include "list_struct.h"

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

int32_t     ListGetHead      (List *lst);
int32_t     ListGetTail      (List *lst);
     
#endif  // LIST_H
 
