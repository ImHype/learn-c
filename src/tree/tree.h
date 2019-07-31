typedef struct node_t
{
    struct node_t * left;
    struct node_t * right;
    int value;
    void * data;
} node_t;


node_t * node_init(int value);
node_t * node_search(node_t ** tree, int value);
int node_visit(node_t ** tree, int (*callback)(node_t * node));
int node_add_node(node_t ** tree, node_t * node);


typedef struct tree_t
{
    node_t * root;
} tree_t;

int tree_init(tree_t * tree);
node_t * tree_search(tree_t * tree, int value);
int tree_visit(tree_t * tree, int (*callback)(node_t * node));

int tree_add_node(tree_t * tree, int value);
