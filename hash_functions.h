#ifndef HASHT_FUNCTIONS_H
#define HASHT_FUNCTIONS_H

#include <stdint.h>

typedef uint32_t (*HashFunction)(const char *str);

uint32_t hash_const      (const char *str);
uint32_t hash_first_char (const char *str);
uint32_t hash_strlen     (const char *str);
uint32_t hash_sum_char   (const char *str);
uint32_t hash_rotr       (const char *str);
uint32_t hash_rotl       (const char *str);
uint32_t hash_crc32      (const char *str);

#endif  // HASHT_FUNCTIONS_H
