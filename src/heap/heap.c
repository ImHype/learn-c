#include <stdlib.h>
#include "heap.h"


int swap(int * p1, int * p2) {
    int tmp = *p1;

    *p1 = *p2;
    *p2 = tmp;

    return 0;
}

int fixup(heap_t * heap) {
    int pos = heap->size - 1;
    int n_val = heap->data[pos];
    // 完全二叉树的骚操作
    int parent = (pos - 1) / 2;

    // 当前节点比父母小，与父母交换位置
    // 上浮
    while (parent >= 0 && n_val < heap->data[parent]){
        swap(heap->data + parent, heap->data + pos);
        pos = parent;
        parent = (pos - 1) / 2;
        n_val = heap->data[pos];
    }

    return 0;
}

int fixdown(heap_t * heap) {
    if (heap->size == 0) {
        return 0;
    }

    int n_val;
    int pos = 0;
    int left = pos * 2 + 1;
    int right = left + 1;

    while (left < heap->size) {
        n_val = heap->data[pos];

        int * leftp = heap->data + left;
        int * rightp = right < heap->size ? heap->data + right: NULL;

        // 下沉
        // 选取左右子节点中更小的数，与当前节点进行替换
        int *ref = rightp ? (*leftp < *rightp ? leftp: rightp): leftp;
        int next_pos = ref == leftp ? left: right;
        if (n_val > *ref) {
            swap(heap->data + pos, ref);
        }
        else
            break;
        
        pos = next_pos;
        left = pos * 2 + 1;
        right = left + 1;
    }

    return 0;
}


int insert_heap(heap_t * heap, int value) {
    heap->data[heap->size] = value;
    heap->size++;
    fixup(heap);
    return 0;
};

int pop_heap(heap_t * heap, int * pop_node) {
    if (heap->size == 0) {
        return -1;
    }
    int val = heap->data[0];

    heap->data[0] = heap->data[heap->size-1];
    heap->size--;

    fixdown(heap);

    *pop_node = val;

    return 0;
};

int init_heap(heap_t * heap, int capacity) {
    heap->size = 0;
    heap->data = malloc(sizeof(int) * capacity);
    heap->insert = insert_heap;
    heap->pop = pop_heap;

    return 0;
};
