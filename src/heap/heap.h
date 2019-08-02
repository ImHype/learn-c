typedef struct heap_s heap_t;

typedef int (*insert_heap_t)(heap_t * heap, int value);

typedef int (*del_heap_t)(heap_t * heap, int * pop_node);

struct heap_s {
    int * data;

    int size;

    // int capacity;

    insert_heap_t insert;

    del_heap_t pop;
};


int init_heap(heap_t * heap, int capacity);
