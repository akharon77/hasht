#ifndef HASHT_H
#define HASHT_H

#include "hasht_struct.h"

void    HashTableCtor   (HashTable *hasht, uint32_t size, HashFunction hash_fun);
void    HashTableDtor   (HashTable *hasht);

void    HashTableInsert (HashTable *hasht, const char *str);

int32_t HashTableFind   (HashTable *hasht, const char *str, uint32_t *ind);

void    HashTableClear  (HashTable *hasht);

#endif  // HASHT_H

