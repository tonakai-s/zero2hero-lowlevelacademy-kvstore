#include <stdio.h>
#include <kv.h>
#include <assert.h>


int main() {
    kv_t *table = kv_init(3);
    
    assert(table != NULL);
    assert(table->capacity == 3);
    assert(table->count == 0);

    kv_free(table);
    return 0;
}
