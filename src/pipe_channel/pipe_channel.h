typedef int pid_tt;

typedef int** channel_t;

typedef struct pipe_channel_t {
    channel_t channel;
    pid_tt * pid;
} pipe_channel_t;


pipe_channel_t* create_pipe_channel(pid_tt * pid);

void init_pipe_channel(pipe_channel_t* pipe_channel);

int read_pipe_channel(pipe_channel_t* pipe_channel, char * buffer, int size);

void write_pipe_channel(pipe_channel_t* pipe_channel, char * buffer, int size);

void close_pipe_channel(pipe_channel_t* pipe_channel);

char * read_until_end(pipe_channel_t *pipe_channel);