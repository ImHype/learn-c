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

int push_task(tasks_t * tasks, task_t * task) {
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

  
void* thread_main(void * arg) { 
    tasks_info_t * tasks_info = arg;
    tasks_t *tasks = tasks_info->pending;
    tasks_t *done = tasks_info->done;
    task_t * task;

    while (1)
    {
        sem_wait(sem);

        task = tasks->task;

        tasks->task = task->next;
        task->next = NULL;

        task->result = task->work(task->argv);

        push_task(done, task);

        write(tasks->pipefds[1], " ", 1);
    }

    return 0;
}

int init_threads(tasks_info_t * task_info) {
    int thread_size = 4;

    for (int i = 0; i < thread_size; i++) {
        pthread_create(&pthread, NULL, thread_main, task_info); 
        printf("thread(%d) started\n", i);
    }

    return 0;
}

tasks_info_t * init_tasks() {
    int * pipefds = (int *) malloc(sizeof(int) * 2);

    tasks_info_t * task_info = (tasks_info_t *) malloc(sizeof(tasks_info_t));

    tasks_t * tasks = (tasks_t *) malloc(sizeof(tasks_t));
    tasks_t * done = (tasks_t *) malloc(sizeof(tasks_t));

    tasks->pipefds = pipefds;
    done->pipefds = pipefds;

    done->task = NULL;
    tasks->task = NULL;

    task_info->pending = tasks;
    task_info->done = done;

    pipe(tasks->pipefds);

    sem = sem_open("sem", O_CREAT, 0777, 0);

    init_threads(task_info);

    return task_info;
}



int add_task(tasks_info_t * tasks_info, function_t work, function_t cb, void* argv) {
    tasks_t * tasks = tasks_info->pending;

    task_t * crt_task = (task_t *) malloc(sizeof(task_t));

    crt_task->cb = cb;
    crt_task->work = work;
    crt_task->argv = argv;
    crt_task->next = NULL;
    crt_task->result = NULL;

    push_task(tasks, crt_task);

    sem_post(sem);

    return 0;
}


int run_tasks(tasks_info_t * tasks_info) {
    tasks_t * tasks = tasks_info->pending;
    tasks_t * done = tasks_info->done;

    char buf[1] = "";

    while (1)
    {
        read(tasks->pipefds[0], buf, 1);
        task_t * task = done->task;

        while (task != NULL)
        {
            task->cb(task->result);
            task = task->next;
        }

        done->task = NULL;
    }
    
    return 0;
}