#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include "pipe_channel.h"


pipe_channel_t* create_pipe_channel(pid_tt * pid)  {
    int rows = 2;
    int **channel = (int **) malloc(rows * sizeof(int *));

    for (int i = 0; i < rows; i++) {
        channel[i] = (int *) malloc (2 * sizeof(int));
    }

    // child -> parent
    pipe(channel[0]);

    // parent -> child
    pipe(channel[1]);

    pipe_channel_t * pipe_channel = (pipe_channel_t * ) malloc (sizeof(pipe_channel_t));

    pipe_channel->pid = pid;
    pipe_channel->channel = channel;

    return pipe_channel;
}

void init_pipe_channel(pipe_channel_t* pipe_channel) {
    int *pid = pipe_channel->pid;
    channel_t channel = pipe_channel->channel;
    if (*pid > 0) {
        // Half Opened fd
        // read only
        close(channel[0][1]);
        // write only
        close(channel[1][0]);
    } else {
        // Half Opened fd
        // read only
        close(channel[1][1]);
        // write only
        close(channel[0][0]);
    }
}

int read_pipe_channel(pipe_channel_t* pipe_channel, char * buffer, int size) {
    int *pid = pipe_channel->pid;
    channel_t channel = pipe_channel->channel;

    if (*pid > 0) {
        return read(channel[0][0], buffer, size);
    } else {
        return read(channel[1][0], buffer, size);
    }
}


int write_pipe_channel(pipe_channel_t* pipe_channel, char * buffer, int size) {
    int *pid = pipe_channel->pid;
    channel_t channel = pipe_channel->channel;

    if (*pid > 0) {
        return write(channel[1][1], buffer, size);
    } else {
        return write(channel[0][1], buffer, size);
    }
}