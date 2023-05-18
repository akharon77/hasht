#ifndef GENERAL_H
#define GENERAL_H

// ON_DEBUG
// (
// #include <fcntl.h>
// )

#define ASSERT(expr)                                        \
ON_DEBUG                                                    \
(                                                           \
do {                                                        \
    if (!(expr))                                            \
        dprintf(2,                                          \
                "Assertion failed. Expression: " #expr "\n" \
                "File: %s, line: %d\n"                      \
                "Function: %s\n",                           \
                __FILE__, __LINE__,                         \
                __PRETTY_FUNCTION__);                       \
} while(0)                                                  \
)

#ifdef _DEBUG
    #define ON_DEBUG(...) __VA_ARGS__
#else
    #define ON_DEBUG(...)
#endif

#endif  // GENERAL_H
