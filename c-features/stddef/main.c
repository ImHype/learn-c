#include <stddef.h>
#include <stdio.h>

typedef struct struct_t
{
    int hello2;
    int hello;
} struct_t;


int main(int argc, char const *argv[])
{
    struct_t t;

    int pos = offsetof(struct_t, hello);

    printf("%d", pos);

    return 0;
}
