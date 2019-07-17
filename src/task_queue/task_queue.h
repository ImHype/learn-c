// C program to demonstrate working of Semaphores 
typedef void* (*function_t)(void *);


typedef struct task_t
{
    void * req;
    function_t work;
    function_t cb;

    void * result;

    struct task_t * next;
    
} task_t;

typedef struct tasks_t {
    int * pipefds;
    task_t * task;
} tasks_t;

typedef struct task_queue_t
{
    tasks_t * pending;
    tasks_t * done;
    int active_handles;
} task_queue_t;

task_queue_t * init_task_queue();

int add_task(task_queue_t * tasks_info, function_t work, function_t cb, void* req);

int run_task_queue(task_queue_t * tasks_info);