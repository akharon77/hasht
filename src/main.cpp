#include "test/test_len.h"
#include "test/test_speed.h"

#define TEXTS_DIR "assets/data/"

int main(int argc, const char *argv[])
{
    HashTable hasht = {};
    HashTableCtor(&hasht, LAB_SIZE, hash_vice);

#ifdef _LEN_TEST
    HashTableLenTest test = {};
    HashTableLenTestCtor(&test, &hasht, TEXTS_DIR "words.txt");

    HashTableLenTestFast(&test, const);
    HashTableLenTestFast(&test, first_char);
    HashTableLenTestFast(&test, strlen);
    HashTableLenTestFast(&test, sum_char);
    HashTableLenTestFast(&test, rotr);
    HashTableLenTestFast(&test, rotl);
    HashTableLenTestFast(&test, crc32);

    HashTableLenTestDtor(&test);
#else
#ifdef _SPEED_TEST
    HashTableSpeedTest test = {};
    HashTableSpeedTestCtor(&test, &hasht, TEXTS_DIR "words.txt");

    HashTableSpeedTestFast(&test, crc32);

    HashTableSpeedTestDtor(&test);
#endif
#endif

    HashTableDtor(&hasht);
    return 0;
}
