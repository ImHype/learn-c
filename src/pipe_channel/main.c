#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include "pipe_channel.h"


int main(void)
{
    pid_tt   childpid;

    pipe_channel_t * pipe_channel = create_pipe_channel(&childpid);

    if ((childpid = fork()) == -1) {
        perror("fork");
        return 1;
    }

    init_pipe_channel(pipe_channel);

    pid_tt pid = *pipe_channel->pid;

    if (pid == 0) {
        char buffer[100];
        read_pipe_channel(pipe_channel, buffer, 100);

        printf("recieved msg from parent: %s\n", buffer);
        
        char new_buffer[] = "Hello Parent";

        write_pipe_channel(pipe_channel, new_buffer, strlen(new_buffer) + 1);
    } else if (pid > 0)
    {
        char buffer[] = "Hello Child";

        write_pipe_channel(pipe_channel, buffer, strlen(buffer) + 1);

        char res[100] = "";

        read_pipe_channel(pipe_channel, res, 100);

        printf("recieved msg from child: %s\n", res);

        wait(NULL);
    }

    return 0;
}
