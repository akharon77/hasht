#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "general.h"
#include "list/buf_list.h"
#include "list/list_debug.h"

void BufferListCtor(BufferList *lst, uint32_t cap)
{
    ASSERT(lst  != NULL);

    lst->size = cap;
    lst->cap  = cap;

    lst->buf  = (Node*) calloc(cap, sizeof(Node));

    ASSERT(lst->buf != NULL);

    lst->head = 0;

    BufferListClear(lst);
}

void BufferListDtor(BufferList *lst)
{
    ASSERT(lst != NULL);

    free(lst->buf);

    lst->buf  = NULL;
    lst->size = 0;
    lst->cap  = 0;
}

void BufferListAdd(BufferList *lst, int32_t anch)
{
    ASSERT(lst  != NULL);

    lst->buf[anch].next = lst->head;
    lst->head           = anch;

    ++lst->size;
}

void BufferListRealloc(BufferList *lst, uint32_t new_cap)
{
    ASSERT(lst != NULL);

    Node *new_buf = (Node*) realloc(lst->buf, new_cap * sizeof(Node));

    ASSERT(new_buf != NULL);
    lst->buf = new_buf;
    
    uint32_t ind = lst->cap;

    lst->buf[lst->cap - 1].next = ind;

    while (ind < new_cap)
    {
        lst->buf[ind] = 
            {
                .val  = NULL,
                .next = ind + 1,
                .prev = -1 
            };

        ++ind;
    }

    lst->buf[new_cap - 1].next = -1;

    lst->size += new_cap - lst->cap;
    lst->cap   = new_cap;
}

int32_t BufferListPop(BufferList *lst)
{
    ASSERT(lst != NULL);

    if (lst->size == 1)
        BufferListRealloc(lst, lst->cap * 2);

    int32_t res = lst->head;
    lst->head = lst->buf[lst->head].next;

    --lst->size;

    return res;
}

void BufferListClear(BufferList *lst)
{
    uint32_t cap = lst->cap;

    for (uint32_t ind = 0; ind < cap; ++ind)
        lst->buf[ind] = 
            {
                .val  = NULL,
                .next = ind + 1,
                .prev = -1
            };

    lst->buf[cap - 1].next = -1;
}

