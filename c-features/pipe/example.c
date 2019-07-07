


/*****************************************************************************
 Excerpt from "Linux Programmer's Guide - Chapter 6"
 (C)opyright 1994-1995, Scott Burkett
 ***************************************************************************** 
 MODULE: pipe.c
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

typedef int pid_tt;


int main(void)
{

    int fds[2];

    pid_tt   childpid;

    pipe(fds);

    if ((childpid = fork()) == -1) {
        perror("fork");
        return 1;
    }

    if (childpid == 0) {
        // Pipe is a Half Duplex IPC way
        // Write Only
        close(fds[0]);
       
        int *write_fd = &fds[1];
        char * buffer = "hello world";
        write(*write_fd, buffer, strlen(buffer));

    } else if (childpid > 0)
    {
        // Pipe is a Half Duplex IPC way
        // Read Only
        close(fds[1]);
        char * buffer = (char *) malloc(100);
        int byteLength;

        byteLength = read(fds[0], buffer, 100);
        printf("Recieve the buffer(size=%d): %s", byteLength, buffer);
    }

    return 0;
}
