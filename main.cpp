#include "test_len.h"

const uint32_t LAB_SIZE = 331;

int main()
{
    HashTable hasht = {};
    HashTableCtor(&hasht, LAB_SIZE, hash_vice);

    HashTableLenTest test = {};
    HashTableLenTestCtor(&test, &hasht, "hamlet.txt");

    HashTableLenTestFast(&test, const);
    HashTableLenTestFast(&test, first_char);
    HashTableLenTestFast(&test, strlen);
    HashTableLenTestFast(&test, sum_char);
    HashTableLenTestFast(&test, rotr);
    HashTableLenTestFast(&test, rotl);
    HashTableLenTestFast(&test, crc32);

    return 0;
}
