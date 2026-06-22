#include <stdio.h>
#include <kv.h>
#include <assert.h>


int main() {
    kv_t *table = kv_init(3);
    
    assert(table != NULL);
    assert(table->capacity == 3);
    assert(table->count == 0);

    printf("Inserted at: %d\n", kv_put(table, "color", "blue"));
    assert(table->count == 1);
    printf("Inserted at: %d\n", kv_put(table, "color", "blue"));
    printf("Inserted at: %d\n", kv_put(table, NULL, NULL));
    //assert(table->count == 2);

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
