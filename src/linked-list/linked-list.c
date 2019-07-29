#include "stdlib.h"
#include "linked-list.h"

int create_linked_list(linked_list_t * linked_list) {
    linked_list->length = 0;
    linked_list->head = NULL;
    return 0;
}

int linked_list_size(linked_list_t * linked_list) {
    return linked_list->length;
}


node_t * linked_list_head(linked_list_t * linked_list) {
    return linked_list->head;
}
node_t * create_node(void * element) {
    node_t * node = malloc(sizeof(node_t));
    node->element = element;
    node->next = NULL;

    return node;
}

int linked_list_add(linked_list_t * linked_list, void * element) {
    node_t * node = create_node(element);

    node_t ** n;
    n = &(linked_list->head);

    while (*n != NULL)
    {
        n = &(*n)->next;
    }

    *n = node;
    linked_list->length++;

    return 0;
}


int linked_list_remove(linked_list_t * linked_list, void * element) {
    int index = 0;
    node_t ** n;
    n = &(linked_list->head);

    node_t * p;

    while (*n != NULL)
    {
        if ((*n)->element == element) {
            (*n) = (*n)->next;
            linked_list->length--;
            return index;
        }

        n = &(*n)->next;
        index++;
    }

    return -1;
};


int linked_list_is_empty(linked_list_t * linked_list) {
    return linked_list_size(linked_list) == 0;
};


int linked_list_index_of(linked_list_t * linked_list, void * element) {
    int i = 0;
    node_t ** n;
    n = &(linked_list->head);

    node_t * p;


    while (*n != NULL)
    {
        if ((*n)->element == element) {
            return i;
        }

        n = &(*n)->next;
        i++;
    }

    return -1;
};


node_t * linked_list_element_at(linked_list_t * linked_list, int index) {
    int i = 0;
    node_t ** n;
    n = &(linked_list->head);

    node_t * p;

    while (i < index)
    {
        if (*n == NULL) {
            return NULL;        
        }

        n = &(*n)->next;

        i++;
    }

    return *n;
};

int linked_list_add_at(linked_list_t * linked_list, int index, void * element) {
    int i = 0;
    node_t ** n;
    n = &(linked_list->head);

    node_t * p;

    while (i < index)
    {
        if (*n == NULL) {
            (*n) = create_node(NULL);
        }

        n = &(*n)->next;
        i++;
    }

    node_t * node = create_node(element);
    node->next = (*n)->next;
    (*n) = node;

    return 1;
};


int linked_list_remove_at(linked_list_t * linked_list, int index) {
    int i = 0;
    node_t ** n;
    n = &(linked_list->head);

    node_t * p;

    while (i < index)
    {
        if (*n == NULL) {
            return 0;
        }

        n = &(*n)->next;
        i++;
    }

    (*n) = (*n)->next;

    return 1;
};


int linked_list_foreach(linked_list_t * linked_list, int (*callback)(int index, void *)) {
    int index = 0;
    node_t ** n;
    n = &(linked_list->head);

    node_t * p;

    while (*n != NULL)
    {
        callback(index, (*n)->element);
        n = &(*n)->next;
        index++;
    }

    return 0;
};