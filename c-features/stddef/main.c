#include <stddef.h>
#include <stdio.h>
#include <assert.h>

typedef struct {
    int hello;
    int world;
} struct_t;

#define container_of(ptr, type, member) \
  ((type *) ((char *) (ptr) - offsetof(type, member)))

int main(int argc, char const *argv[])
{
    struct_t t;

    t.hello = 123;
    t.world = 456;

    struct_t * hello_container = container_of(&t.hello, struct_t, hello);

    int pos = offsetof(struct_t, hello);

    assert(pos == 0);

    assert(hello_container->hello == t.hello);
    assert(hello_container->world == t.world);
    assert(hello_container == &t);

    printf("All cases success\n");

    return 0;
}
