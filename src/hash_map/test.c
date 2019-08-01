#include <stdio.h>
#include "hash_map.h"
#include "assert.h"

int print(void * key, void * value) {
    printf("%s:", key);
    printf("%s\n", value);
    return 0;
}


int main(int argc, char const *argv[])
{
    hashmap_t hashmap;
    hashmap_t * h = &hashmap;

    hash_map_init(h);

    h->put(h, "hello", "world");
    assert( h->get(h, "hello") == "world");

    h->put(h, "hello", "world1");
    assert( h->get(h, "hello") == "world1");

    h->put(h, "hello", "world2");
    assert( h->get(h, "hello") == "world2");

    h->put(h, "hello", "world3");
    assert( h->get(h, "hello") == "world3");

    h->del(h, "hello");

    assert(h->isempty(h));
    h->put(h, "hello", "world");
    h->put(h, "hello1", "world");
    assert(h->size == 2);

    // assert(h->get(h, "hello1") == "world");

    h->put(h, "key1", "hello");
    h->put(h, "key2", "hello");
    h->put(h, "key3", "hello");
    h->put(h, "key4", "hello");

    assert(h->get(h, "key1") == "hello");
    assert(h->get(h, "key2") == "hello");
    assert(h->get(h, "key3") == "hello");
    assert(h->get(h, "key4") == "hello");
    
    hash_map_foreach(h, print);

    return 0; 
}
