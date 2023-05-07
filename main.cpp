#include <stdint.h>

#include "hasht.h"

const uint32_t LAB_SIZE = 19;

uint32_t constHash(const char *str)
{
    uint32_t res = 0;

    while (*str)
    {
        res = res * 49 + *str;
        ++str;
    }

    return res;
}

int main()
{
    HashTable hasht = {};
    HashTableCtor(&hasht, LAB_SIZE, constHash);

    const char *arr[] = 
        {
            "abba",
            "abaga",
            "acc",
            "abba",
            "acca",
            "lol"
        };

    for (uint32_t i = 0; i < sizeof(arr) / sizeof(const char*); ++i)
        HashTableInsert(&hasht, arr[i]);

    for (uint32_t i = 0; i < hasht.size; ++i)
    {
        printf("List %d\n", i);
        ListPrint(hasht.lists + i);
    }

    HashTableDtor(&hasht);
    return 0;
}
