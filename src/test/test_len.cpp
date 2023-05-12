#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#include "general.h"
#include "test_len.h"

void HashTableLenTestCtor(HashTableLenTest *test, HashTable *hasht, const char *input_filename)
{
    ASSERT (test  != NULL);
    ASSERT (hasht != NULL);

    ASSERT (input_filename != NULL);

    test->hasht          = hasht;
    test->input_filename = input_filename;

    test->hash_fun_name  = NULL;
    test->result         = (uint32_t*) calloc(hasht->size, sizeof(uint32_t));

    TextInfoCtor(&test->text);

    int32_t err = 0;
    TextInfoInputFromFile(&test->text, input_filename, &err);
    ASSERT(err == 0);

    TextInfoMarkout(&test->text, &err);
    ASSERT(err == 0);
}

void HashTableLenTestDtor(HashTableLenTest *test)
{
    ASSERT(test  != NULL);

    test->hasht          = NULL;
    test->input_filename = NULL;

    test->hash_fun_name  = NULL;

    free(test->result);
    test->result         = NULL;

    TextInfoDtor(&test->text);
}

void HashTableLenTestExec_(HashTableLenTest *test, HashFunction hash_fun, const char *hash_fun_name)
{
    ASSERT (test          != NULL);
    ASSERT (hash_fun      != NULL);
    ASSERT (hash_fun_name != NULL);

    test->hash_fun_name   = hash_fun_name;

    test->hasht->hash_fun = hash_fun;

    for (uint32_t i = 0; i < test->text.words_cnt; ++i)
        HashTableInsert(test->hasht, test->text.words[i]);

    for (uint32_t i = 0; i < test->hasht->size; ++i)
        test->result[i] = test->hasht->lists[i].size;

    HashTableClear(test->hasht);
}

void HashTableLenTestSaveResults(HashTableLenTest *test)
{
    ASSERT(test != NULL);

    char output_filename[64] = "";
    ASSERT(strlen(test->hash_fun_name) + sizeof(".dat") < 64);

    strcpy(output_filename, test->hash_fun_name);
    strcat(output_filename, ".dat");

    int32_t fd = creat(output_filename, S_IRWXU);
    ASSERT(fd != -1);

    dprintf(fd, "#%10s %10s\n", "id", "len");
    for (uint32_t i = 0; i < test->hasht->size; ++i)
        dprintf(fd, "%10u %10u\n", i, test->result[i]);

    close(fd);
}

