//
// Created by ms on 2022/8/15.
//

#ifndef LOGEX_HASH_MAP_STR_H
#define LOGEX_HASH_MAP_STR_H

#include "hash_map.h"

typedef struct {
    void *value;
    short type;
    bool is_free;
} value_t;

hash_map *hash_map_init_str(uint capacity, float factor);

value_t *hash_map_put_str(hash_map *map, char *k, void *value, short value_type, bool v_free);

value_t *hash_map_put_str_v(hash_map *map, char *k, void *value, bool v_free);

value_t *hash_map_put_absent_str(hash_map *map, char *k, void *value, short value_type, bool v_free);

value_t *hash_map_get_str(hash_map *, char *key);

value_t *hash_map_remove_str(hash_map *, char *key, bool free_value);

char **hash_map_keys_str(hash_map *);

bool hash_map_contains_key_str(hash_map *, char *key);

#endif //LOGEX_HASH_MAP_STR_H
