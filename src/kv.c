#include <kv.h>
#include <string.h>

size_t hash(const char *value, int capacity) {
    size_t hash = 0x13371337deadbeef;

    while(*value) {
        hash ^= *value;
        hash = hash << 8;
        hash += *value;

        value++;
    }

    return hash % capacity;
}

int kv_delete(kv_t *db, char *key) {
    if(!db || !key) return -1;

    size_t idx = hash(key, db->capacity);

    for(int i = 0; i < db->capacity - 1; i++) {
        size_t search_idx = (idx + i) % db->capacity;

        kv_entrie_t *entry = &db->entries[search_idx];

        if(entry->key == NULL) return -1;

        if(entry->key && entry->key != TOMBSTONE && !strcmp(entry->key, key)){
            free(entry->key);
            free(entry->value);
            db->count--;
            entry->key = TOMBSTONE;
            entry->value = NULL;
            return search_idx;
        }
    }

    return -1;
}

char *kv_get(kv_t *db, char *key) {
    if(!db || !key) return NULL;

    size_t idx = hash(key, db->capacity);

    for(int i = 0; i < db->capacity - 1; i++) {
        size_t search_idx = (idx + i) % db->capacity;

        kv_entrie_t *entry = &db->entries[search_idx];

        if(entry->key == NULL) return NULL;

        if(entry->key && entry->key != TOMBSTONE && !strcmp(entry->key, key)){
            return entry->value;
        }
    }

    return NULL;
}

int kv_put(kv_t *db, char *key, char *value) {
    if(!db || !key || !value) return -1;

    size_t idx = hash(key, db->capacity);

    for(int i = 0; i < db->capacity - 1; i++) {
        size_t search_idx = (idx + i) % db->capacity;

        kv_entrie_t *entry = &db->entries[search_idx];

        // TOMBSTONE is an integer, would segfault in strcmp;
        if(entry->key && entry->key != (void *)TOMBSTONE && !strcmp(entry->key, key)) {
            // Get the ownership of the value;
            char *new_value = strdup(value);
            if(!new_value) return -1;
            free(entry->value);
            entry->value = new_value;
            return search_idx;
        }

        if(!entry->key || entry->key == (void *)TOMBSTONE) {
            char *new_value = strdup(value);
            char *new_key = strdup(key);
            if(!new_value || !new_key) {
                free(new_value);
                free(new_key);
                return -1;
            }
            entry->value = new_value;
            entry->key = new_key;
            db->count++;

            return search_idx;
        }
    }

    return -2;
}

kv_t *kv_init(size_t capacity) {
    if(capacity == 0) return NULL;

    kv_t *table = malloc(sizeof(kv_t));
    if(table == NULL) return NULL;

    table->capacity = capacity;
    table->count = 0;
    table->entries = calloc(sizeof(kv_entrie_t), capacity);

    if(table->entries == NULL) return NULL;
    return table;
}

int kv_free(kv_t *db) {
    if(db == NULL) return -1;
    for(int i = 0; i < db->capacity; i++) {
        kv_entrie_t *e = &db->entries[i];

        if(e->key && e->key != TOMBSTONE) {
            free(e->key);
            free(e->value);
            e->key = NULL;
            e->value = NULL;
            db->count--;
        }
    }

    free(db->entries);
    free(db);

    return 0;
}
