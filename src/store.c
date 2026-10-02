#include "store.h"

#include <stdlib.h>
#include <string.h>

#include "uthash.h"

typedef struct Entry {
    char *key;    // uthash가 이 필드를 키로 쓰도록 HASH_ADD_KEYPTR에서 지정한다
    char *value;
    UT_hash_handle hh;
} Entry;

struct Store {
    Entry *entries; // uthash 테이블의 "머리" — NULL이면 빈 테이블
};

Store *store_create(void) {
    Store *s = malloc(sizeof(Store));
    s->entries = NULL;
    return s;
}

void store_destroy(Store *s) {
    Entry *e, *tmp;
    HASH_ITER(hh, s->entries, e, tmp) {
        HASH_DEL(s->entries, e);
        free(e->key);
        free(e->value);
        free(e);
    }
    free(s);
}

void store_set(Store *s, const char *key, const char *value) {
    Entry *e;
    HASH_FIND_STR(s->entries, key, e);
    if (e) {
        free(e->value);
        e->value = strdup(value);
        return;
    }

    e = malloc(sizeof(Entry));
    e->key = strdup(key);
    e->value = strdup(value);
    HASH_ADD_KEYPTR(hh, s->entries, e->key, strlen(e->key), e);
}

const char *store_get(Store *s, const char *key) {
    Entry *e;
    HASH_FIND_STR(s->entries, key, e);
    return e ? e->value : NULL;
}

int store_del(Store *s, const char *key) {
    Entry *e;
    HASH_FIND_STR(s->entries, key, e);
    if (!e) return 0;

    HASH_DEL(s->entries, e);
    free(e->key);
    free(e->value);
    free(e);
    return 1;
}
