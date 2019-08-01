#include "heap.h"


int main(int argc, char const *argv[])
{
    heap_t heap;
    heap_t * h;

    init_heap(h);

    h->insert(h, 1);
    return 0;
}
