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

#define HashTableLenTestExec(test, hash_fun) HashTableLenTestExec_(test, hash_fun, #hash_fun)
#define HashTableLenTestFast(test, fun_name)      \
do                                                \
{                                                 \
    HashTableLenTestExec(test, hash_ ## fun_name); \
    HashTableLenTestSaveResults(test);            \
}                                                 \
while (0)

void HashTableLenTestCtor  (HashTableLenTest *test, HashTable *hasht, const char *input_filename);
void HashTableLenTestDtor  (HashTableLenTest *test);

void HashTableLenTestExec_ (HashTableLenTest *test, HashFunction hash_fun, const char *hash_fun_name);

void HashTableLenTestSaveResults (HashTableLenTest *test);

#endif  // TEST_LEN_H
