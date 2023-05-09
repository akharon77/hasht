#include <stdint.h>

#include "hasht.h"
#include "iostr.h"

const uint32_t LAB_SIZE = 277;

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

    TextInfo text = {};
    TextInfoCtor(&text);

    int32_t err = 0;
    TextInfoInputFromFile(&text, "hamlet.txt", &err);

    TextInfoMarkout(&text, &err);
    for (uint32_t i = 0; i < text.words_cnt; ++i)
        HashTableInsert(&hasht, text.words[i]);

    for (uint32_t i = 0; i < hasht.size; ++i)
    {
        printf("List %u size: %u\n", i, hasht.lists[i].size);
    }

    HashTableDtor (&hasht);
    TextInfoDtor  (&text);
    return 0;
}
