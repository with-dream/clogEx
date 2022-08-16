//
// Created by ms on 2022/8/14.
//

#include "hash_map.h"
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <string.h>
#include <printf.h>

static uint get_max_capacity();

static uint node_size(uint cap);

static bool resize(hash_map *map);

static void node_free(hash_map *map);

static void *put_absent(hash_map *map, void *key1, void *value, bool onlyIfAbsent, bool free_enable);

hash_map *hash_map_init(uint capacity, float factor, key_hash hash, key_equals equals, free_callback free_cb) {
    assert(hash && equals && free_cb);
    if (!hash || !equals || !free_cb) return NULL;

    hash_map *map = (hash_map *) malloc(sizeof(hash_map));
    assert(map);
    if (!map) return NULL;
    memset(map, 0, sizeof(hash_map));

    map->hash = hash;
    map->equals = equals;
    map->free_cb = free_cb;
    map->factor = factor < 0.01f ? DEFAULT_LOAD_FACTOR : factor;
    if (capacity)
        map->threshold = node_size(capacity);
    return map;
}

void hash_map_release(hash_map *map) {
    node_free(map);
    free(map);
}

void *hash_map_put(hash_map *map, void *key, void *value, bool free_enable) {
    return put_absent(map, key, value, false, free_enable);
}

void *hash_map_put_absent(hash_map *map, void *key, void *value, bool free_enable) {
    return put_absent(map, key, value, true, free_enable);
}

static void *put_absent(hash_map *map, void *key1, void *value, bool onlyIfAbsent, bool free_enable) {
    assert(map);
    node *p = NULL, *oldValue = NULL;

    if (map->table == NULL || !map->cap)
        resize(map);

    uint i;
    uint hash = map->hash(key1);
    if (!(p = map->table[i = (map->cap - 1) & hash])) {
        node *tmp_node = (node *) malloc(sizeof(node));
        assert(tmp_node);
        memset(tmp_node, 0, sizeof(node));
        tmp_node->hash = hash;
        tmp_node->key = key1;
        tmp_node->value = value;
        map->table[i] = tmp_node;
    } else {
        void *k;
        while (p) {
            if (p->hash == hash &&
                ((k = p->key) == key1 || map->equals(key1, k))) {
                oldValue = p->value;
                if (!onlyIfAbsent || !oldValue)
                    p->value = value;
            }
            if (!p->next) {
                node *tmp_node = (node *) malloc(sizeof(node));
                assert(tmp_node);
                memset(tmp_node, 0, sizeof(node));
                tmp_node->hash = hash;
                tmp_node->key = key1;
                tmp_node->value = value;
                p->next = tmp_node;
                break;
            }
            p = p->next;
        }
    }
    if (++map->size > map->threshold)
        resize(map);

    if (oldValue && free_enable) {
        assert(map->free_cb);
        map->free_cb(oldValue, free_value);
        return NULL;
    }

    return oldValue;
}

void *hash_map_get(hash_map *map, void *key1) {
    assert(map);
    node **tab;
    node *first = NULL, *e = NULL;
    uint n = map->cap;
    void *k = NULL;
    uint hash = map->hash(key1);

    if (MAP_DEBUG) {
        int index = (n - 1) & hash;
        printf("hash_map_get index:%d cap:%d\n", index, map->cap);
        node *tmp = map->table[index];
        while (tmp) {
            printf("hash_map_get key:%s\n", (char *) (tmp->key));
            tmp = tmp->next;
        }
    }

    if ((tab = map->table) && n > 0 &&
        (first = tab[(n - 1) & hash])) {
        if (first->hash == hash && // always check first node
            ((k = first->key) == key1 || map->equals(k, key1))) {
            return first->value;
        }
        while ((e = first->next)) {
            if (e->hash == hash &&
                ((k = e->key) == key1 || map->equals(k, key1)))
                return e->value;
            first = first->next;
        }
    }
    return NULL;
}

void *hash_map_remove(hash_map *map, void *key1, bool free_enable) {
    assert(map);
    node **tab;
    node *first = NULL, *next = NULL;
    int n = map->cap;
    void *k = NULL;
    uint hash = map->hash(key1);

    if ((tab = map->table) && n > 0 &&
        (first = tab[(n - 1) & hash])) {
        if (first->hash == hash && // always check first node
            ((k = first->key) == key1 || map->equals(k, key1))) {
            tab[(n - 1) & hash] = first->next;
            map->size--;
            if (free_enable) {
                assert(map->free_cb);
                map->free_cb(first, free_node);
                return NULL;
            } else
                return first;
        }
        while ((next = first->next)) {
            if (next->hash == hash &&
                ((k = next->key) == key1 || map->equals(k, key1))) {
                first->next = next->next;
                map->size--;
                if (free_enable) {
                    assert(map->free_cb);
                    map->free_cb(next, free_node);
                    return NULL;
                } else
                    return next;
            }
            first = next;
        }
    }
    return NULL;
}

uint hash_map_size(hash_map *map) {
    assert(map);
    return map->size;
}

void hash_map_clear(hash_map *map) {
    assert(map);
    node_free(map);
    map->size = 0;
}

void **hash_map_keys(hash_map *map) {
    assert(map);
    void **res = (void **) malloc(sizeof(void *) * map->size);
    assert(res);
    uint index = 0;
    for (uint i = 0; i < map->cap; i++) {
        node *n = (node *) (map->table[i]);
        while (n) {
            res[index++] = n->key;
            node *tmp = n->next;
            n = tmp;
        }
    }
    assert(index - 1 == map->size);
    return res;
}

void **hash_map_values(hash_map *map) {
    assert(map);
    void **res = (void **) malloc(sizeof(void *) * map->size);
    assert(res);
    uint index = 0;
    for (uint i = 0; i < map->cap; i++) {
        node *n = (node *) (map->table[i]);
        while (n) {
            res[index++] = n->value;
            node *tmp = n->next;
            n = tmp;
        }
    }
    assert(index - 1 == map->size);
    return res;
}

bool hash_map_contains_key(hash_map *map, void *key1) {
    return hash_map_get(map, key1) != NULL;
}

void hash_map_debug(hash_map *map) {
    assert(map);
    for (uint i = 0; i < map->cap; i++) {
        int count = 0;
        node *n = (node *) (map->table[i]);
        while (n) {
            count++;
            n = n->next;
        }
        if (count > 0) {
            printf("==>index:%d count:%d\n", i, count);
        }
    }
}

static bool resize(hash_map *map) {
    node **old_table = map->table;
    uint old_cap = old_table ? map->cap : 0;
    uint old_thr = map->threshold;
    uint new_cap = 0, new_thr = 0;

    if (old_cap > 0) {
        if (old_cap >= get_max_capacity()) {
            map->threshold = UINT_MAX;
            return true;
        } else if ((new_cap = old_cap << 1) < UINT_MAX &&
                   old_cap >= DEFAULT_INITIAL_CAPACITY)
            new_thr = old_thr << 1; // double threshold
    } else if (old_thr > 0) // initial capacity was placed in threshold
        new_cap = old_thr;
    else {               // zero initial threshold signifies using defaults
        new_cap = DEFAULT_INITIAL_CAPACITY;
        new_thr = (int) (DEFAULT_LOAD_FACTOR * DEFAULT_INITIAL_CAPACITY);
    }
    if (new_thr == 0) {
        float ft = (float) new_cap * map->factor;
        new_thr = (new_cap < get_max_capacity() && ft < (float) get_max_capacity() ?
                   (int) ft : UINT_MAX);
    }

    node **new_table = NULL;
    if (!(new_table = (node **) calloc(new_cap, sizeof(node *))))
        return false;
    map->cap = new_cap;
    map->table = new_table;
    map->threshold = new_thr;

    if(MAP_DEBUG) {
        printf("resize old_cap:%d new_cap:%d\n", old_cap, new_cap);
    }

    if (old_table) {
        for (int j = 0; j < old_cap; ++j) {
            node *e = old_table[j];
            if (e) {
                old_table[j] = NULL;
                if (!e->next)
                    new_table[e->hash & (new_cap - 1)] = e;
                else { // preserve order
                    node *loHead = NULL, *loTail = NULL;
                    node *hiHead = NULL, *hiTail = NULL;
                    node *next = NULL;
                    do {
                        next = e->next;
                        if ((e->hash & old_cap) == 0) {
                            if (loTail == NULL)
                                loHead = e;
                            else
                                loTail->next = e;
                            loTail = e;
                        } else {
                            if (hiTail == NULL)
                                hiHead = e;
                            else
                                hiTail->next = e;
                            hiTail = e;
                        }
                        e = next;
                    } while (e);
                    if (loTail) {
                        loTail->next = NULL;
                        new_table[j] = loHead;
                    }
                    if (hiTail) {
                        hiTail->next = NULL;
                        new_table[j + old_cap] = hiHead;
                    }
                }
            }
        }
    }

    return true;
}

static uint get_max_capacity() {
    static uint max_capacity = 0;
    if (max_capacity == 0) {
        switch (sizeof(uint)) {
            case 2:
                max_capacity = 1 << 15;
                break;
            case 4:
                max_capacity = 1 << 30;
                break;
            case 8:
                max_capacity = 1 << 60;
                break;
        }
    }
    assert(max_capacity != 0);
    return max_capacity;
}

static void node_free(hash_map *map) {
    assert(map);
    uint cap = map->cap;
    for (int i = 0; i < cap; i++) {
        node *n = map->table[i];
        while (n) {
            node *tmp = n->next;
            map->free_cb(n, free_node);
            n = tmp;
        }
    }
}

static uint node_size(uint cap) {
    uint n = cap - 1;
    int bit = sizeof(uint);
    for (int i = 1; i < (bit * 8) << 1; i <<= 1) {
        n |= n >> i;
    }
    return (n < 0) ? 1 : (n >= get_max_capacity()) ? get_max_capacity() : n + 1;
}


