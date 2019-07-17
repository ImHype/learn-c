# Task queue
## Description

It's a queue who could make your operations non-blocking.

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
    int chunkSize = sizeof(chunk);
    
    while ((size = read(fd, chunk, chunkSize)) > 0) {
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
    
    task_req_t * req1 = init_fs_req("/Users/xujunyu.joey/learn-series/learn-c/README.md");
    task_req_t * req2 = init_fs_req("/Users/xujunyu.joey/learn-series/learn-c/Makefile");

    add_task(tasks_queue, &read_file, &callback, req1);
    add_task(tasks_queue, &read_file, &callback, req2);

    run_task_queue(tasks_queue);
    return 0; 
} 
 
```