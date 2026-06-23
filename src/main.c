#include <stdio.h>
#include <kv.h>
#include <assert.h>


int main() {
    kv_t *table = kv_init(3);
    
    assert(table != NULL);
    assert(table->capacity == 3);
    assert(table->count == 0);

    kv_put(table, "foo", "bar");
    kv_put(table, "baz", "John Doe");

    for(int i = 0; i < table->capacity; i++) {
        printf(
            "Key -> %s | Value -> %s\n",
            table->entries[i].key,
            table->entries[i].value
        );
    }

    char *val = kv_get(table, "foo");
    char *val2 = kv_get(table, "baz");
    char *val3 = kv_get(table, "not_found");
    printf("%s %s %s\n", val, val2, val3);

    kv_delete(table, "foo");
    val = NULL;
    val = kv_get(table, "foo");
    printf("%s %s %s\n", val, val2, val3);

    kv_free(table);
    return 0;
}
