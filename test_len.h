#ifndef TEST_LEN_H
#define TEST_LEN_H

#include <stdint.h>

#include "hasht.h"
#include "iostr.h"

struct HashTableLenTest
{
    HashTable  *hasht;

    TextInfo    text;
    const char *input_filename;

    const char *hash_fun_name;
    uint32_t   *result;
};

#define HashTableTestExec(test, hash_fun) HashTableTestExec_(test, hash_fun, #hash_fun)

void HashTableTestCtor  (HashTableLenTest *test, HashTable *hasht, const char *input_filename);
void HashTableTestDtor  (HashTableLenTest *test);

void HashTableTestExec_ (HashTableLenTest *test, HashFunction hash_fun, const char *hash_fun_name);

void HashTableTestSaveResults (HashTableLenTest *test);

#endif  // TEST_LEN_H
