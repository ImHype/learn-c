


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
#include <fcntl.h>
#include <errno.h> // errno 变量的头文件
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
            sleep(1);
            write(pipe_for_child_p1[1], buffer, strlen(buffer));
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
            sleep(3);
            write(pipe_for_child_p2[1], buffer, strlen(buffer));
        }
        exit(0);
    }

    // printf("This is the main process\n");

    char buf[64] = "";
    close(pipe_for_child_p1[1]);
    close(pipe_for_child_p2[1]);

    int is_process1_end = 0;
    int is_process2_end = 0;

    if (fcntl(pipe_for_child_p1[0], F_SETFL, O_NONBLOCK) == -1) {
        fprintf(stderr, "Call to fcntl failed.\n");
        exit(1);
    }

    if (fcntl(pipe_for_child_p2[0], F_SETFL, O_NONBLOCK) == -1) {
        fprintf(stderr, "Call to fcntl failed.\n");
        exit(1);
    }

    while (!is_process1_end && !is_process2_end)
    {
        time_t time_1 = time(NULL);
        time_t time_2;

        if (!is_process1_end) {
            int n = read(pipe_for_child_p1[0], buf, 64);

            if (n < 0) {
                if (errno == EAGAIN) {
                }   
                else {
                    perror("read");
                    exit(1);
                }   
            } else {
                if (n == 0) {
                    is_process1_end = 1;
                } else {
                    time_2 = time(NULL);
                    printf("%s\n", buf);
                    printf("read child1 message pending %lus\n", time_2 - time_1);
                }
            }   
        }


        if (!is_process2_end) {
            int n = read(pipe_for_child_p2[0], buf, 64);

            if (n < 0) {
                if (errno == EAGAIN) {
                    // sleep(1); // 让出 CPU，避免CPU长时间空转
                }   
                else {
                    perror("read");
                    exit(1);
                }   
            } else {
                if (n == 0) {
                    is_process2_end = 1;
                } else {
                    time_2 = time(NULL);
                    printf("%s\n", buf);
                    printf("read child2 message pending %lus\n", time(NULL) - time_2);
                }
            }   
        }
        
        sleep(1); // 让出 CPU，避免CPU长时间空转
    }

    wait(NULL);

    return 0;
}
