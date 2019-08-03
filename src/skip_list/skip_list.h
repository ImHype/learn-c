
#define MAX_LEVEL 3

typedef struct node_s node_t; 
typedef struct skip_list_s skip_list_t; 
typedef int (*insert_t)(skip_list_t * skip_list, int value);
typedef node_t * (*find_t)(skip_list_t * skip_list, int value);
typedef int (*remove_t)(skip_list_t * skip_list, int value);

struct node_s
{
    node_t ** next;
    int value;
};


struct skip_list_s
{
    int max_level;
    int level;
    node_t * head;

    insert_t insert;
    find_t find;
    remove_t remove;
};


int init_skip_list(skip_list_t * skip_list);

int skip_list_insert(skip_list_t * skip_list, int value);

node_t * skip_list_find(skip_list_t * skip_list, int value);

int skip_list_remove(skip_list_t * skip_list, int value);