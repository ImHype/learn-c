#include <stdlib.h>
#include "skip_list.h"
#include <string.h>


node_t * create_node(int value, int max_level) {
    node_t * node = malloc(sizeof(node_t));

    node->value = value;
    
    int space = max_level * sizeof(node_t *);
    node->next = malloc(space);
    memset(node->next, 0, space);

    return node;
}

int item_level(skip_list_t * skip_list) {
    int level = 0;
    for (int i = 0; i < skip_list->max_level; i++)
    {
        if (rand() % 10 == 0) {
            level++;
        }
    }

    return level;
}

int skip_list_insert(skip_list_t * skip_list, int value) {
    node_t * head = skip_list->head;
    node_t * nnode = create_node(value, skip_list->max_level);

    if (head == NULL) {
        skip_list->head = nnode;
        return 0;
    }
    
    int space = sizeof(node_t *) * skip_list->max_level;
    node_t ** predecessors = malloc(space);
    memset(predecessors, 0, space);

    for (int i = skip_list->level; i >= 0; i--) {
        while (head != NULL)
        {
            node_t * item = head->next[i];

            if (item == NULL) {
                break;
            }

            if (item->value > value) {
                break;
            }
            
            head = item;
        }

        predecessors[i] = head;
    }

    int level = item_level(skip_list);

    if (level > skip_list->level) {
        skip_list->level = level;
    }

    for (int i = level; i >= 0; i--)
    {
        node_t * node = (predecessors[i] == NULL) ? skip_list->head: predecessors[i];

        nnode->next[i] = node->next[i];
        node->next[i] = nnode;
    }

    free(predecessors);
    
    return 0;
};

node_t * skip_list_find(skip_list_t * skip_list, int value) {
    node_t * head = skip_list->head;

    if (head == NULL) {
        return NULL;
    }

    for (int i = skip_list->level; i >= 0; i--) {
        while (head != NULL)
        {
            node_t * item = head->next[i];

            if (item == NULL) {
                break;
            }

            if (item->value > value) {
                break;
            }

            head = item;
        }

        if (value == head->value) {
            return head;
        }
    }

    return NULL;
};

int skip_list_remove(skip_list_t * skip_list, int value) {
    node_t * head = skip_list->head;
    node_t ** prev = &skip_list->head;

    if (head == NULL) {
        return -2;
    }
    
    int space = sizeof(node_t *) * skip_list->max_level;
    node_t ** predecessors = malloc(space);
    memset(predecessors, 0, space);

    int level = -1;

    for (int i = skip_list->level; i >= 0; i--) {

        while (head != NULL)
        {
            node_t * item = head->next[i];

            if (item == NULL) {
                break;
            }

            if (item->value > value) {
                break;
            }
            prev = &head;
            head = item;
        }

        predecessors[i] = head;

        if (value == head->value) {
            level = i;
        }
    }

    if (level < 0) {
        return level;
    }

    for (int i = level; i >= 0; i--)
    {
        *prev = predecessors[i]->next[i];
    }

    free(head->next);
    free(head);

    return 0;
};



int init_skip_list(skip_list_t * skip_list) {
    skip_list->max_level = MAX_LEVEL;
    skip_list->level = 0;

    skip_list->insert = skip_list_insert;
    skip_list->remove = skip_list_remove;
    skip_list->find = skip_list_find;

    return 0;
};