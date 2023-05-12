#ifndef IOSTR_DEBUG_H
#define IOSTR_DEBUG_H

#include <stdio.h>

#define LOG_ERROR(errorID)              \
do {                                    \
    if ((errorID) != NO_ERROR)          \
        fprintf(stderr,                 \
                "%s\n"                  \
                "File: %s, line: %d\n", \
                ERRORS[(errorID)],      \
                __FILE__, __LINE__);    \
} while (0)

#define RET_ERR(expr, errPtr, errId) \
do {                                 \
    if (expr)                        \
    {                                \
        *(errPtr) = (errId);         \
        return;                      \
    }                                \
} while (0)

enum ERRORS
{
    NO_ERROR,
    FILE_READING_ERROR,
    FILE_OPEN_ERROR,
    FILE_STATS_READING_ERROR,
    FILE_NAME_ERROR,
    FILE_CONTENT_MALLOC_ERROR,
    TEXT_MALLOC_ERROR,
    LINES_MALLOC_ERROR,
    TEXT_MARKOUT_NULL_ERROR,
    N_ERRORS
};

struct ErrorTag
{
    const char *description;
    int         errorId;
};

void InitErrorTags();

#endif  //IOSTR_DEBUG_H

