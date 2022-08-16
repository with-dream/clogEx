//
// Created by ms on 2022/8/15.
//

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <printf.h>
#include "hash_map_str.h"

#define VALUE_TYPE_CHAR 0

static uint key_hash_str(void *);

static bool key_equals_str(void *k1, void *k2);

static bool free_value_str(node *n, free_type type);

static value_t *create_value(void *value, short type, bool is_free);

static char *cpy_str(const char *src) {
    uint len = strlen(src) + 1;
    char *tmp_key = (char *) malloc(len);
    assert(tmp_key);
    memcpy(tmp_key, src, len);
    return tmp_key;
}

hash_map *hash_map_init_str(uint capacity, float factor) {
    return hash_map_init(capacity, factor, key_hash_str, key_equals_str, free_value_str);
}

value_t *hash_map_put_str(hash_map *map, char *k, void *value, short type, bool is_free) {
    return hash_map_put(map, cpy_str(k), create_value(value, type, is_free), true);
}

value_t *hash_map_put_str_v(hash_map *map, char *k, void *value, bool v_free) {
    return hash_map_put_str(map, k, value, VALUE_TYPE_CHAR, v_free);
}

value_t *hash_map_put_absent_str(hash_map *map, char *k, void *value, short type, bool is_free) {
    return hash_map_put_absent(map, cpy_str(k), create_value(value, type, is_free), true);
}

value_t *hash_map_get_str(hash_map *map, char *k) {
    return hash_map_get(map, k);
}

value_t *hash_map_remove_str(hash_map *map, char *k, bool free_value) {
    return hash_map_remove(map, k, free_value);
}

char **hash_map_keys_str(hash_map *map) {
    assert(map);
    char **res = malloc(sizeof(char **) * map->size);
    uint index = 0;
    for (uint i = 0; i < map->cap; i++) {
        node *n = (node *) (map->table[i]);
        while (n) {
            res[index++] = n->key;
            n = n->next;
        }
    }

    assert(index == map->size);
    return res;
}

bool hash_map_contains_key_str(hash_map *map, char *k) {
    return hash_map_get_str(map, k) != NULL;
}

static uint key_hash_str(void *k) {
    unsigned int h = 5381;
    const char *p = (const char *) k;
    while (*p != '\0')
        h = ((h << 5) + h) + (*p++); /* hash * 33 + c */
    return h;
}

static bool key_equals_str(void *k1, void *k2) {
    if (MAP_DEBUG) {
        printf("key_equals_str k1:%s k2:%s\n", (char *)k1, (char *)k2);
    }
    return k1 == k2 || !strcmp((const char *) k1, (const char *) k2);
}

static void free_single_value(node *n) {
    if (n->value) {
        value_t *vt = (value_t *) n->value;
        if (vt->is_free)
            free(n->value);
    }
}

static bool free_value_str(node *n, free_type type) {
    switch (type) {
        case free_value:
            free_single_value(n);
            break;
        case free_key:
            if (n->key)
                free(n->key);
            break;
        case free_node:
            free_single_value(n);
            free(n);
            break;
    }
    return true;
}

static value_t *create_value(void *value, short type, bool is_free) {
    value_t *v = (value_t *) malloc(sizeof(value_t));
    assert(v);
    v->value = value;
    v->type = type;
    v->is_free = is_free;
    return v;
}

