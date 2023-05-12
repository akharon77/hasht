#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

#include "general.h"
#include "hasht/hasht_debug.h"

void HashTableDumpLenToFile(HashTable *hasht, const char *filename)
{
    ASSERT(hasht    != NULL);
    ASSERT(filename != NULL);

    int32_t fd = creat(filename, S_IRWXU);
    ASSERT(fd != -1);

    for (uint32_t i = 0; i < hasht->size; ++i)
        dprintf(fd, "%u,", hasht->lists[i].size);

    close(fd);
}
