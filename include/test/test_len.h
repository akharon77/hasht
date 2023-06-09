#ifndef TEST_LEN_H
#define TEST_LEN_H

#include <stdint.h>

#include "hasht/hasht.h"
#include "iostr/iostr.h"
#include "test/config.h"

struct HashTableLenTest
{
    HashTable  *hasht;

    TextInfo    text;
    const char *input_filename;

    const char *hash_fun_name;
    uint32_t   *result;
};

#define HashTableLenTestExec(test, hash_fun, size) HashTableLenTestExec_(test, hash_fun, #hash_fun, size)
#define HashTableLenTestFast(test, fun_name)                  \
do                                                            \
{                                                             \
    HashTableLenTestExec(test, hash_ ## fun_name, LAB_SIZE1); \
    HashTableLenTestSaveResults(test);                        \
    HashTableLenTestExec(test, hash_ ## fun_name, LAB_SIZE2); \
    HashTableLenTestSaveResults(test);                        \
    HashTableLenTestExec(test, hash_ ## fun_name, LAB_SIZE3); \
    HashTableLenTestSaveResults(test);                        \
    HashTableLenTestExec(test, hash_ ## fun_name, LAB_SIZE4); \
    HashTableLenTestSaveResults(test);                        \
}                                                             \
while (0)

void HashTableLenTestCtor  (HashTableLenTest *test, HashTable *hasht, const char *input_filename);
void HashTableLenTestDtor  (HashTableLenTest *test);

void HashTableLenTestExec_ (HashTableLenTest *test, HashFunction hash_fun, const char *hash_fun_name, uint32_t size);

void HashTableLenTestSaveResults (HashTableLenTest *test);

#endif  // TEST_LEN_H
