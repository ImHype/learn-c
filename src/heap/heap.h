typedef struct min_heap_s min_heap_t;

typedef int (*push_min_heap_t)(min_heap_t * heap, int value);

typedef int (*del_min_heap_t)(min_heap_t * heap, int * pop_node);

struct min_heap_s {
    int * data;

    int size;

    // int capacity;

    push_min_heap_t push;

    del_min_heap_t pop;
};


int init_min_heap(min_heap_t * heap, int capacity);
