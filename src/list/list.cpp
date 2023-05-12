#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "buf_list.h"
#include "general.h"
#include "list.h"

void ListCtor(List *lst, BufferList *free_buf)
{
    ASSERT(lst        != NULL);
    ASSERT(free_buf   != NULL);

    lst->free_buf   = free_buf;
    lst->dummy_head = BufferListPop(free_buf);

    lst->free_buf->buf[lst->dummy_head] =
        {
            .val  = NULL,
            .next = lst->dummy_head,
            .prev = lst->dummy_head
        };

    lst->size = 0;
}

void ListDtor(List *lst)
{
    ASSERT(lst != NULL);

    BufferListDtor(lst->free_buf);

    lst->free_buf   = NULL;
    lst->dummy_head = -1;
    lst->size       =  0;
}

int32_t ListInsertBefore(List *lst, const char *val, int32_t anch)
{
    ASSERT(lst != NULL);
    ASSERT(val != NULL);

    int32_t npos = BufferListPop(lst->free_buf);

    int32_t anch_prev = lst->free_buf->buf[anch].prev;

    lst->free_buf->buf[npos] = 
        {
            .val  = val,
            .next = anch,
            .prev = anch_prev
        };

    lst->free_buf->buf[anch_prev].next = npos;
    lst->free_buf->buf[anch     ].prev = npos;
    
    ++lst->size;

    return npos;
}

int32_t ListInsertAfter(List *lst, const char *val, int32_t anch)
{
    return ListInsertBefore(lst, val, lst->free_buf->buf[anch].next);
}

void ListErase(List *lst, int32_t anch)
{
    ASSERT(lst  != NULL);

    int32_t prev_anch = lst->free_buf->buf[anch].prev,
            next_anch = lst->free_buf->buf[anch].next;

    lst->free_buf->buf[prev_anch].next = next_anch;
    lst->free_buf->buf[next_anch].prev = prev_anch;

    BufferListAdd(lst->free_buf, anch);

    --lst->size;
}

int32_t ListPushBack (List *lst, const char *val)
{
    return ListInsertBefore(lst, val, lst->dummy_head);
}

int32_t ListPushFront(List *lst, const char *val)
{
    return ListInsertAfter (lst, val, lst->dummy_head);
}

void ListPopBack(List *lst)
{
    ListErase(lst, ListGetTail(lst));
}

void ListPopFront(List *lst)
{
    ListErase(lst, ListGetHead(lst));
}

int32_t ListGetHead(List *lst)
{
    ASSERT(lst != NULL);
    return lst->free_buf->buf[lst->dummy_head].next;
}

int32_t ListGetTail(List *lst)
{
    ASSERT(lst != NULL);
    return lst->free_buf->buf[lst->dummy_head].prev;
}

uint32_t ListGetSize(List *lst)
{
    ASSERT(lst != NULL);
    return lst->size;
}

