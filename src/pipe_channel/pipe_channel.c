#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
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

pipe_channel_t* fork_with_pipe_channel() {
    int * pid = (int *) malloc(sizeof(int));

    pipe_channel_t * pipe_channel = create_pipe_channel(pid);

    if ((*pid = fork()) == -1) {
        perror("fork");
        exit(1);
    }

    init_pipe_channel(pipe_channel);
    return pipe_channel;
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

int get_pipe_channel_fd(pipe_channel_t* pipe_channel) {
    int *pid = pipe_channel->pid;
    channel_t channel = pipe_channel->channel;

    if (*pid > 0) {
        return channel[1][1];
    } else {
        return channel[0][1];
    }
}


void write_pipe_channel(pipe_channel_t* pipe_channel, char * buffer, int size) {
    write(get_pipe_channel_fd(pipe_channel), buffer, size);
}

void end_pipe_channel(pipe_channel_t* pipe_channel) {
    close(get_pipe_channel_fd(pipe_channel));
}


void close_pipe_channel(pipe_channel_t* pipe_channel) {
    end_pipe_channel(pipe_channel);

    free(pipe_channel->channel);
    free(pipe_channel->pid);
    free(pipe_channel);
}

#define CHUNK_SIZE 4



char * read_until_end(pipe_channel_t *pipe_channel) {
    int frame_size = 1;

    int buffer_length = 0;
    int chunk_size = 0;
    char chunk[CHUNK_SIZE];

    char * buffer = (char *) malloc(0);

    while((chunk_size = read_pipe_channel(pipe_channel, chunk, CHUNK_SIZE)) > 0) {
        strcat(buffer, chunk);
        memset(chunk, 0, 4);
    }
    return buffer;
}
