// C program to demonstrate working of Semaphores 

typedef void* (*function_t)(void *);
typedef void* (*function_p_t)(void **);

typedef struct task_t
{
    int id;
    void * req;

    function_p_t work;
    function_t cb;

    void * result;
    int error;

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

int add_task(task_queue_t * task_queue, task_t * task);

int run_task_queue(task_queue_t * tasks_info);

tasks_t * init_tasks(int * pipefds);

task_t * init_task(function_p_t work, function_t cb, void* req);

int push_queue(tasks_t * tasks, task_t * task);

task_t * pop_queue(tasks_t * tasks);