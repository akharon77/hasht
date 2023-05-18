#ifndef TEST_SPEED_H
#define TEST_SPEED_H

#include <stdint.h>

#include "hasht/hasht.h"
#include "iostr/iostr.h"
#include "test/config.h"

#define BASE_ASSETS_DATA_SPEED_HASH_FUNS_PATH "assets/data/hash_funs/speed/"

struct HashTableSpeedTest
{
    HashTable  *hasht;

    TextInfo    text;
    const char *input_filename;

    const char *hash_fun_name;
    double      result;
};

#define HashTableSpeedTestExec(test, hash_fun, cnt) HashTableSpeedTestExec_(test, hash_fun, #hash_fun, cnt)
#define HashTableSpeedTestFast(test, fun_name)                \
do                                                            \
{                                                             \
    HashTableSpeedTestExec(test, hash_ ## fun_name, LAB_CNT); \
    HashTableSpeedTestSaveResults(test);                      \
}                                                             \
while (0)

void HashTableSpeedTestCtor  (HashTableSpeedTest *test, HashTable *hasht, const char *input_filename);
void HashTableSpeedTestDtor  (HashTableSpeedTest *test);

void HashTableSpeedTestExec_ (HashTableSpeedTest *test, HashFunction hash_fun, const char *hash_fun_name, uint32_t cnt);

void HashTableSpeedTestSaveResults (HashTableSpeedTest *test);

#endif  // TEST_SPEED_H
