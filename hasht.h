#ifndef HASHT_H
#define HASHT_H

#include "hasht_struct.h"

void  HashTableCtor   (HashTable *hasht, uint32_t size, HashFunction hash_fun);
void  HashTableDtor   (HashTable *hasht);

void  HashTableInsert (HashTable *hasht, const char *str);

Node* HashTableFind   (const HashTable *hasht, const char *str, uint32_t *ind);

#endif  // HASHT_H

