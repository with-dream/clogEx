#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "../../src/utils/hash_map_str.h"

static void map_test() {
    hash_map *map = hash_map_init_str(0, 0);
    char key[100];
    int count = 100;
    long int start = time(NULL);
    for (int i = 0; i < count; i++) {
        memset(key, 0, 100);
        sprintf(key, "index==>%d", i);
        printf("put==>%ld\n", i);
        hash_map_put_str_v(map, key, "12345", false);
    }
    printf("put=>%d\n", (time(NULL) - start));

    hash_map_debug(map);

    start = time(NULL);
    for (int i = 0; i < count; i++) {
        memset(key, 0, 100);
        sprintf(key, "index==>%d", i);
        value_t *rs = hash_map_get_str(map, key);
        printf("get i:%d res:%s\n", i, rs->value);
    }
    printf("get=>%d\n", time(NULL) - start);
    start = time(NULL);
    for (int i = 0; i < count / 2; i++) {
        memset(key, 0, 100);
        sprintf(key, "index==>%d", i);
        if (i == 268) {
            printf("");
        }
        hash_map_remove_str(map, key, false);
        assert(i + map->size != 2000 - 1);
                printf("remove res:%d size:%d\n", i, map->size);
    }
    printf("remove=>%d\n", time(NULL) - start);
    start = time(NULL);
    char **keys = hash_map_keys_str(map);
    for (int i = 0; i < map->size; i++) {
        printf("%d>%s ks:%d\n", i, keys[i], sizeof(keys) / sizeof(keys[0]));
    }
    printf("keys=>%ld\n", time(NULL) - start);
    printf("size:%d\n", map->size);

    hash_map_release(map);
}

int main() {
    map_test();
    return 0;
}
