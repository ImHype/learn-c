


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
#include <time.h>
typedef int pid_tt;

int main(void)
{

    int pipe_for_child_p1[2];
    int pipe_for_child_p2[2];

    pid_tt   childpid;

    pipe(pipe_for_child_p1);
    pipe(pipe_for_child_p2);

    if ((childpid = fork()) == -1) {
        perror("fork");
        return 1;
    }


    if (childpid == 0) {
        // Pipe is a Half Duplex IPC way
        // Write Only
        close(pipe_for_child_p1[0]);
       
        char buffer[] = "from child process 1";
        int i = 0;
        while (i++ < 3)
        {
            write(pipe_for_child_p1[1], buffer, strlen(buffer) + 1);
            sleep(1);
        }
        exit(0);
    } 

    if ((childpid = fork()) == -1) {
        perror("fork");
        return 1;
    }

    if (childpid == 0) {
        // Pipe is a Half Duplex IPC way
        // Write Only
        close(pipe_for_child_p2[0]);
        // printf("This is child process 2.\n");
    
        char buffer[] = "from child process 2";
        int i = 0;

        while (i++ < 3)
        {
            write(pipe_for_child_p2[1], buffer, strlen(buffer) + 1);
            sleep(3);
        }
        exit(0);
    }

    // printf("This is the main process\n");

    char buf[64] = "";
    close(pipe_for_child_p1[1]);
    close(pipe_for_child_p2[1]);

    int is_process1_end = 0;
    int is_process2_end = 0;

    while (!is_process1_end && !is_process2_end)
    {
        time_t time_1 = time(NULL);
        time_t time_2;
        if (!is_process1_end) {
            is_process1_end = !(read(pipe_for_child_p1[0], buf, 64));
            if (!is_process1_end) {
                printf("%s\n", buf);
                time_2 = time(NULL);
                printf("read child1 message pending %lus\n", time_2 - time_1);
            }
        }


        if (!is_process2_end) {
            is_process2_end = !(read(pipe_for_child_p2[0], buf, 64));
            if (!is_process2_end) {
                printf("%s\n", buf);
                printf("read child2 message pending %lus\n", time(NULL) - time_2);
            }
        }

    }

    wait(NULL);

    return 0;
}
