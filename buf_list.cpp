#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "buf_list.h"
#include "list_debug.h"

void BufferListCtor(BufferList *lst, uint32_t size)
{
    ASSERT(lst  != NULL);

    lst->size = size;
    lst->cap  = size;

    lst->buf  = (Node*) calloc(size, sizeof(Node));

    ASSERT(lst->buf != NULL);

    lst->head = lst->buf;
    lst->tail = lst->buf + size - 1;

    uint32_t ind = 0;
    for (Node *anch = lst->buf; ind < size; ++ind, ++anch)
        *anch = 
            {
                .val  = -1,
                .next = anch + 1,
                .prev = NULL
            };

    lst->tail->next = NULL;
}

void BufferListDtor(BufferList *lst)
{
    ASSERT(lst != NULL);

    free(lst->buf);

    lst->buf  = NULL;
    lst->size = 0;
    lst->cap  = 0;
}

void BufferListAdd(BufferList *lst, Node *anch)
{
    ASSERT(lst  != NULL);
    ASSERT(anch != NULL);

    anch->next = lst->head;
     lst->head = anch;

    ++lst->size;
}

void BufferListRealloc(BufferList *lst, uint32_t new_cap)
{
    ASSERT(lst != NULL);

    Node *new_buf = (Node*) realloc(lst->buf, new_cap * sizeof(Node));

    ASSERT(new_buf != NULL);
    
    uint32_t ind = lst->size;

    lst->tail->next = new_buf + ind;
    lst->tail       = new_buf + new_cap - 1;

    for (Node *anch = new_buf + lst->size; ind < new_cap; ++ind, ++anch)
        *anch = 
            {
                .val  = -1,
                .next = anch + 1,
                .prev = NULL
            };

    lst->tail->next = NULL;

    lst->buf   = new_buf;
    lst->size += new_cap - lst->cap;
    lst->cap   = new_cap;
}

Node* BufferListPop(BufferList *lst)
{
    ASSERT(lst != NULL);

    if (lst->size == 1)
        BufferListRealloc(lst, lst->cap * 2);

    Node *res = lst->head;
    lst->head = lst->head->next;

    --lst->size;

    return res;
}

