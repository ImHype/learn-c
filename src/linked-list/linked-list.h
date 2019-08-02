#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node_t {
    void * element;
    struct node_t * next;
} node_t;


typedef struct linked_list_s {
    node_t * head;
    int length;
} linked_list_t;


int create_linked_list(linked_list_t * linked_list);
int linked_list_size(linked_list_t * linked_list);
node_t * linked_list_head(linked_list_t * linked_list);
int linked_list_add(linked_list_t * linked_list, void * element);
int linked_list_remove(linked_list_t * linked_list, void * element);
int linked_list_is_empty(linked_list_t * linked_list);
int linked_list_index_of(linked_list_t * linked_list, void * element);
node_t * linked_list_element_at(linked_list_t * linked_list, int index);
int linked_list_add_at(linked_list_t * linked_list, int index, void * element);
int linked_list_remove_at(linked_list_t * linked_list, int index);
int linked_list_foreach(linked_list_t * linked_list, int (*callback)(int index, void *));

#define LIST_FOREACH_BEGIN(linked_list, q)\
    int i = 0;\
    node_t ** n;\
    n = &(linked_list->head);\
    while (*n != NULL)\
    {\
        q = (*n)->element;
    
#define LIST_FOREACH_END \
        n = &(*n)->next;\
        i++;\
    }


#endif
