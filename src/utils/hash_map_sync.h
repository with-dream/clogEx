//
// Created by ms on 2022/8/14.
//

#ifndef LOGEX_HASH_MAP_H
#define LOGEX_HASH_MAP_H

#include "type.h"

#define KEY_TYPE_CHAR 0

#define DEFAULT_INITIAL_CAPACITY 16
#define DEFAULT_LOAD_FACTOR 0.75f

typedef enum {
    free_key, free_value, free_node
} free_type;

typedef struct _node {
    uint hash;
    void *key;
    void *value;
    struct _node *next;
} node;

typedef uint (*key_hash)(void *);

typedef bool (*key_equals)(void *k1, void *k2);

typedef bool (*free_callback)(node *n, free_type type);

typedef struct {
    uint size;
    uint cap;
    float factor;
    uint threshold;
    node **table;
    key_hash hash;
    key_equals equals;
    free_callback free_cb;
} hash_map;

hash_map *hash_map_init(uint capacity, float factor, key_hash hash, key_equals equals, free_callback free_cb);

void hash_map_release(hash_map *);

void *hash_map_put(hash_map *, void *key1, void *value, bool free_enable);

void *hash_map_put_absent(hash_map *, void *key1, void *value, bool free_enable);

void *hash_map_get(hash_map *, void *key1);

void *hash_map_remove(hash_map *, void *key1, bool free_enable);

void hash_map_clear(hash_map *);

uint hash_map_size(hash_map *);

void **hash_map_keys(hash_map *);

void **hash_map_values(hash_map *);

bool hash_map_contains_key(hash_map *, void *key1);

void hash_map_debug(hash_map *map);

#endif //LOGEX_HASH_MAP_H
