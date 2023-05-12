#ifndef LIST_DEBUG_H
#define LIST_DEBUG_H

#include <stdio.h>
#include "list_struct.h"

#define ListOk(lst)                                                          \
do                                                                           \
{                                                                            \
    int32_t fd_dump = ListGetLogFd();                                        \
    dprintf(fd_dump, "<h2>ListOk() is called from function: %s, file: %s(%d)</h2>", \
                      __PRETTY_FUNCTION__, __FILE__, __LINE__);              \
    uint32_t flags = ListStatus(lst);                                        \
    dprintf(fd_dump, "%s\n", ListErrorDesc(flags));                          \
    ASSERT(ListStatus(lst) == 0);                                            \
}                                                                            \
while(0)

struct DebugInfo
{
    int32_t     line;
    const char *name;
    const char *funcname;
    const char *filename;
};

extern const char * const COLOR_NODE_EMPTY;
extern const char * const COLOR_NODE_FILLED;
extern const char * const COLOR_NODE_ROOT;
extern const char * const COLOR_NODE_INFO_HEAD;
extern const char * const COLOR_NODE_INFO_TAIL;
extern const char * const COLOR_EDGE_FILLED;
extern const char * const COLOR_EDGE_NEXT;
extern const char * const COLOR_EDGE_PREV;
extern const char * const COLOR_EDGE_EMPTY;

extern const int32_t EDGE_BASE_WEIGHT;
 
extern const uint32_t ERROR_SIZE_NEG;
extern const uint32_t ERROR_BUF_BAD_PTR;
extern const uint32_t ERROR_COMM_VIOL;
extern const uint32_t ERROR_ELEMS;
extern const uint32_t ERROR_FREE_INCORR;
extern const uint32_t ERROR_FREE_VIOL;
extern const uint32_t ERROR_CAP_NEG;
extern const uint32_t ERROR_SIZE_MISMATCH;
extern const uint32_t ERROR_CAP_MISMATCH;
extern const uint32_t ERROR_POISIONED_STRUCT;

extern const int32_t  DUMP_NODE_HEAD;
extern const int32_t  DUMP_NODE_TAIL;
extern const int32_t  DUMP_NODE_FREE;
 
extern const uint64_t POISON;
extern const double   POISIONED_PERC;

 void        ListPrint               (List *lst);
 
// uint32_t    ListStatus              (List *lst);
// const char* ListErrorDesc           (uint32_t flags);
 
void        ListDump                (List *lst, int32_t fd_dump);
void        ListDumpGraph           (List *lst, int32_t fd_dump);

void        ListDumpGraphInfoNode   (int32_t anch, const char *name, const char *fillcolor, int32_t fd_dump);

void        ListDumpGraphNode       (List *lst, int32_t anch, const char *fillcolor, int32_t fd_dump);

void        ListDumpGraphNodeRecord (List *lst, int32_t anch, const char *fillcolor, int32_t fd_dump);
void        ListDumpGraphNodeEdges  (List *lst, int32_t anch, int32_t fd_dump);

void        ListDumpGraphEdge       (int32_t anch1, int32_t anch2, const char *color, int32_t weight, int32_t fd_dump);
 
// bool        isBadPtr                (void *ptr);
// int32_t     min                     (int32_t a, int32_t b);
// int32_t     max                     (int32_t a, int32_t b);

#endif  // LIST_DEBUG_H

