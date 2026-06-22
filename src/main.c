#include <stdio.h>
#include <kv.h>
#include <assert.h>


int main() {
    kv_t *table = kv_init(3);
    
    assert(table != NULL);
    assert(table->capacity == 3);
    assert(table->count == 0);

    kv_put(table, "foo", "bar");
    kv_put(table, "foo", "bar");
    assert(table->count == 1);
    kv_put(table, "baz", "bar");
    assert(table->count == 2);

    for(int i = 0; i < table->capacity; i++) {
        printf(
            "Key -> %s | Value -> %s\n",
            table->entries[i].key,
            table->entries[i].value
        );
    }
    kv_free(table);
    return 0;
}
