# Task queue
## Description

It's a queue who could make your operations non-blocking.

### MAKE .so
```sh
$ make libtask_queue.so
```

### MAKE main_process
```sh
$ make main_process.o
```

### RUN
```sh
$ ./main_process.o
```

## Quick start

### Define worker
```c
void* read_file(void* _argv) {
    task_req_t * argv = _argv;
    printf("%s\n", argv->data);

    int fd = open((char *) argv->data, O_RDONLY);

    int size = 0;

    char * buf = (char *) malloc(500 * sizeof(char));
    char chunk[1024] = "";
    int chunk_size = sizeof(chunk);
    
    while ((size = read(fd, chunk, chunk_size)) > 0) {
        strcat(buf, chunk);
    }

    return buf;

    return 0;
}
```

### Define callback
```c
void* callback(void* argv) {
    char * buf = argv;
    printf("recieve %s\n", buf);
    return 0;
}
```

### Define main
```c
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
```