// C program to demonstrate working of Semaphores 
#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <stdlib.h>
#include <unistd.h>
#include "./task_queue.h"

sem_t * sem;
sem_t * mutex;
tasks_t pending;
tasks_t done;
pthread_t pthread;

#define INIT_SEM(sem) sem_open(sem, O_CREAT, 0777, 0)

#define INIT_MUTEX(mutex) sem_open(mutex, O_CREAT, 0777, 1)
        
#define LOCK() sem_wait(mutex);

#define UN_LOCK() (sem_post(mutex))

int pipefds[2];

int push_queue(tasks_t * tasks, task_t * task) {
    task_t * new_task = tasks->task;

    LOCK();

    if (new_task == NULL) {
        tasks->task = task;
    } else {
        // if (task->next == NULL) {
     
        // } else {
        //     printf("task has next\n");
        // }
        while (new_task->next != NULL)
        {
            new_task = new_task->next;
        }
        new_task->next = task;
    }
    tasks->active_handles ++;

    UN_LOCK();
    return 0;
}

task_t * pop_queue(tasks_t * tasks) {
    LOCK();

    task_t * task = tasks->task;
    tasks->task = task->next;
    task->next = NULL;
    tasks->active_handles --;

    UN_LOCK();
    return task;
}

  
void* run_task(void * arg) { 
    task_queue_t * task_queue = arg;
    tasks_t *tasks = task_queue->pending;
    tasks_t *done = task_queue->done;
    task_t * task;
    void * result;

    while (1)
    {
        sem_wait(sem);

        task = pop_queue(tasks);
    
        task->result = task->work(task->req);
        push_queue(done, task);

        write(tasks->pipefds[1], " ", 1);
    }

    return 0;
}

int init_threads(task_queue_t * task_queue) {
    int thread_size = 4;

    for (int i = 0; i < thread_size; i++) {
        pthread_create(&pthread, NULL, run_task, task_queue); 
        printf("thread(%d) started\n", i);
    }

    return 0;
}

tasks_t * init_task(int * pipefds) {
    tasks_t * tasks = (tasks_t *) malloc(sizeof(tasks_t));

    tasks->task = NULL;
    tasks->pipefds = pipefds;
    tasks->active_handles = 0;

    return tasks;
}

task_queue_t * init_task_queue() {
    int * pipefds = (int *) malloc(sizeof(int) * 2);
    pipe(pipefds);

    task_queue_t * task_queue = (task_queue_t *) malloc(sizeof(task_queue_t));

    task_queue->pending = init_task(pipefds);
    task_queue->done =  init_task(pipefds);

    sem_unlink("sem");
    sem = sem_open("sem", O_CREAT, 0777, 0);

    sem_unlink("mutex");
    mutex = sem_open("mutex", O_CREAT, 0777, 1);

    init_threads(task_queue);

    return task_queue;
}

int add_task(task_queue_t * task_queue, function_t work, function_t cb, void* req) {
    tasks_t * tasks = task_queue->pending;
    task_t * crt_task = (task_t *) malloc(sizeof(task_t));

    crt_task->cb = cb;
    crt_task->work = work;
    crt_task->req = req;
    crt_task->next = NULL;
    crt_task->result = NULL;

    push_queue(tasks, crt_task);

    sem_post(sem);

    return 0;
}


int run_task_queue(task_queue_t * task_queue) {
    tasks_t * tasks = task_queue->pending;
    tasks_t * done = task_queue->done;

    char buf[1] = "";

    while (tasks->active_handles > 0)
    {
        read(tasks->pipefds[0], buf, 1);
        
        task_t * task = done->task;

        while (done->task != NULL)
        {
            task = pop_queue(done);
            task->cb(task);
            free(task);
        }
    }
    
    return 0;
}