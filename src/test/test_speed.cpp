#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "general.h"
#include "test/test_speed.h"

void HashTableSpeedTestCtor(HashTableSpeedTest *test, HashTable *hasht, const char *input_filename)
{
    ASSERT (test  != NULL);
    ASSERT (hasht != NULL);

    ASSERT (input_filename != NULL);

    test->hasht          = hasht;
    test->input_filename = input_filename;

    test->hash_fun_name  = NULL;
    test->result         = NAN;

    TextInfoCtor(&test->text);

    int32_t err = 0;
    TextInfoInputFromFile(&test->text, input_filename, &err);
    ASSERT(err == 0);

    TextInfoMarkout(&test->text, &err);
    ASSERT(err == 0);
}

void HashTableSpeedTestDtor(HashTableSpeedTest *test)
{
    ASSERT(test  != NULL);

    test->hasht          = NULL;
    test->input_filename = NULL;

    test->hash_fun_name  = NULL;

    test->result         = NAN;

    TextInfoDtor(&test->text);
}

void HashTableSpeedTestExec_(HashTableSpeedTest *test, HashFunction hash_fun, const char *hash_fun_name, uint32_t cnt)
{
    ASSERT (test          != NULL);
    ASSERT (hash_fun      != NULL);
    ASSERT (hash_fun_name != NULL);

    HashTableDtor (test->hasht);
    HashTableCtor (test->hasht, 1, hash_fun);

    test->hash_fun_name   = hash_fun_name;

    for (uint32_t i = 0; i < test->text.words_cnt; ++i)
        HashTableInsert(test->hasht, test->text.words[i]);

    clock_t begin = clock();

    uint32_t ind = 0;
    for (uint32_t i = 0; i < cnt; ++i)
    {
        const char *next_word = test->text.words[rand() % test->text.words_cnt];
        HashTableFind(test->hasht, next_word, &ind);
    }

    clock_t end = clock();

    test->result = (double) (end - begin) / CLOCKS_PER_SEC;
}

void HashTableSpeedTestSaveResults(HashTableSpeedTest *test)
{
    ASSERT(test != NULL);

    char output_filename[256] = BASE_ASSETS_DATA_SPEED_HASH_FUNS_PATH;
    ASSERT(strlen(BASE_ASSETS_DATA_SPEED_HASH_FUNS_PATH) + strlen(test->hash_fun_name) + sizeof(".csv") < 256);

    strcat(output_filename, test->hash_fun_name);
    strcat(output_filename, ".csv");

    int32_t fd = open(output_filename, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
    ASSERT(fd != -1);

    dprintf(fd, "%lf;", test->result * 1000);

    close(fd);
}


