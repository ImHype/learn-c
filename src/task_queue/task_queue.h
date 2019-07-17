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
    int active_handles;
    task_t * task;
} tasks_t;

typedef struct task_queue_t
{
    tasks_t * pending;
    tasks_t * done;
} task_queue_t;

task_queue_t * init_task_queue();

int add_task(task_queue_t * tasks_info, function_t work, function_t cb, void* req);

int run_task_queue(task_queue_t * tasks_info);

tasks_t * init_task(int * pipefds);

int push_queue(tasks_t * tasks, task_t * task);

task_t * pop_queue(tasks_t * tasks);