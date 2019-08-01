typedef struct node_s node_t;
typedef struct heap_s heap_t;

struct node_s {
    node_t * left;
    node_t * right;
    int data;
};

typedef int (*insert_heap_t)(heap_t * heap, int value);

typedef int (*del_heap_t)(heap_t * heap, int value);

struct heap_s {
    node_t * root;

    insert_heap_t insert;

    del_heap_t del;
};


int init_heap(heap_t * heap);
