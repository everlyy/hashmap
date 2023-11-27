#include "hashmap.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Bucket* find(const HashMap* hm, const void* key) {
    uint32_t h = hm->hash(key) % hm->capacity;

    Bucket* b = &hm->buckets[h];

    for(size_t i = 0; i < hm->capacity && b->occupied && !hm->compare_key(b->item.key, key); i++) {
        printf("Collision of ");
        hm->print_key(key);
        printf(" and ");
        hm->print_key(b->item.key);
        printf(" - hash=0x%08X - i=%zu\n", h, i);

        h = (h + 1) % hm->capacity;
        b = &hm->buckets[h];
    }

    if(b->occupied && !hm->compare_key(b->item.key, key))
        assert(!"Table overflow!");

    return b;
}

HashMap hashmap_create(size_t capacity, hashmap_compare_key compare_key, hashmap_hash hash, hashmap_print_key print_key, hashmap_print_value print_value) {
    HashMap hm = {
        .buckets = malloc(sizeof(*hm.buckets) * capacity),
        .capacity = capacity,
        .compare_key = compare_key,
        .hash = hash,
        .print_key = print_key,
        .print_value = print_value
    };

    memset(hm.buckets, 0, sizeof(*hm.buckets) * capacity);
    return hm;
}

void hashmap_free(HashMap* hm) {
    free(hm->buckets);
}

void hashmap_set(HashMap* hm, const void* key, void* value) {
    Bucket* bucket = find(hm, key);
    assert(bucket != NULL);

    bucket->item.key = key;
    bucket->item.value = value;
    bucket->occupied = true;
}

bool hashmap_get(const HashMap* hm, const void* key, void** out) {
    Bucket* bucket = find(hm, key);
    if(!bucket)
        return false;

    *out = bucket->item.value;
    return true;
}

void hashmap_delete(HashMap* hm, const void* key) {
    Bucket* bucket = find(hm, key);
    assert(bucket != NULL);

    bucket->occupied = false;
}

void hashmap_dump(const HashMap* hm) {
    printf("HashMap @ %p (capacity=%ld):\n", (void*)hm, hm->capacity);
    for(size_t i = 0; i < hm->capacity; i++) {
        const Bucket* b = &hm->buckets[i];
        if(!b->occupied)
            continue;

        printf("  #%03zu -> (", i);
        hm->print_key(b->item.key);
        printf(", ");
        hm->print_value(b->item.value);
        printf(")\n");
    }
}
