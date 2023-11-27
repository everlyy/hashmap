#include "hashmap.h"

#include <stdio.h>
#include <string.h>

static bool compare_key(const void* _a, const void* _b) {
    const char* a = _a;
    const char* b = _b;
    return strcmp(a, b) == 0;
}

// Very stupid hashing algorithm but it works for this example :-)
static uint32_t hash(const void* _key) {
    const char* key = _key;
    uint32_t h = 0;

    while(*key)
        h += *key++;

    return h;
}

static void print_key(const void* _key) {
    const char* key = _key;
    printf("\"%s\"", key);
}

static void print_value(const void* _value) {
    const int64_t value = (int64_t)_value;
    printf("%ld", value);
}

int main(void) {
    HashMap hm = hashmap_create(
        10,
        compare_key,
        hash,
        print_key,
        print_value
    );

    hashmap_set(&hm, "a", (void*)1);
    hashmap_set(&hm, "b", (void*)2);
    hashmap_set(&hm, "c", (void*)3);
    hashmap_set(&hm, "d", (void*)4);
    hashmap_set(&hm, "e", (void*)5);
    hashmap_set(&hm, "f", (void*)6);
    hashmap_set(&hm, "g", (void*)7);
    hashmap_set(&hm, "h", (void*)8);
    hashmap_set(&hm, "i", (void*)9);
    hashmap_set(&hm, "j", (void*)10);
    hashmap_dump(&hm);

    int64_t value;
    if(hashmap_get(&hm, "b", (void**)&value))
        printf("Value at key \"b\" = %ld\n", value);

    hashmap_free(&hm);
    return 0;
}
