#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include <stddef.h>
#include <stdint.h>

typedef struct {
    const void* key;
    void* value;
} KVPair;

typedef struct {
    KVPair item;
    bool occupied;
} Bucket;

typedef bool(*hashmap_compare_key)(const void*, const void*);
typedef uint32_t(*hashmap_hash)(const void*);
typedef void(*hashmap_print_key)(const void*);
typedef void(*hashmap_print_value)(const void*);

typedef struct {
    Bucket* buckets;
    size_t capacity;

    hashmap_compare_key compare_key;
    hashmap_hash hash;
    hashmap_print_key print_key;
    hashmap_print_value print_value;
} HashMap;

HashMap hashmap_create(size_t capacity, hashmap_compare_key, hashmap_hash, hashmap_print_key, hashmap_print_value);
void hashmap_free(HashMap*);
void hashmap_set(HashMap*, const void* key, void* value);
bool hashmap_get(const HashMap*, const void* key, void** out);
void hashmap_delete(HashMap*, const void* key);
void hashmap_dump(const HashMap*);

#endif // _HASHMAP_H_
