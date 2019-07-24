#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h> 

void first() {
    // make two process which run same 
    // program after this instruction 
    fork ();   // Line 1
    fork ();   // Line 2
    fork ();   // Line 3

    printf("Hello world!\n"); 
}

void second() {
    if (fork() && fork() && fork() && fork()) {
        printf("Hello from Parent!\n"); 
    } else {
        printf("Hello from Children!\n"); 
    }
}


void pid() {
    int pid = fork();

    if (pid) {
        wait(NULL);
        printf("the process is parent process; and my child process is %d\n", pid);
    } else {
        printf("the process is child process\n");
    }
}

int main() 
{ 
    printf("main fc only excuted once\n");
    pid();
    return 0; 
} 
