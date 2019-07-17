// C program to demonstrate working of Semaphores 
typedef void* (*function_t)(void *);

#define ARGV \
    char * type; \
    char * name; \
    char * data; 

typedef struct task_argv_t {
    ARGV
} task_argv_t;

typedef struct init_tasks_argv_t {
    int * pipefds;
} init_tasks_argv_t;

typedef struct task_t
{
    void * argv;
    function_t work;
    function_t cb;

    void * result;

    struct task_t * next;
    
} task_t;

typedef struct tasks_t {
    int * pipefds;
    task_t * task;
} tasks_t;

typedef struct tasks_info_t
{
    tasks_t * pending;
    tasks_t * done;
} tasks_info_t;


tasks_info_t * init_tasks();

int add_task(tasks_info_t * tasks_info, function_t work, function_t cb, void* argv);

int run_tasks(tasks_info_t * tasks_info);