#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./task_queue.h"

#define ARGV \
    char * type; \
    char * name; \
    char * data; 

typedef struct task_req_t {
    ARGV
} task_req_t;


void* read_file(void* _argv) {
    task_req_t * argv = _argv;
    printf("reading[filename=%s]\n", argv->data);

    int fd = open((char *) argv->data, O_RDONLY);

    if (fd < 0) {
        return 0;
    }

    int size = 0;

    char * buf = (char *) malloc(500 * sizeof(char));
    char chunk[1024];
    
    while ((size = read(fd, chunk, sizeof(chunk))) > 0) {
        strcat(buf, chunk);
    }

    close(fd);

    return buf;
}

void* callback(void* argv) {
    task_t * task = (task_t *) argv;
    task_req_t * req = task->req;

    if (task->error) {
        printf("[%d] filename=%s, error=%s\n", task->id, req->data, strerror(task->error));
    } else {
        printf("[%d] filename=%s, content=%s\n", task->id, req->data, task->result);
    }

    return 0;
}

task_req_t * init_fs_req(char * path) {
    task_req_t * req = (task_req_t*)malloc(sizeof(task_req_t));
    req->data = path;
    return req;
}
  
int main() 
{ 
    task_queue_t * tasks_queue = init_task_queue();
    
    for (int i = 0; i < 10; i++) {
        task_req_t * req = init_fs_req("/Users/xujunyu.joey/learn-series/learn-c/src/task_queue/fixtures/content1.txt");
        add_task(tasks_queue, &read_file, &callback, req);
    }

    for (int i = 0; i < 100000; i++) {
        task_req_t * req = init_fs_req("/Users/xujunyu.joey/learn-series/learn-c/src/task_queue/fixtures/content.txt");
        add_task(tasks_queue, &read_file, &callback, req);
    }

    run_task_queue(tasks_queue);
    return 0; 
} 
