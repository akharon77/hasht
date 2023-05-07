#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "buf_list.h"
#include "list.h"

void ListCtor(List       *lst,
              Node       *dummy_head,
              BufferList *free_buf)
{
    ASSERT(lst        != NULL);
    ASSERT(dummy_head != NULL);
    ASSERT(free_buf   != NULL);

    *dummy_head =
        {
            .val  = NULL,
            .next = dummy_head,
            .prev = dummy_head
        };

    lst->size = 0;

    lst->dummy_head = dummy_head;
    lst->free_buf   = free_buf;
}

void ListDtor(List *lst)
{
    ASSERT(lst != NULL);

    BufferListDtor(lst->free_buf);

    *lst->dummy_head =
        {
            .val  = NULL,
            .next = NULL,
            .prev = NULL
        };

    lst->free_buf   = NULL;
    lst->dummy_head = NULL;
    lst->size = 0;
}

Node* ListInsertBefore(List *lst, const char *val, Node *anch)
{
    ASSERT(lst  != NULL);
    ASSERT(anch != NULL);

    Node *npos = BufferListPop(lst->free_buf);

    Node *anch_prev = anch->prev;

    *npos = 
        {
            .val  = val,
            .next = anch,
            .prev = anch_prev
        };

    anch_prev->next = npos;
    anch     ->prev = npos;
    
    ++lst->size;

    return npos;
}

Node* ListInsertAfter(List *lst, const char *val, Node *anch)
{
    return ListInsertBefore(lst, val, anch->next);
}

void ListErase(List *lst, Node *anch)
{
    ASSERT(lst  != NULL);
    ASSERT(anch != NULL);

    Node *prev_anch = anch->prev,
         *next_anch = anch->next;

    prev_anch->next = next_anch;
    next_anch->prev = prev_anch;

    BufferListAdd(lst->free_buf, anch);

    --lst->size;
}

Node* ListPushBack (List *lst, const char *val)
{
    return ListInsertBefore(lst, val, lst->dummy_head);
}

Node* ListPushFront(List *lst, const char *val)
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

Node* ListGetHead(List *lst)
{
    ASSERT(lst != NULL);
    return lst->dummy_head->next;
}

Node* ListGetTail(List *lst)
{
    ASSERT(lst != NULL);
    return lst->dummy_head->prev;
}

uint32_t ListGetSize(List *lst)
{
    ASSERT(lst != NULL);
    return lst->size;
}

