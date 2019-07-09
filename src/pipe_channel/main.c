#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "pipe_channel.h"


int main(void)
{
    pipe_channel_t * pipe_channel = fork_with_pipe_channel();
    pid_tt pid = *pipe_channel->pid;

    if (pid == 0) {
        char * buffer = read_until_end(pipe_channel);
        printf("message from child:\n\n%s", buffer);

        char new_buffer[4][100] = {"Hello Parent\n", "I'm Child Process\n", "Here is my message to you:\n", "I want to exit(0)\n"};
        for (int i = 0; i < 4; i++)
        {
            write_pipe_channel(pipe_channel, new_buffer[i], strlen(new_buffer[i]));
        }
        end_pipe_channel(pipe_channel);
        close_pipe_channel(pipe_channel);
        exit(0);
    } else if (pid > 0)
    {
        char buffer[4][100] = {"Hello Child\n", "I'm Parent Process\n", "Here is my message to you:\n", "Keep down and carry on\n"};

        for (int i = 0; i < 4; i++)
        {
            write_pipe_channel(pipe_channel, buffer[i], strlen(buffer[i]));
        }

        end_pipe_channel(pipe_channel);
        wait(NULL);

        char * res = read_until_end(pipe_channel);

        printf("\nmessage from parent:\n\n%s", res);

        close_pipe_channel(pipe_channel);

        exit(0);
    }

    return 0;
}
