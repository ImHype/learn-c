// C program to demonstrate working of Semaphores 
#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <stdlib.h>
#include <unistd.h>
#include "./task_queue.h"

sem_t * sem;
tasks_t pending;
tasks_t done;
pthread_t pthread;


int pipefds[2];

int push_queue(tasks_t * tasks, task_t * task) {
    task_t * new_task = tasks->task;

    if (new_task == NULL) {
        tasks->task = task;
    } else {
        while (new_task->next != NULL)
        {
            new_task = new_task->next;
        }
        new_task->next = task;
    }

    return 0;
}

  
void* task_worker(void * arg) { 
    task_queue_t * task_queue = arg;
    tasks_t *tasks = task_queue->pending;
    tasks_t *done = task_queue->done;
    task_t * task;

    while (1)
    {
        sem_wait(sem);

        task = tasks->task;

        tasks->task = task->next;
        task->next = NULL;

        task->result = task->work(task->req);

        push_queue(done, task);

        write(tasks->pipefds[1], " ", 1);
    }

    return 0;
}

int init_threads(task_queue_t * task_queue) {
    int thread_size = 4;

    for (int i = 0; i < thread_size; i++) {
        pthread_create(&pthread, NULL, task_worker, task_queue); 
        printf("thread(%d) started\n", i);
    }

    return 0;
}

tasks_t * init_task(int * pipefds) {
    tasks_t * tasks = (tasks_t *) malloc(sizeof(tasks_t));
    tasks->task = NULL;
    tasks->pipefds = pipefds;

    return tasks;
}

task_queue_t * init_task_queue() {
    int * pipefds = (int *) malloc(sizeof(int) * 2);
    pipe(pipefds);

    task_queue_t * task_queue = (task_queue_t *) malloc(sizeof(task_queue_t));

    task_queue->active_handles = 0;
    task_queue->pending = init_task(pipefds);
    task_queue->done =  init_task(pipefds);

    sem = sem_open("sem", O_CREAT, 0777, 0);

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

    task_queue->active_handles ++;

    push_queue(tasks, crt_task);

    sem_post(sem);

    return 0;
}


int run_task_queue(task_queue_t * task_queue) {
    tasks_t * tasks = task_queue->pending;
    tasks_t * done = task_queue->done;

    char buf[1] = "";

    while (task_queue->active_handles > 0)
    {
        read(tasks->pipefds[0], buf, 1);
        task_t * task = done->task;

        while (task != NULL)
        {
            task->cb(task);
            task_queue->active_handles --;
            task = task->next;
        }

        done->task = NULL;
    }
    
    return 0;
}