#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./task_queue.h"

void* work(void* _argv) {
    task_argv_t * argv = _argv;
    printf("%s\n", argv->data);

    char * type = argv->type;
    char * name = argv->name;

    if (strcmp(type, "fs") == 0) {
        int fd = open((char *) argv->data, O_RDONLY);

        if (strcmp(name, "read") == 0) {
            int size = 0;

            char * buf = (char *) malloc(500 * sizeof(char));
            char chunk[1024] = "";
            int chunkSize = sizeof(chunk);
            
            while ((size = read(fd, chunk, chunkSize)) > 0) {
                strcat(buf, chunk);
            }

            return buf;
        }
    }

    return 0;
}

void* callback(void* argv) {
    char * buf = argv;
    printf("recieve %s\n", buf);
    return 0;
}
  
int main() 
{ 
    tasks_info_t * tasks_info = init_tasks();
    
    task_argv_t argv = {
        "fs",
        "read",
        "/Users/xujunyu.joey/learn-series/learn-c/README.md"};

    task_argv_t argv2 = {
        "fs",
        "read",
        "/Users/xujunyu.joey/learn-series/learn-c/Makefile"
    };

    add_task(tasks_info, &work, &callback, &argv);
    add_task(tasks_info, &work, &callback, &argv2);

    run_tasks(tasks_info);
    return 0; 
} 
